#ifndef KAMIKAZE
#define KAMIKAZE
#include "IComportement.h"

class Kamikaze : public IComportement {
private:
  Bestiole const *
  getAttractedNeighbor(const Bestiole &b,
                       std::vector<Bestiole const *> const &seen_neighbors);

public:
  Kamikaze();
  ~Kamikaze() override;
  void move(Bestiole &b,
            std::vector<Bestiole const *> const &seen_neighbors) override;
  std::unique_ptr<IComportement> clone() const override;
};
#endif