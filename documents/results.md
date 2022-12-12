# CS225 Final Report
## Algorithm Overview

### BFS
The breadth-first search algorithm is given both a source and destination Airport ID and returns whether or not there is a flight route between the two airports. The runtime of this function will be O(V+E) where V is the number of vertices and E is the number of edges.

We confirmed the correctness of our algorithm by creating tests between airports that we could manually check if they had a route between them. Our tests also included cases for disconnected graphs and on faulty inputs to confirm that the algorithm would work on edge cases.

Examples:
```
Checking between O’Hare to LAX
1: Flight Path Exists
2: Shortest Path
3: Get Strongly Connected
Input the number of the function you would like to use: 1

What's the ID of the source airport?
3830 
What's the ID of the destination airport?
3484
There is a route from source to destination

Checking with a ID that does not exist in the dataset
```
1: Flight Path Exists
2: Shortest Path
3: Get Strongly Connected
Input the number of the function you would like to use: 1

What's the ID of the source airport?
9077
What's the ID of the destination airport?
3830
There is no route from source to destination

```


### Dijkstra’s Algorithm
Our implementation of Djikstra’s algorithm is given both a source and destination Airport ID and returns a vector containing the shortest path between the two airports. This can allow a user to find a series of airport routes that will travel the shortest distance. The runtime of this function will be O((V+E)*logV) where V is the number of vertices and E is the number of edges since we used an adjacency list representation where each node has a set of adjacent neighbors.


We confirmed that the algorithm is working correctly by creating tests that we were able to manually check. We generated many different scenarios including some where we knew there was no path between the two nodes. Our algorithm handled all of these algorithms correctly as intended.

Example:
```
1: Flight Path Exists
2: Shortest Path
3: Get Strongly Connected
Input the number of the function you would like to use: 2

What's the ID of the source airport?
8949
What's the ID of the destination airport?
3156
The shortest route is through the following airport IDs: 3156 3024 8949
```



### Strongly Connected Components
The Strongly Connected Components algorithm is given an airport ID and returns a vector of airport IDs, including the input ID, that are considered strongly connected components. 

We confirmed that our algorithm is working properly by creating tests where we made sure that the size of our output was indeed correct and on a small data set we could make sure that the airports were indeed strongly connected components. The worst case runtime of this function is O(V+E) where V is the number of airports in the graph, and E is the number of routes between airports in the graph.

Example: 

```
1: Flight Path Exists
2: Shortest Path
3: Get Strongly Connected
Input the number of the function you would like to use: 3

What's the ID of the airport?
507
Here are the following strongly connected airports in the graph: 3127 26 507
```


## Leading Question
### We are hoping to provide travelers with a navigation tool that can efficiently minimize the path to travel from one position to another, potentially with multiple stops in between.

BFS, for instance, allows travelers to check if they can fly from one airport to another. Because not all airports are connected to each other, travelers need to know if it is possible to fly from their departure and destination airports before planning their trip. Furthermore, Dijkstra’s provides travelers with a list of airport IDs that represents a path with the shortest distance from one airport to another. Another tool to help travelers plan their trips is with Strongly Connected Components. The algorithm produces a list of airports that can be flown from a source airport, so travelers can know the possible places to travel to if they wanted to start planning a trip.

One of the discoveries we made while implementing the shortest path algorithm was the use of the Haversine distance formula. We initially planned on using Euclidean distance to calculate the shortest distance between two airports, but this did not account for the curvature of the earth. Thus, the Haversine formula determines the distance between two points on a sphere given their longitude and latitudes, which would best fit our algorithm to provide the shortest path between two airports. Additionally, our original idea for our BFS algorithm required iterating through every single airport node and we discovered that this took an impossibly long time when it came to our large data set. This is why we decided to change it so that it was way more efficient and could be used in our other methods as well for error detection of invalid inputs. Lastly, we discovered that Strongly Connected Components would greatly benefit travelers if they did not know where they could travel to from a nearby airport. 

