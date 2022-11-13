#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

// FOR TESTING
std::vector<AirportNode*> Graph::getAirports() {
    std::vector<AirportNode*> a;
    for (auto it = amap_.begin(); it != amap_.end(); ++it) {
        a.push_back(it->second);
    }
    return a;
}