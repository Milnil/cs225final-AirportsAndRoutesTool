## Leading Question 

We are hoping to provide travelers with a navigation tool that can efficiently minimize the path to travel from one position to another, potentially with multiple stops in between.


Closest Airport: From the user’s inputted starting location and desired destination, the application will determine the nearest airport from the starting location to depart from as well as the nearest airport to the destination to arrive at. We will do this by implementing a single breadth-first-search while keeping track of both the nearest beginning and ending airports. This portion of the application will focus on processing the airport data, specifically the longitude and latitude data. The nodes of our graph will be the latitude and longitude coordinates, the edges are the distances between nodes’ coordinates, and the graph is unweighted.

Shortest Path between Two Airports: When travelers want to fly from one airport to another due to continuous traveling, it becomes useful to know what the shortest path between two specific airports is. To achieve this, our application will use the A* Search algorithm to find the shortest path from a specified origin airport to a specified destination airport. This implementation will focus on processing the route data. We will represent the graph using an adjacency matrix between airports.


Shortest Path from One Airport to All Other Airports: Sometimes a specified airport destination is not necessary when users may be more interested in understanding the shortest path from an origin to all other possible airports. To find this shortest path, we will implement Dijkstra's algorithm, which produces a shortest-path tree that fixes a single node as the source node and determines the shortest path from the source to all the other nodes in the graph. The source node of our graph will be the origin, and all the other nodes in the graph will be all the other possible airports. An adjacency matrix between airports will be used to represent the graph. 


## Dataset Acquisition
We will be using the datasets on OpenFlights (https://openflights.org/data.html). Specifically, we will be utilizing the airport database and route database in our project. The airport dataset will help us find the closest airport based on a user’s longitude and latitude points. The route database will help us find a path between two airports and also the path containing multiple locations and airports based on a user’s desired destinations.

## Data Format
Our dataset consists of two parts and is from OpenFlights. One of those parts is a set of airports where we will be using the different latitudes and longitudes of said airports. We will also be using the route data to create the edges on our graph which will be the flights that leave one airport and go to another. The airport database has the airport’s ID as an integer, longitude with decimal degrees to six significant digits where negative is West and positive is East, and latitude with six significant digits where negative is South and positive is North. For the routes dataset, we will be using the source airport and destination airport data to create our edges which will be in the form of airport IDs that are 3 characters.

## Data Correction
Since the database containing the routes of airports is a directed graph, this means there is a possibility that a path does not exist between the starting location and ending location or a path between the ending location and starting location. If this is the case, we will tell the user to input alternative locations that would result in an existing path. Specifically, we will return a message to the user about this issue.

We will also check that the latitudes and longitudes in the dataset are valid numbers and inside the range. When going through the route data we will make sure that the airport IDs are valid otherwise no edge will be created since an edge has to be between two nodes. We will parse the data line by line since the data is in a CSV and check each value before storing it to make sure they are valid.

## Data Storage
We will be creating one graph to be used in the first part of our application which will save 1 integer as the airport ID, and 2 doubles which will represent the location of the airport. The second graph will be used in parts two and three of our application which will also store 1 integer as the airport ID, as well as a vector of nodes that are the neighbors of the airport. Since we will have N nodes that each have a vector that can possibly point to N-1 other nodes our storage cost estimate would be O(N^2).

## Algorithm 
Function Inputs:
We will have to convert our airport and flight data into nodes and edges on a graph. We will be using the A* algorithm to figure out the shortest path between two locations. The heuristic we will be using in this algorithm is the Haversine distance between nodes. The input for our A* function will simply be two locations in terms of latitude and longitude. We will proceed to find the airports nearest to each of those points and find the shortest path between them. We will also be using Djikstras to create a shortest path tree which will simply take a location and equate it to the nearest airport as a starting point or root for the tree. Our BFS function will take in longitude and latitude and find the nearest airport or the airport with the shortest Haversine distance from the location.
Function Outputs:
Our BFS function will return an airport ID which can be printed. Our A star function will return a string of one or more airport IDs which will be the airports that one will visit on their journey from one location to another. The Dijkstra's function will return a root node to the tree of shortest paths to other airports. 
Function Efficiency:
We aim for the time complexity of our Djikstra’s function to be at most O((E)+Vlog(V)) where E is the number of edges and V is the number of airports where N is our number of airports and the space complexity to be O(N). The time complexity of our A* algorithm should be less than our Djikstra’s because of our heuristic so we aim for less than O((E)+Vlog(V)) and the space complexity should be less than O(N). The hope is also for our BFS function to have a time complexity under O(N + E) where N is the number of airports and E is the number of edges and the space complexity should be less than or equal to O(N).


## Timeline

Week 1 (Nov 7)
Set up a node class for airport dataset
Construct a graph containing all the airports and their respective IDs and coordinates
Create a function that takes in user input to start closest airport implementation
Create a function that parses through airport dataset and route dataset

Week 2 (Nov 14)
Note: Mid-project check-in
Implement closest airport using BFS algorithm
Make test cases for BFS algorithm
Start implementing A star (shortest path) algorithm

Week 3 (Nov 21) **Fall break

Week 4 (Nov 28)
Finish shortest path algorithm
Make test cases for shortest path algorithm
Start implementing Dijkstra’s algorithm
Start working on presentation

Week 5 (Dec 5)
Note: Final Deliverables (Dec 8)
Finish Dijkstra’s algorithm that takes multiple locations from user input
Make tests for Dijkstra’s algorithm
Finish presentation
