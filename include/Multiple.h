#include "Comportement.h"
#include "Gregaire.h"
#include "Kamikaze.h"
#include "Peureuse.h"
#include "Prevoyante.h"
#include <vector>
using namespace std;
class Multiple : public IComportement {
private:
  vector<IComportement> comportements;

public:
  Multiple();
  ~Multiple();
  void move();
};