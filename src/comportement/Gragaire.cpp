//
// Created by Lenovo on 2022/11/25.
//

#include "Gragaire.h"
#include <vector>
#include <iostream>
using namespace std;
Gragaire::Gragaire() {
    cout << "create a gregaire behavior" << endl;
}

Gragaire::~Gragaire() {
    cout << "destroying a gregaire behavior" << endl;
}
/*
 * set the bug's direction to be the average direction of its neighbors
 */
void Gragaire::move(Bestiole& b, vector<Bestiole> const& seen_neighbors) {
    auto averageDirection = calculateAverageDirection(seen_neighbors);
    b.setOrientation(averageDirection);
}
/*
 * calculateAverageDirection calculates the average directions of its neighbors bugs
 */
double Gragaire::calculateAverageDirection(vector<Bestiole> const& seen_neighbors) {
    double averageDirection = 0.0;
    for (auto const& neighbor : seen_neighbors) {
        auto orientation = neighbor->getOrientation();
        averageDirection += orientation;
    }
    averageDirection /= seen_neighbors.size();
    return averageDirection;
}