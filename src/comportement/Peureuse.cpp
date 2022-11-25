//
// Created by Lenovo on 2022/11/25.
//

#include "Peureuse.h"
#include <iostream>

using namespace std;


Peureuse::Peureuse() {
    cout << "Create peureuse behavior" << endl;
}

Peureuse::~Peureuse() {
    cout << "Destroy peureuse behavior" << endl;
}

void Peureuse::move(const Bestiole &b, vector<Bestiole> const& seen_neighbors) {
    int neighbor_number = seen_neighbors.size();
    if (neighbor_number > MAX_NEIGHBOR) {
        double new_direction = b.getOrientation() * -1;
        double new_vitesse = ESCAPE_VITESSE;
        b.setOrientation(new_direction);
        b.setVitesse(new_vitesse);
    } else {
        new_vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
        b.setVitesse(new_vitesse);
    }
}