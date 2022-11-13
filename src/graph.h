#pragma once

#include <map>
#include <unordered_map>

#include "airportnodes.h"

using namespace std;

class Graph {
    public:
    void allAirports(string airports_filename);
    void createGraph(string routes_filename);

    // FOR TESTING
    std::vector<AirportNode*> getAirports();


    private:
    unordered_map<int, AirportNode*> amap_;

};