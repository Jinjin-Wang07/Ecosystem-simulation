#include "Multiple.h"
#include <algorithm>
using namespace std;

Multiple::Multiple() { cout << "Create multiple behavior" << endl; }
}

Multiple::~Multiple() { cout << "Destroy multiple behavior" << endl; }

void Multiple::move(const Bestiole &b, vector<Bestiole> const &seen_neighbors) {
    int randomBehaviourIndex = rand() % 4;
    comportements[randomBehaviourIndex] ->move(&b, &seen_neighbors);
}
