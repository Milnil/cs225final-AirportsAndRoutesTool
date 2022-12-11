#pragma once

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class AirportNode {
    public:
    // Default Constructor of an airport node
    AirportNode();
    /**
     * Constructor of an Airport node that accepts a unique airport ID, coordinates, and set of neighboring airports
     * @param id : openflights unique identifier for an airport
     * @param location : coordinates of the airport in latitude, longitude
     * @param neighbors : unordered set of neighboring airports
    */
    AirportNode(int id, pair<double, double> location, unordered_set<int> neighbors);
    /**
     * Method to return the coordinate of an airport node in latitude, longitude
    */
    pair<double, double> getLocation();
    /**
     * Method to return the ID of an airport 
    */
    int getID();
    /**
     * Method to set the ID of an airport node
     * @param id : openflights unique identifier for an airport
    */
    void setID(int id);
    /**
     * Method to add a neighbor to the set of neighbors of an airport node
     * @param neighbor : openflights unique identifier for the neighboring airport
    */
    void addNeighbor(int neighbor);
    /**
     * Method to set the location of an airport in terms of latitude, longitude
     * @param latitude : latitude for the airport
     * @param longitude : longitude for the airport
    */
    void setLocation(double latitude, double longitude);
    /**
     * Method to get the set of neighbors for an airport
    */
    unordered_set<int> getNeighbors();

    private:
    int id_;
    pair<double, double> location_;
    unordered_set<int> neighbors_;
};
