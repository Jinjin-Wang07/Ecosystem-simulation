#ifndef PREVOYANTE
#define PREVOYANTE
#include "IComportement.h"
#include <string>
using namespace std;
class Prevoyante : public IComportement {

public:
  Prevoyante();

  ~Prevoyante() override;
  void move(Bestiole &b,
            std::vector<Bestiole const *> const &seen_neighbors) override;

  std::string get_name() const override {return "Prevoyante";}

  Couleur get_color() const override { return {0, 255, 0}; }
  std::unique_ptr<IComportement> clone() const override;
};
#endif