#pragma once

#include <map>
#include <unordered_map>
#include <stack>

#include "airportnodes.h"

using namespace std;

class Graph
{
public:
  /**
   * Given a file name for a csv file with data on airport nodes from https://openflights.org/data.html, this function populates a map with
   * the airport nodes and the keys to the aiports are their unique IDs that were assigned to them by openflights.
   *
   * @param airports_filename Name of the file which contains the data on airports.
   */
  void allAirports(string airports_filename);
  /**
   * Given a file name for a csv file with data on airplane routes from https://openflights.org/data.html, this function populates the unordered sets of neighbors
   * that each airport node has.
   *
   * @param routes_filename Name of the file which contains the data on routes.
   */
  void createGraph(string routes_filename);
  /**
   * Given an ID for an airport, this function will return another ID of the airport closest to it that can be flown to from the given airport.
   *
   * @param source_id ID of the airport from which you want to start
   * @param dest_id ID of the airport that you want to arrive at
   */
  bool flightPathExists(int source_id, int dest_id);
  /**
   * Given a source node ID and a destination node ID, return the shortest path between the two nodes in a vector of airport IDs
   *
   * @param source_id ID of the airport that you are starting from.
   * @param dest_id ID of the airport that you consider your destination.
   */
  vector<int> shortestPath(int source_id, int dest_id);
  /**
   * Calculates the Haversine distance between two airports using the coordinates
   * @param id1 : first airport ID
   * @param id2 : second airport ID
   */
  double getHaversineDistance(int id1, int id2);
  /**
   * Gets the strongly connected components on airport nodes graph given a node id using Kosaraju's Algorithm
   * @param id ID of the airport of which the function will return all nodes in its Strongly Connected Component Graph.
   */
  std::vector<int> getStronglyConnected(int id);

  /**
   * Returns all the airports in the map inside a vector
   */
  std::vector<AirportNode *> getAirports();

private:
  /**
   * A helper method for the Strongly Connected Components Graph method that helps form the vector of components using the transpose of the original graph
   * @param visited map of airport IDs to a boolean value declaring if they were visited or not
   * @param ids Vector of airport IDs that are connected through strongly connected component
   * @param bmap A Map that maps airport ids to an unordered set of airport ids that are the key's neighbors in the transpose
   */
  void stronglyFormer(int id,
                      std::unordered_map<int, bool> &visited, std::vector<int> &ids,
                      unordered_map<int, unordered_set<int>> &bmap);
  /**
   * A helper method for the Strongly Connected Components Graph method that helps create the stack of IDs through using DFS
   * @param id ID of the airport to be checked
   * @param visited map detailing whether a node has been visited or not
   * @param stack stack of airport IDs that is being built
   */
  void stronglyHelper(int id,
                      std::unordered_map<int, bool> &visited, stack<int> &stack);

  // Maps Airport IDs to a AirportNode object containing the airport data
  unordered_map<int, AirportNode *> amap_;
  // Maps Airport IDs to a boolean declaring whether the aiport has been visited for a method.
  unordered_map<int, bool> visited_map_;
  // Maps the Airport IDs to a double that contains a distance value for use in the shortest path algorithm
  unordered_map<int, double> dist_map_;
  // Number of airports
  int vertices_;
  // Number of routes between airports
  int edges_;
};
