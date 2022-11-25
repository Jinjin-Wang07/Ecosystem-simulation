#include "Comportement.h"

class Kamikaze : public IComportement{
private:
&Bestiole getAttractedNeighbor();

public:
Kamikaze();
~Kamikaze();
void move();
};