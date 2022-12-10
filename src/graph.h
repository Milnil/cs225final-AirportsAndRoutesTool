#pragma once

#include <map>
#include <unordered_map>
#include <stack>

#include "airportnodes.h"

using namespace std;

class Graph {
    public:
    void allAirports(string airports_filename);
    void createGraph(string routes_filename);
    bool flightPathExists(int source_id, int dest_id);
    vector<int> shortestPath(int source_id, int dest_id);
    double getHaversineDistance(int id1, int id2);
    std::vector<int> getStronglyConnected(int id);

    //TESTING METHODS
    std::vector<AirportNode *> getAirports();

    private:
    void stronglyFormer(int id,
     std::unordered_map<int, bool> &visited, std::vector<int> &ids,
      unordered_map<int, unordered_set<int>> &bmap);
    void stronglyHelper(int id, 
    std::unordered_map<int, bool> &visited, stack<int> &stack);

    unordered_map<int, AirportNode *> amap_;
    unordered_map<int, bool> visited_map_;
    unordered_map<int, double> dist_map_;
    int vertices_;
    int edges_;
};