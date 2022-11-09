#pragma once

#include <vector>
#include <string>

using namespace std;

class AirportNode {
    public:
    AirportNode();
    AirportNode(int id, pair<double, double> location, vector<AirportNode> neighbors);
    pair<double, double> getLocation();
    int getID();
    void setID(int id);
    void addNeighbor(AirportNode neighbor);
    void setLocation(double latitude, double longitude);

    private:
    int id_;
    pair<double, double> location_;
    vector<AirportNode> neighbors_;

};