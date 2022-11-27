//
// Created by Lenovo on 2022/11/25.
//

#include "Gragaire.h"
#include "../bestiole/Bestiole.h"
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

Gragaire::Gragaire() {
    cout << "create a gregaire behavior" << endl;
}

Gragaire::~Gragaire() {
    cout << "destroying a gregaire behavior" << endl;
}

void Gragaire::move(Bestiole& b, vector<Bestiole const*> const& seen_neighbors) {
    double orientation = b.getOrientation();
    while (orientation < 0.0) {
        orientation += 2*M_PI;
    }

    while (orientation >= 2*M_PI) {
        orientation -= 2*M_PI;
    }

    auto averageOrientation = calculateAverageDirection(orientation, seen_neighbors);
    orientation -= sin(orientation - averageOrientation) * 0.1;

    b.setVitesse(5);
    b.setOrientation(orientation);
}

unique_ptr<IComportement> Gragaire::clone() const {
    return unique_ptr<IComportement>(new Gragaire());
}

double Gragaire::calculateAverageDirection(double orientation, vector<Bestiole const*> const& seen_neighbors) {
    double averageDirection = 0.0;
    for (auto const& neighbor : seen_neighbors) {
        auto orientation = neighbor->getOrientation();
        while (orientation < 0.0) {
            orientation += 2*M_PI;
        }

        while (orientation >= 2*M_PI) {
            orientation -= 2*M_PI;
        }
        averageDirection += orientation;
    }
    //std::cout << "computing avg of " << (1 + seen_neighbors.size()) << " values" << std::endl;
    averageDirection = ((averageDirection + orientation) / (1 + seen_neighbors.size()));
    return averageDirection;
}