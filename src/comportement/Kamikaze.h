#ifndef KAMIKAZE
#define KAMIKAZE
#include "IComportement.h"

class Kamikaze : public IComportement{
private:
Bestiole* getAttractedNeighbor();

public:
Kamikaze();
~Kamikaze();
void move(const Bestiole & b, vector<Bestiole> seen_neighbors);
};
#endif