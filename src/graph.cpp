#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <math.h>
#include <limits.h>
#include <limits>
#include <float.h>
#include <stack>


/**
 * Given a file name for a csv file with data on airport nodes from https://openflights.org/data.html, this function populates a map with 
 * the airport nodes and the keys to the aiports are their unique IDs that were assigned to them by openflights. 
 * 
 * @param airports_filename Name of the file which contains the data on airports.
 */
void Graph::allAirports(string airports_filename) {
    std::ifstream reader(airports_filename);
    vector<string> row;

    if (reader.is_open())
    {
        string line;
        while (std::getline(reader, line))
        {
            row.clear(); // read full line
            int start = 0;
            int next = 0;
            bool inQuotes = false;
            for (unsigned i = 0; i < line.size(); i++)
            {
                char ch = line[i]; // iterate through the string
                if (ch == '"')     // toggle flag if we're btw double quote
                    inQuotes = !inQuotes;
                else if (ch == ',' && !inQuotes)
                {
                    // if comma OUTSIDE double quote
                    // keep the field
                    row.push_back(line.substr(start, i - start));
                    start = i + 1; // and start parsing next one
                }
            }
            unordered_set<int> neighbors = unordered_set<int>();
            neighbors.reserve(4000);

            AirportNode *a = new AirportNode(stoi(row.at(0)), pair<double, double>(stod(row.at(6)), stod(row.at(7))), neighbors);
            amap_.insert(pair<int, AirportNode *>(stoi(row.at(0)), a));
            visited_map_.insert(pair<int, int>(stoi(row.at(0)), false));
            dist_map_.insert(pair<int,double>(stoi(row.at(0)), 0));
            vertices_++;
        }
    } else {
        std::cout << "FILE COULD NOT BE OPENED" << std::endl;
        exit(EXIT_FAILURE);
    }
}
/**
 * Given a file name for a csv file with data on airplane routes from https://openflights.org/data.html, this function populates the unordered sets of neighbors
 * that each airport node has.
 *
 * @param routes_filename Name of the file which contains the data on routes.
 */
void Graph::createGraph(string routes_filename)
{
    fstream file(routes_filename, ios::in);
    vector<string> row;
    string line, word;
    int errorCount = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
            {
                row.push_back(word);
            }

            if (row.at(3).at(0) == '\\' || row.at(5).at(0) == '\\')
                continue;
            try
            {

                amap_.at(stoi(row.at(3)))->addNeighbor(stoi(row.at(5)));
                edges_++;
            }
            catch (const std::out_of_range &)
            {
                errorCount++;
                
            }
        }
    } else {
        std::cout << "FILE COULD NOT BE OPENED" << std::endl;
        exit(EXIT_FAILURE);
    }
    cout << "errorCount from createGraph: " << errorCount << endl;
}

/**
 * Given an ID for an airport, this function will return another ID of the airport closest to it that can be flown to from the given airport.
 * 
 * @param id Integer ID of the airport which will be used to find the nearest airport.
 */
bool Graph::flightPathExists(int source_id, int dest_id)
{

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    
    std::queue<int> q;

    q.push(source_id);
    int errorCount = 0;
    while (!q.empty())
    {
        try
        {

            AirportNode *node = amap_.at(q.front());

            visited_map_[q.front()] = true;
            q.pop();

            for (auto a : node->getNeighbors())
            {
                if (a == dest_id)
                    return true;
                if (visited_map_.at(a) == false)
                {
                    q.push(a);
                }
            }
        }

        catch (const std::out_of_range &)
        {
            errorCount++;
        }
    }
    cout << "errorCount from closestNeighbor: " << errorCount << endl;

    return false;
}

/**
 * Given a source node ID and a destination node ID, return the shortest path between the two nodes in a vector of airport IDs
 *
 * @param source_id ID of the airport that you are starting from.
 * @param dest_id ID of the airport that you consider your destination.
 */
vector<int> Graph::shortestPath(int source_id, int dest_id)
{
    // use bfs to confirm there is some path first
    if (!flightPathExists(source_id, dest_id)) {
        return vector<int>();
    }

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    for (auto it = dist_map_.begin(); it != dist_map_.end(); it++)
    {
        it->second = std::numeric_limits<double>::max();
    }


    dist_map_[source_id] = 0;
    unordered_map<int, int> parents;
    parents.insert(pair<int,int>(source_id,-1));
    


    for (int i = 1; i < vertices_; i++) {
        int nearest = -1;
        double shortestDist = std::numeric_limits<double>::max();
        for (auto it = dist_map_.begin(); it != dist_map_.end(); it++)
        {
            
            if (!visited_map_[it->first] && dist_map_[it->first] < shortestDist) {
                nearest = it->first;
                shortestDist = dist_map_[it->first];
            }
        }
        visited_map_[nearest] = true;
        std::unordered_set<int> neighbors;
        if (amap_.find(nearest) != amap_.end()) {
            for (int neighbor : amap_[nearest]->getNeighbors()) {
                double dist = getHaversineDistance(nearest, neighbor);
                if (dist == -1) {
                    continue;
                }
                if (dist > 0 && ((shortestDist + dist) < dist_map_[neighbor])) {
                    parents[neighbor] = nearest;
                    dist_map_[neighbor] = shortestDist + dist;
                }
            }
        }
        for (int neighbor : neighbors) {
            double dist = getHaversineDistance(nearest, neighbor);
            if (dist == -1) {
                continue;
            }
            if (dist > 0 && ((shortestDist + dist) < dist_map_[neighbor])) {
                parents[neighbor] = nearest;
                dist_map_[neighbor] = shortestDist + dist;
            }
        }
    }
    
    int curr = parents[dest_id];
    vector<int> final_path;
    final_path.push_back(dest_id);
    while (curr != -1) {
        final_path.push_back(curr);
        
        curr = parents[curr];
    }
    return final_path;
}

/**
 * A helper method for the Strongly Connected Components Graph method that helps form the vector of components using the transpose of the original graph
 * @param visited map of airport IDs to a boolean value declaring if they were visited or not
 * @param ids Vector of airport IDs that are connected through strongly connected component
 * @param bmap A Map that maps airport ids to an unordered set of airport ids that are the key's neighbors in the transpose
 */
void Graph::stronglyFormer(int id, std::unordered_map<int, bool> &visited, std::vector<int> &ids, std::unordered_map<int, unordered_set<int>> &bmap) {
    visited[id] = true;
    ids.push_back(id);

    for (auto node : bmap[id]) {
        if (visited.find(node) == visited.end()) {
            continue;
        }
        if(!visited[node]) {
            stronglyFormer(node, visited, ids, bmap);
        }
    }
}

/**
 * A helper method for the Strongly Connected Components Graph method that helps create the stack of IDs through using DFS
 * @param id ID of the airport to be checked
 * @param visited map detailing whether a node has been visited or not
 * @param stack stack of airport IDs that is being built
 */
void Graph::stronglyHelper(int id, std::unordered_map<int, bool> &visited, stack<int> &stack) {
    visited[id] = true;
    for (auto neighbor : amap_[id]->getNeighbors()) {
        if (visited.find(neighbor) == visited.end()) {
            continue;
        }
        if(!visited[neighbor]) {
            stronglyHelper(neighbor, visited, stack);
        }
    }
    stack.push(id);
}


/**
 * Gets the strongly connected components on airport nodes graph given a node id using Kosaraju's Algorithm
 * @param id ID of the airport of which the function will return all nodes in its Strongly Connected Component Graph.
 *
 */
std::vector<int> Graph::getStronglyConnected(int id) {
    stack<int> stack;
    unordered_map<int, unordered_set<int>> bmap;
    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        if (it->second == false) {
            stronglyHelper(it->first, visited_map_, stack);
        }
    }


    for (auto it = amap_.begin(); it != amap_.end(); it++)
    {
        for (auto neighbor : it->second->getNeighbors()) {
            if (bmap.find(neighbor) != bmap.end()) {
                bmap[neighbor].insert(it->first);
            } else {
                bmap[neighbor] = unordered_set<int>({it->first});
            }
        }
    }

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        std::vector<int> ids;
        if (!visited_map_[node]) {
            stronglyFormer(node, visited_map_, ids, bmap);
        }
        if (visited_map_[id]) { return ids; }
    }

    return std::vector<int>({id});

}


/**
 * Returns all the airports in the map inside a vector
 */
std::vector<AirportNode *> Graph::getAirports()
{
    std::vector<AirportNode *> a;
    for (auto it = amap_.begin(); it != amap_.end(); ++it)
    {
        a.push_back(it->second);
    }
    return a;
}

/**
 * Calculates the Haversine distance between two airports using the coordinates
 * @param id1 : first airport ID
 * @param id2 : second airport ID
 */
double Graph::getHaversineDistance(int id1, int id2)
{
    if (amap_.find(id1) == amap_.end() || amap_.find(id2) == amap_.end()) {
        return -1;
    }

    AirportNode *node = amap_.at(id2);
    double id_lat = amap_.at(id1)->getLocation().first * M_PI / 180;
    double id_long = amap_.at(id1)->getLocation().second * M_PI / 180;
    double dlat = id_lat - node->getLocation().first * M_PI / 180;
    double dlon = id_long - node->getLocation().second * M_PI / 180;
    double step1 = sin(dlat / 2) * sin(dlat / 2) + cos(id_lat) * cos(node->getLocation().first * M_PI / 180) * sin(dlon / 2) * sin(dlon / 2);
    double step2 = abs(2 * asin(sqrt(step1)) * 3956);
    return step2;
}