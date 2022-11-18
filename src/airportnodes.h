#pragma once

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class AirportNode {
    public:
    AirportNode();
    AirportNode(int id, pair<double, double> location, unordered_set<int> neighbors);
    pair<double, double> getLocation();
    int getID();
    void setID(int id);
    void addNeighbor(int neighbor);
    void setLocation(double latitude, double longitude);
    unordered_set<int> getNeighbors();

    private:
    int id_;
    pair<double, double> location_;
    unordered_set<int> neighbors_;

};