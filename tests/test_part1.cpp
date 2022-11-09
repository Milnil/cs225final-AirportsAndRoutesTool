#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "airportnodes.h"

using namespace std;


TEST_CASE("addElements1", "[weight=10][part1]")
{
	AirportNode airnode = AirportNode(1, pair<double, double>(123.233, 283.222), vector<AirportNode>());
    airnode.addNeighbor(AirportNode());
    REQUIRE(airnode.getNeighbors().size() == 1);

}
