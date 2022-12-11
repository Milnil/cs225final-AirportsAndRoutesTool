# CS225 Final Project: Airport Navigation Tool
### [Presentation Video](URL)
## Data
We will be using the datasets on [OpenFlights](https://openflights.org/data.html). Specifically, we will be utilizing the airport dataset and route dataset in our project.
* [OpenFlights Airport Nodes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat)
* [OpenFlights Route Nodes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat)

## Repo Structure
### Deliverables
* All major files that contain our functions and classes are in the [src](https://github.com/Milnil/cs225final-nerds/tree/main/src) directory.
* Datasets are stored as csv files in `/tests`
* Project report, development log, contract, etc. are in `/documents`

## Running Instructions
Make sure you are running the program in Docker. If not, follow [this guide](https://courses.engr.illinois.edu/cs225/sp2022/resources/own-machine/) to get started.

To use our Airport Navigation Tool, run the following in the root directory of the repository:
```
mkdir build
cd build
```

We call all functions in main for you. The required inputs for each of the functionality are as follows:

### Executables
* Dijkstra’s
  * Input:
  * Output:
* BFS
  * Input:
  * Output:
* Strongly Connected Components
  * Input:
  * Output:

### Tests
To run the test cases, run `make test` then `./test` in the root directory.

We constructed several small to medium sized datasets in `/tests` directory. What else did we test for?

In addition to the above functions called in main, you can also refer to the input and output definitions in the comments for each small function in the `graph.h`.  

## Team
*  Ayush Basu (` ayushb3 `)
*  Jessica Ho (` jmho3 `)
*  Milind Philar (` mphilar2 `)
*  Joy Wan (` joywan2 `)
