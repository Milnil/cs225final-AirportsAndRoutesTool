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
    // ifstream file;
    // vector<string> row;
    // string line, word;
    // file.open(airports_filename);
    // if (file.is_open()) {
    //     while(getline(file, line)) {
    //         row.clear();
    //         stringstream str(line);
    //         while (getline(str, word, ',')) {
    //             row.push_back(word);
    //         }
    //         if (row.at(0).empty() || row.at(6).empty() || row.at(7).empty())
    //         {
    //             continue;
    //         }
    //         else
    //         {
    //             try
    //             {
    //                 AirportNode *a = new AirportNode(stoi(row.at(0)), pair<double, double>(stod(row.at(6)), stod(row.at(7))), unordered_set<int>());
    //                 amap_.insert(pair<int, AirportNode *>(stoi(row.at(0)), a));
    //             }
    //             catch (const std::invalid_argument &)
    //             {
    //                 cout << "Argument is invalid\n";
    //                 cout << row.at(6) << ',' << row.at(7) << endl;
    //             }
    //             catch (const std::out_of_range &)
    //             {
    //                 cout << "Argument is out of range for a double\n";
    //             }
    //             catch (exception &e)
    //             {
    //                 cout << "Standard exception: " << e.what() << endl;
    //             }
    //         }
    //     }
    // }
    // else
    // {
    //     exit(EXIT_FAILURE);
    // }

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
            visited_map_.insert(pair<int, bool>(stoi(row.at(0)), false));
            vertices_++;
        }
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
                // cout << "Key is not in the map " << endl;
            }
        }
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
            // cout << "Key is not in the map " << endl;
        }
    }
    cout << "errorCount from closestNeighbor: " << errorCount << endl;

    return false;
}

// FOR TESTING
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
    AirportNode *node = amap_.at(id2);
    double id_lat = amap_.at(id1)->getLocation().first * M_PI / 180;
    double id_long = amap_.at(id1)->getLocation().second * M_PI / 180;
    double dlat = id_lat - node->getLocation().first * M_PI / 180;
    double dlon = id_long - node->getLocation().second * M_PI / 180;
    double step1 = sin(dlat / 2) * sin(dlat / 2) + cos(id_lat) * cos(node->getLocation().first * M_PI / 180) * sin(dlon / 2) * sin(dlon / 2);
    double step2 = abs(2 * asin(sqrt(step1)) * 3956);
    return step2;
}