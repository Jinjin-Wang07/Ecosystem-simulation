//
// Created by Lenovo on 2022/11/25.
//

#include "Peureuse.h"
#include "../../include/LogUtil.h"
#include "../bestiole/Bestiole.h"
#include "../constants.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

Peureuse::Peureuse() { LOG_DEBUG("Create peureuse behavior"); }

Peureuse::~Peureuse() { LOG_DEBUG("Destroy peureuse behavior"); }

/*
 * the bug adjusts his direction to the opposite and adjusts his speed to the
 * maximum when the number of his neighbor are more than 2.
 */
void Peureuse::move(Bestiole &b,
                    vector<Bestiole const *> const &seen_neighbors) {
  int neighbor_number = seen_neighbors.size();
  auto orientation = b.getOrientation();
  auto should_flee = neighbor_number > 2;
  if (fleeing && !should_flee) {
    fleeing = false;
    b.setVitesse(b.get_max_vitesse() / 2);
  } else if (!fleeing && should_flee) {
    fleeing = true;
    b.setOrientation(orientation + M_PI);
    b.setVitesse(b.get_max_vitesse());
  }
}

unique_ptr<IComportement> Peureuse::clone() const {
  return unique_ptr<IComportement>(new Peureuse());
}