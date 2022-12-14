//
// Created by Lenovo on 2022/11/25.
//

#ifndef ECOSYSTEM_SIMULATION_ICOMPORTEMENT_H
#define ECOSYSTEM_SIMULATION_ICOMPORTEMENT_H

#include "UImg.h"

#include <array>
#include <memory>
#include <vector>
#include <string>

class Bestiole;

using Couleur = std::array<T, 3>;
/*
 * Interface for bug's behaviors
 */
class IComportement {

public:
  virtual ~IComportement() = default;

  virtual void move(Bestiole &b,
                    std::vector<Bestiole const *> const &seen_neighbors) = 0;

  virtual Couleur get_color() const = 0;

  virtual std::string get_name() const = 0;

  virtual std::unique_ptr<IComportement> clone() const = 0;
};
#endif // ECOSYSTEM_SIMULATION_ICOMPORTEMENT_H
