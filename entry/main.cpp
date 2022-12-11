#include <iostream>
#include "../src/airportnodes.h"
#include "../src/graph.h"

using namespace std;

int main()
{
    cout << "Welcome to the our Airport data based program" << endl;
    cout << "To exit our program at anyime just enter 0 as your input" << endl;
    cout << "To use one of our algorithms on a data set you have to first acquire a dataset with a structure similar to the ones available at https://openflights.org/data.html" << endl;
    cout << "Enter the file_path to your data set of airports: ";
    string file_path;
    cin >> file_path;
    if (file_path == "0")
    {
        cout << "Bye Bye :)" << endl;
        return 0;
    }
    cout << endl;
    Graph a;
    a.allAirports(file_path);
    cout << "Enter the file_path to your data set of routes: ";
    cin >> file_path;
    if (file_path == "0")
    {
        cout << "Bye Bye :)" << endl;
        return 0;
    }
    cout << endl;
    a.createGraph(file_path);
    string stop = "4";
    while (stop != "0")
    {

        cout << "1: Flight Path Exists" << endl;
        cout << "2: Shortest Path" << endl;
        cout << "3: Get Strongly Connected" << endl;
        cout << "Input the number of the function you would like to use: ";
        cin >> stop;
        cout << endl;
        if (stop == "1")
        {
            string f;
            cout << "What's the ID of the source airport?" << endl;
            cin >> f;
            int id1 = stoi(f);
            cout << "What's the ID of the destination airport?" << endl;
            cin >> f;
            int id2 = stoi(f);
            bool value = a.flightPathExists(id1, id2);
            if (value)
            {
                cout << "There is a route from source to destination" << endl;
            }
            else
            {
                cout << "There is no route from source to destination" << endl;
            }
        }
        else if (stop == "2")
        {
            string f;
            cout << "What's the ID of the source airport?" << endl;
            cin >> f;
            int id1 = stoi(f);
            cout << "What's the ID of the destination airport?" << endl;
            cin >> f;
            int id2 = stoi(f);
            vector<int> value = a.shortestPath(id1, id2);
            if (!value.empty())
            {
                cout << "The shortest route is through the following airport IDs: ";
                for (const auto val : value)
                {
                    cout << val << " ";
                }
                cout << endl;
            }
            else
            {
                cout << "There is no route from source to destination" << endl;
            }
        }
        else if (stop == "3")
        {
            string f;
            cout << "What's the ID of the airport?" << endl;
            cin >> f;
            int id1 = stoi(f);

            vector<int> value = a.getStronglyConnected(id1);
            if (!value.empty())
            {
                cout << "Here are the following strongly connected airports in the graph: ";
                for (const auto val : value)
                {
                    cout << val << " ";
                }
                cout << endl;
            }
            else
            {
                cout << "This is not a valid airport ID" << endl;
            }
        }
        else if (stop == "0")
        {
            cout << "Bye Bye :)" << endl;
            return 0;
        }
        else
        {
            cout << "Sorry but I don't think your input is valid, how about you give it another shot?" << endl;
        }
    }

    return 0;
}
