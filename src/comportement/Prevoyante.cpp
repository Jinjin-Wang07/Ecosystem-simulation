#include "Prevoyante.h"
#include "../bestiole/Bestiole.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

Prevoyante::Prevoyante() { cout << "Create prevoyante behavior" << endl; }

Prevoyante::~Prevoyante() { cout << "Destroy prevoyante behavior" << endl; }

void Prevoyante::move(Bestiole &b,
                      vector<Bestiole const *> const &seen_neighbors) {
  if (seen_neighbors.empty()) {
    return nullptr;
  }
  for (auto neighbor : seen_neighbors) {
    auto directionX =
        neighbor->getCoordinates().first - b.getCoordinates().first;
    auto directionY =
        neighbor->getCoordinates().second - b.getCoordinates().second;
    prevoyanteDirection = atan2(-directionY, directionX);
    neighborDirection = neighbor->getOrientation();
    if (prevoyanteDirection == neighborDirection) {
      orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
      b.setOrientation(direction);
    }
  }
}

unique_ptr<IComportement> Prevoyante::clone() const {
  return unique_ptr<IComportement>(new Prevoyante());
}