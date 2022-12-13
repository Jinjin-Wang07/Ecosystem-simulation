#include "Kamikaze.h"
#include "../../include/LogUtil.h"
#include "../bestiole/Bestiole.h"

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

Kamikaze::Kamikaze() { LOG_DEBUG("Create a kamikaze behavior par default"); }
Kamikaze::~Kamikaze() {
  LOG_DEBUG("Destroying a kamikaze behavior par default");
}
/*
 * the bug adjusts its direction to its nearest neighbor.
 */
void Kamikaze::move(Bestiole &b,
                    vector<Bestiole const *> const &seen_neighbors) {
  auto attractedNeighbor = getAttractedNeighbor(b, seen_neighbors);
  if (!attractedNeighbor) {
    b.setVitesse(3);
    return;
  }
  auto directionX =
      attractedNeighbor->getCoordinates().first - b.getCoordinates().first;
  auto directionY =
      attractedNeighbor->getCoordinates().second - b.getCoordinates().second;
  auto distance = sqrt(directionX * directionX + directionY * directionY);
  auto newDirection = atan2(-directionY, directionX);
  auto direction = b.getOrientation();
  direction -= sin(direction - newDirection) * 0.1;
  b.setOrientation(direction);
  b.setVitesse(max(1 + distance * 0.1, b.get_max_vitesse()));
}
/*
 * calculate the distance between the bug and its neighbors and return the
 * nearest bug
 */
Bestiole const *
Kamikaze::getAttractedNeighbor(const Bestiole &b,
                               vector<Bestiole const *> const &seen_neighbors) {
  if (seen_neighbors.empty()) {
    return nullptr;
  }
  vector<double> distances;
  for (auto neighbor : seen_neighbors) {
    double dis =
        (neighbor->getCoordinates().first - b.getCoordinates().first) *
            (neighbor->getCoordinates().first - b.getCoordinates().first) +
        ((neighbor->getCoordinates().second - b.getCoordinates().second)) *
            ((neighbor->getCoordinates().second - b.getCoordinates().second));
    dis = sqrt(dis);
    distances.push_back(dis);
  }
  int indexOfAttractedNeighbor =
      min_element(begin(distances), end(distances)) - begin(distances);
  auto attractedNeighbor = seen_neighbors[indexOfAttractedNeighbor];
  return attractedNeighbor;
}

unique_ptr<IComportement> Kamikaze::clone() const {
  return unique_ptr<IComportement>(new Kamikaze());
}
// namespace std;
