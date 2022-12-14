#ifndef KAMIKAZE
#define KAMIKAZE
#include "IComportement.h"
#include <string>

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

  Couleur get_color() const override { return {255, 0, 0}; }
  std::string get_name() const override {return "Kamikaze";}

  std::unique_ptr<IComportement> clone() const override;
};
#endif