#include "Multiple.h"
#include "Gragaire.h"
#include "Kamikaze.h"
#include "Peureuse.h"
#include "Prevoyante.h"
#include <iostream>
#include <random>
using namespace std;

Multiple::Multiple() : currentComportement(updateComportement()) {
  cout << "Create multiple behavior" << endl;
}

Multiple::~Multiple() { cout << "Destroy multiple behavior" << endl; }

std::unique_ptr<IComportement> Multiple::updateComportement() const {
  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(0, 2);
  switch (dis(gen)) {
  case 0:
    return unique_ptr<Gragaire>(new Gragaire());
  case 1:
    return unique_ptr<Peureuse>(new Peureuse());
  case 2:
    return unique_ptr<Kamikaze>(new Kamikaze());
  case 3:
    return unique_ptr<Prevoyante>(new Prevoyante());
  default:
    throw std::runtime_error{"Should not reach there"};
  }

  return nullptr;
}

void Multiple::move(Bestiole &b,
                    vector<Bestiole const *> const &seen_neighbors) {
  if (stepsSinceLastComportementChange++ > 100) {
    stepsSinceLastComportementChange = 0;
    currentComportement = updateComportement();
  }

  return currentComportement->move(b, seen_neighbors);
}
