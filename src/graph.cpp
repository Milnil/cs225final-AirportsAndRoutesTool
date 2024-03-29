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

void Graph::allAirports(string airports_filename)
{
    std::ifstream reader(airports_filename);
    vector<string> row;

    if (reader.is_open())
    {
        string line;
        while (std::getline(reader, line))
        {
            row.clear();
            int start = 0;
            int next = 0;
            bool inQuotes = false;
            for (unsigned i = 0; i < line.size(); i++)
            {
                char ch = line[i];
                if (ch == '"')
                    inQuotes = !inQuotes;
                else if (ch == ',' && !inQuotes)
                {

                    row.push_back(line.substr(start, i - start));
                    start = i + 1;
                }
            }
            unordered_set<int> neighbors = unordered_set<int>();
            neighbors.reserve(4000);

            AirportNode *a = new AirportNode(stoi(row.at(0)), pair<double, double>(stod(row.at(6)), stod(row.at(7))), neighbors);
            amap_.insert(pair<int, AirportNode *>(stoi(row.at(0)), a));
            visited_map_.insert(pair<int, int>(stoi(row.at(0)), false));
            dist_map_.insert(pair<int, double>(stoi(row.at(0)), 0));
            vertices_++;
        }
    }
    else
    {
        std::cout << "FILE COULD NOT BE OPENED" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Graph::createGraph(string routes_filename)
{
    fstream file(routes_filename, ios::in);
    vector<string> row;
    string line, word;
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
                continue;
            }
        }
    }
    else
    {
        std::cout << "FILE COULD NOT BE OPENED" << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool Graph::flightPathExists(int source_id, int dest_id)
{

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    std::queue<int> q;

    q.push(source_id);
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
            q.pop();
            continue;
        }
    }

    return false;
}

vector<int> Graph::shortestPath(int source_id, int dest_id)
{
    if (!flightPathExists(source_id, dest_id))
    {
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
    parents.insert(pair<int, int>(source_id, -1));

    for (int i = 1; i < vertices_; i++)
    {
        int nearest = -1;
        double shortestDist = std::numeric_limits<double>::max();
        for (auto it = dist_map_.begin(); it != dist_map_.end(); it++)
        {

            if (!visited_map_[it->first] && dist_map_[it->first] < shortestDist)
            {
                nearest = it->first;
                shortestDist = dist_map_[it->first];
            }
        }
        visited_map_[nearest] = true;
        std::unordered_set<int> neighbors;
        if (amap_.find(nearest) != amap_.end())
        {
            for (int neighbor : amap_[nearest]->getNeighbors())
            {
                double dist = getHaversineDistance(nearest, neighbor);
                if (dist == -1)
                {
                    continue;
                }
                if (dist > 0 && ((shortestDist + dist) < dist_map_[neighbor]))
                {
                    parents[neighbor] = nearest;
                    dist_map_[neighbor] = shortestDist + dist;
                }
            }
        }
        for (int neighbor : neighbors)
        {
            double dist = getHaversineDistance(nearest, neighbor);
            if (dist == -1)
            {
                continue;
            }
            if (dist > 0 && ((shortestDist + dist) < dist_map_[neighbor]))
            {
                parents[neighbor] = nearest;
                dist_map_[neighbor] = shortestDist + dist;
            }
        }
    }

    int curr = parents[dest_id];
    vector<int> final_path;
    final_path.push_back(dest_id);
    while (curr != -1)
    {
        final_path.push_back(curr);

        curr = parents[curr];
    }
    return final_path;
}

void Graph::stronglyFormer(int id, std::unordered_map<int, bool> &visited, std::vector<int> &ids, std::unordered_map<int, unordered_set<int>> &bmap)
{
    visited[id] = true;
    ids.push_back(id);

    for (auto node : bmap[id])
    {
        if (visited.find(node) == visited.end())
        {
            continue;
        }
        if (!visited[node])
        {
            stronglyFormer(node, visited, ids, bmap);
        }
    }
}

void Graph::stronglyHelper(int id, std::unordered_map<int, bool> &visited, stack<int> &stack)
{
    visited[id] = true;
    for (auto neighbor : amap_[id]->getNeighbors())
    {
        if (visited.find(neighbor) == visited.end())
        {
            continue;
        }
        if (!visited[neighbor])
        {
            stronglyHelper(neighbor, visited, stack);
        }
    }
    stack.push(id);
}

std::vector<int> Graph::getStronglyConnected(int id)
{
    stack<int> stack;
    unordered_map<int, unordered_set<int>> bmap;
    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        if (it->second == false)
        {
            stronglyHelper(it->first, visited_map_, stack);
        }
    }

    for (auto it = amap_.begin(); it != amap_.end(); it++)
    {
        for (auto neighbor : it->second->getNeighbors())
        {
            if (bmap.find(neighbor) != bmap.end())
            {
                bmap[neighbor].insert(it->first);
            }
            else
            {
                bmap[neighbor] = unordered_set<int>({it->first});
            }
        }
    }

    for (auto it = visited_map_.begin(); it != visited_map_.end(); it++)
    {
        it->second = false;
    }

    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();
        std::vector<int> ids;
        if (!visited_map_[node])
        {
            stronglyFormer(node, visited_map_, ids, bmap);
        }
        if (visited_map_[id])
        {
            return ids;
        }
    }

    return std::vector<int>({id});
}

std::vector<AirportNode *> Graph::getAirports()
{
    std::vector<AirportNode *> a;
    for (auto it = amap_.begin(); it != amap_.end(); ++it)
    {
        a.push_back(it->second);
    }
    return a;
}

double Graph::getHaversineDistance(int id1, int id2)
{
    if (amap_.find(id1) == amap_.end() || amap_.find(id2) == amap_.end())
    {
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
