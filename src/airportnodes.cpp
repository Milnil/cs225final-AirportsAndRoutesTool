#include "airportnodes.h"

AirportNode::AirportNode() {}
AirportNode::AirportNode(int id, pair<double, double> location, unordered_set<int> neighbors) {
    id_ = id;
    location_ = location;
    neighbors_ = neighbors;
}
pair<double, double> AirportNode::getLocation() {
    return location_;
}
int AirportNode::getID() {
    return id_;
}
void AirportNode::setID(int id) {
    id_ = id;
}
void AirportNode::addNeighbor(int neighbor) {
    neighbors_.insert(neighbor);
}
void AirportNode::setLocation(double latitude, double longitude) {
    location_ = pair<double, double>(latitude, longitude);
}

unordered_set<int> AirportNode::getNeighbors() {
    return neighbors_;
}