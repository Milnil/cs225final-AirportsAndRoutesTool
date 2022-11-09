#pragma once

#include <map>

#include "airportnodes.h"

using namespace std;

class Graph {
    public:
    vector<AirportNode> allAirports(string airports_filename);
    void createGraph(string routes_filename);
    
    private:
    map<string, AirportNode> amap_;


}