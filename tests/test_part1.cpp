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

TEST_CASE("Airports File Parse", "[weight=10][part1]")
{
	Graph a;
    
    a.allAirports("/workspaces/cs225/cs225final-nerds/tests/airports1.txt");
    vector<AirportNode*> vect = a.getAirports();
    
    REQUIRE(vect.size() == 4);
    REQUIRE(vect.at(0)->getID() == 8810);
    REQUIRE(vect.at(1)->getID() == 3127);
    REQUIRE(vect.at(2)->getID() == 26);
    
}
