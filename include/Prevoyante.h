#include "Comportement.h"
#include <vector>
using namespace std;
typedef vector<float> Path;
class Prevoyante {
private:
  vector<Path> getNeighborPaths(vector<Bestiole> const &neighbors);

public:
  Prevoyante();
  ~Prevoyante();
  void move();
};