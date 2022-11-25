#include "Kamikaze.h"
#include <vector>
#include <cmath>
using namespace std;

Kamikaze::Kamikaze() {
    cout << "create a behavior kamikaze" << endl;
}
Kamikaze::~Kamikaze() {
    cout << "destroying a behavior kamikaze" << endl;
}
void move(const Bestiole & b, vector<Bestiole*>const& seen_neighbors) {
    auto attractedNeighbor = getAttractedNeighbor(b, seen_neighbors);
    
}
Bestiole* getAttractedNeighbor(const Bestiole & b, vector<Bestiole*>const& seen_neighbors) {
    vector<double> distances;
    for (auto neighbor : seen_neighbors) {
        double dis = (neighbor->getCoordinates().first - b.getCoordinates().first) * (neighbor->getCoordinates().first - b.getCoordinates().first)
        + ((neighbor->getCoordinates().second - b.getCoordinates().second))*((neighbor->getCoordinates().second - b.getCoordinates().second));
        dis = sqrt(dis);
        distances.push_back(dis);
    }
    int indexOfAttractedNeighbor = min_element(begin(distances), 
    end(distances)) - begin(distances);
    auto attractedNeighbor = seen_neighbors[indexOfAttractedNeighbor];
    return attractedNeighbor;
}
 // namespace std;

