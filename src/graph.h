#pragma once

#include <map>
#include <unordered_map>

#include "airportnodes.h"

using namespace std;

class Graph {
    public:
    void allAirports(string airports_filename);
    void createGraph(string routes_filename);
    bool flightPathExists(int source_id, int dest_id);
    vector<AirportNode *> shortestPath(int source_id);
    double getHaversineDistance(int id1, int id2);

    // FOR TESTING
    std::vector<AirportNode *> getAirports();

private:
    unordered_map<int, AirportNode *> amap_;
    unordered_map<int, bool> visited_map_;

    int vertices_;
    int edges_;
};