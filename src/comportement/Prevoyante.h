#ifndef PREVOYANTE
#define PREVOYANTE
#include "IComportement.h"
using namespace std;
class Prevoyante : public IComportement {

public:
  Prevoyante();

  ~Prevoyante() override;
  void move(Bestiole &b, std::vector<Bestiole const *> const &seen_neighbors) override;
  std::unique_ptr<IComportement> clone() const override;
};
#endif