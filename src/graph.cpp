#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <math.h>


/**
 * Given a file name for a csv file with data on airport nodes from https://openflights.org/data.html, this function populates a map with 
 * the airport nodes and the keys to the aiports are their unique IDs that were assigned to them by openflights. 
 * 
 * @param airports_filename Name of the file which contains the data on airports.
 */
void Graph::allAirports(string airports_filename) {
    ifstream file;
    vector<string> row;
    string line, word;
    file.open(airports_filename);
    if (file.is_open()) {
        while(getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            
            AirportNode* a = new AirportNode(stoi(row.at(0)), pair<double, double>(stod(row.at(6)), stod(row.at(7))), unordered_set<int>());
            amap_.insert(pair<int, AirportNode*>(stoi(row.at(0)), a));
        }
    } else {
        exit(EXIT_FAILURE);
    }
}

/**
 * Given a file name for a csv file with data on airplane routes from https://openflights.org/data.html, this function populates the unordered sets of neighbors
 * that each airport node has. 
 * 
 * @param routes_filename Name of the file which contains the data on routes.
 */
void Graph::createGraph(string routes_filename) {
    fstream file(routes_filename, ios::in);
    vector<string> row;
    string line, word;
    
    if (file.is_open()) {
        while(getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            amap_.at(stoi(row.at(3)))->addNeighbor(stoi(row.at(5)));
        }
    }
}

/**
 * Given an ID for an airport, this function will return another ID of the airport closest to it that can be flown to from the given airport.
 * 
 * @param id Integer ID of the airport which will be used to find the nearest airport.
 */
int Graph::closestAirport(int id) {
    std::queue<int> q;
    std::unordered_set<int> visited;
    int mindist = INT32_MAX;
    double id_lat = amap_.at(id)->getLocation().first * M_PI / 180;
    double id_long = amap_.at(id)->getLocation().second * M_PI / 180;
    q.push(id);
    int airport_id = -1;
    while(!q.empty()) {
        AirportNode* node = amap_.at(q.front());
        visited.insert(q.front());
        q.pop();

        //Haversine Formula Usage
        double dlat = id_lat - node->getLocation().first * M_PI / 180;
        double dlon = id_long - node->getLocation().second * M_PI / 180;
        double step1 = sin(dlat/2) * sin(dlat/2) + cos(id_lat) * cos(node->getLocation().first * M_PI / 180) * sin(dlon/2) * sin(dlon/2);
        double step2 = abs(2 * asin(sqrt(step1)) * 3956);
        if (step2 < mindist && step2 != 0) {
            mindist = step2;
            airport_id = node->getID();
        }
        for (auto a : node->getNeighbors()) {
            if (visited.find(a) == visited.end()) {
                q.push(a);
            }
        }
    }
    return airport_id;
} 

// FOR TESTING
std::vector<AirportNode*> Graph::getAirports() {
    std::vector<AirportNode*> a;
    for (auto it = amap_.begin(); it != amap_.end(); ++it) {
        a.push_back(it->second);
    }
    return a;
}