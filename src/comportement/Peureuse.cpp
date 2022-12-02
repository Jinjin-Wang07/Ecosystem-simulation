//
// Created by Lenovo on 2022/11/25.
//

#include "Peureuse.h"
#include "../bestiole/Bestiole.h"
#include "../constants.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

Peureuse::Peureuse() { cout << "Create peureuse behavior" << endl; }

Peureuse::~Peureuse() { cout << "Destroy peureuse behavior" << endl; }

void Peureuse::move(Bestiole &b,
                    vector<Bestiole const *> const &seen_neighbors) {
  int neighbor_number = seen_neighbors.size();
  auto orientation = b.getOrientation();
  auto should_flee = neighbor_number > 2;
  if (fleeing && !should_flee) {
    fleeing = false;
    b.setVitesse(3.0);
  } else if (!fleeing && should_flee) {
    fleeing = true;
    b.setOrientation(orientation + M_PI);
    b.setVitesse(MAX_VITESSE);
  }
}

unique_ptr<IComportement> Peureuse::clone() const {
  return unique_ptr<IComportement>(new Peureuse());
}