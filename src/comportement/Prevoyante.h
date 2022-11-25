#ifndef PREVOYANTE
#define PREVOYANTE
#include "IComportement.h"
#include <vector>
using namespace std;
typedef vector<float> Path;
class Prevoyante : public IComportement{
private:
vector<Path> getNeighborPaths(vector<Bestiole> const& neighbors);
public:
Prevoyante();
~Prevoyante();
void move();
};
#endif