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
TEST_CASE("Large Routes File Parse and Storage", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/large_airports.csv");
    a->createGraph("../tests/large_routes.csv");

    vector<AirportNode *> vect = a->getAirports();
    REQUIRE(a->flightPathExists(3830, 3484) == true);
    REQUIRE(a->flightPathExists(4235, 3860) == false);
}

TEST_CASE("Shortest Route", "[weight=10][part1]")
{
    Graph *a = new Graph();
    a->allAirports("../tests/large_airports.csv");
    a->createGraph("../tests/large_routes.csv");

    vector<AirportNode *> vect = a->getAirports();
    REQUIRE(a->flightPathExists(3830, 3484) == true);
    
    for (auto a : a->shortestPath(3830, 3484)) {
        cout << a << endl;
    }
}
