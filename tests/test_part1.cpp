#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "airportnodes.h"
#include "graph.h"

using namespace std;


TEST_CASE("addElements1", "[weight=10][part1]")
{
	AirportNode airnode = AirportNode(1, pair<double, double>(123.233, 283.222), unordered_set<int>());
    airnode.addNeighbor(2);
    REQUIRE(airnode.getNeighbors().size() == 1);

}

TEST_CASE("Airports File Parse and Storage", "[weight=10][part1]")
{
	Graph a;

    a.allAirports("../tests/small_airports.csv");
    vector<AirportNode*> vect = a.getAirports();
    
    REQUIRE(vect.size() == 4);
    REQUIRE(vect.at(0)->getID() == 8810);
    REQUIRE(vect.at(1)->getID() == 3127);
    REQUIRE(vect.at(2)->getID() == 26);
    REQUIRE(vect.at(3)->getID() == 507);
    
}

TEST_CASE("Medium Airports File Parse and Storage", "[weight=10][part1]")
{
    Graph a;

    a.allAirports("../tests/med_airports.csv");
    vector<AirportNode *> vect = a.getAirports();
    REQUIRE(vect.size() == 148);
    for (AirportNode *node : vect)
    {
        if (node->getID() == 149)
            REQUIRE(node->getLocation() == pair<double, double>(48.20610046386719, -78.83560180664062));
    }
}

TEST_CASE("Large Airports File Parse and Storage", "[weight=10][part1]")
{
    Graph a;

    a.allAirports("../tests/large_airports.csv");
    vector<AirportNode *> vect = a.getAirports();
    REQUIRE(vect.size() == 7698);

    for (AirportNode *node : vect)
    {
        if (node->getID() == 641)
            REQUIRE(node->getLocation() == pair<double, double>(68.491302490234, 16.678100585938));
    }
}

TEST_CASE("Small Routes File Parse and Storage", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/small_airports.csv");
    a->createGraph("../tests/small_routes.csv");
    vector<AirportNode *> vect = a->getAirports();

    REQUIRE(a->flightPathExists(507, 8810) == true);
}

TEST_CASE("Strongly Connected Components Small", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/small_airports.csv");
    a->createGraph("../tests/small_routes2.csv");

    vector<AirportNode *> vect = a->getAirports();
    auto vec1 = a->getStronglyConnected(507);
    REQUIRE(vec1.size() == 3);
    auto vec2 = a->getStronglyConnected(8810);
    REQUIRE(vec2.size() == 1);
    auto vec3 = a->getStronglyConnected(3830);
    REQUIRE(vec3.size() == 1);

}

TEST_CASE("Strongly Connected Components Large", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/large_airports.csv");
    a->createGraph("../tests/large_routes.csv");

    vector<AirportNode *> vect = a->getAirports();
    auto vec1 = a->getStronglyConnected(507);
    REQUIRE(vec1.size() == 3147);
    auto vec2 = a->getStronglyConnected(1038);
    REQUIRE(vec2.size() == 3147);

}

TEST_CASE("Shortest Route Large", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/large_airports.csv");
    a->createGraph("../tests/large_routes.csv");

    vector<AirportNode *> vect = a->getAirports();
    REQUIRE(a->flightPathExists(3830, 3484) == true);
    
    auto vec1 = a->shortestPath(3830,3484);
    REQUIRE(vec1[1] == 3830);
    REQUIRE(vec1[0] == 3484);
   
    auto vec2 = a->shortestPath(5726, 3678);
    REQUIRE(vec2[0] == 3678);
    REQUIRE(vec2[1] == 5726);
    
    auto vec3 = a->shortestPath(8949, 3156);
    REQUIRE(vec3[0] == 3156);
    REQUIRE(vec3[1] == 3024);
    REQUIRE(vec3[2] == 8949);

    
    REQUIRE(a->shortestPath(932, 2039) == vector<int>());
}

TEST_CASE("Large Routes File Parse and Storage", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/large_airports.csv");
    a->createGraph("../tests/large_routes.csv");

    vector<AirportNode *> vect = a->getAirports();
    REQUIRE(a->flightPathExists(3830, 3484) == true);
    REQUIRE(a->flightPathExists(4235, 3860) == false);
    REQUIRE(a->flightPathExists(4029, 244) == true);
    REQUIRE(a->flightPathExists(8949, 3156) == true);
    REQUIRE(a->flightPathExists(3156, 8949) == true);



}




