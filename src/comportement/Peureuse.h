//
// Created by Lenovo on 2022/11/25.
//

#ifndef ECOSYSTEM_SIMULATION_PEUREUSE_H
#define ECOSYSTEM_SIMULATION_PEUREUSE_H

#include "IComportement.h"

class Peureuse : public IComportement {

public:
  Peureuse();

  ~Peureuse() override;

  void move(Bestiole &b,
            std::vector<Bestiole const *> const &seen_neighbors) override;
  std::unique_ptr<IComportement> clone() const override;
private:
    bool fleeing = false;
};
#endif // ECOSYSTEM_SIMULATION_PEUREUSE_H
