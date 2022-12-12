#ifndef MULTIPLE
#define MULTIPLE
#include "Gragaire.h"
#include "IComportement.h"
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

   Couleur get_color() const override {
    return {255, 255, 255};
   }
  void move(const Bestiole &b, vector<Bestiole> const &seen_neighbors);
};
#endif
