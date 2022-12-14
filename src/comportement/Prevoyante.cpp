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

  // This method isn't finished.
  return;

  auto b_ori = b.getOrientation();
  auto b_vitesse = b.get_vitesse();
  auto b_coord = b.getCoordinates();
  double distance_min = static_cast<double>(INFINITY);
  Bestiole const* closest_neighbor = nullptr;
  if (seen_neighbors.empty()) {
    b.setVitesse(0.6 * b.get_max_vitesse());
    b.setOrientation(b_ori);
  }
  for (auto neighbor : seen_neighbors) {
    auto neighbor_ori = neighbor->getOrientation();
    auto neighbor_coord = neighbor->getCoordinates();
    auto neighbor_vitesse = neighbor->get_vitesse();
    // next round distance
    auto next_distance_x = neighbor_coord.first +
                           neighbor_vitesse * cos(neighbor_ori) -
                           b_coord.first + b_vitesse * cos(b_ori);
    auto next_distance_y = neighbor_coord.second +
                           neighbor_vitesse * sin(neighbor_ori) -
                           b_coord.second + b_vitesse * sin(b_ori);
    auto next_distance = sqrt(next_distance_x * next_distance_x +
                              next_distance_y * next_distance_y);
    if (next_distance < distance_min) {
      distance_min = next_distance;
      closest_neighbor = neighbor;
    }
  }
  if (closest_neighbor) {
    b.setOrientation(b_ori + M_PI);
  }
}

unique_ptr<IComportement> Prevoyante::clone() const {
  return unique_ptr<IComportement>(new Prevoyante());
}