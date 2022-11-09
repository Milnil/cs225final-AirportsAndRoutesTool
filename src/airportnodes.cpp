#include "airportnodes.h"

AirportNode::AirportNode() {}
AirportNode::AirportNode(int id, pair<double, double> location, vector<AirportNode> neighbors) {
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
void AirportNode::addNeighbor(AirportNode neighbor) {
    neighbors_.push_back(neighbor);
}
void AirportNode::setLocation(double latitude, double longitude) {
    location_ = pair<double, double>(latitude, longitude);
}

vector<AirportNode> AirportNode::getNeighbors() {
    return neighbors_;
}