#include "Kamikaze.h"
#include "../bestiole/Bestiole.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

Kamikaze::Kamikaze() { cout << "create a behavior kamikaze" << endl; }
Kamikaze::~Kamikaze() { cout << "destroying a behavior kamikaze" << endl; }
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
  b.setVitesse(1 + distance * 0.1);
}
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
