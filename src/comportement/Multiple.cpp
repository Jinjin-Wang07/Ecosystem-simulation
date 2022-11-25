#include "Multiple.h"
#include <algorithm>
using namespace std;

Multiple::Multiple() {
    cout << "Create multiple behavior" << endl;
}
}

Multiple::~Multiple() {
    cout << "Destroy multiple behavior" << endl;
}
void Multiple::move(const Bestiole &b, vector<Bestiole> const& seen_neighbors) {
    random_shuffle(comportements.begin(), comportements.end())
}
