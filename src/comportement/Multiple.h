#ifndef MULTIPLE
#define MULTIPLE
#include "IComportement.h"
#include <vector>
#include <string>
class Multiple : public IComportement {
private:
  std::unique_ptr<IComportement> currentComportement;
  int stepsSinceLastComportementChange = 0;
  std::unique_ptr<IComportement> updateComportement() const;

public:
  Multiple();
  ~Multiple() override;

  Couleur get_color() const override {
    return currentComportement->get_color();
  }

  std::string get_name() const override {return "Multiple";}

  void move(Bestiole &b,
            std::vector<Bestiole const *> const &seen_neighbors) override;

  std::unique_ptr<IComportement> clone() const override {
    return std::unique_ptr<Multiple>(new Multiple());
  }
};
#endif
