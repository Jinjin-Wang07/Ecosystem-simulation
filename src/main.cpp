#include "./bestiole/Bestiole.h"
#include "./environment/Aquarium.h"
#include "./environment/Milieu.h"
#include "factory/BestiolFactory.h"

#include <iostream>

using namespace std;

int main() {

  Aquarium ecosysteme(640, 480, 30);
  BestiolFactory bestiole_factory(ecosysteme.getMilieu());

  for (int i = 1; i <= 20; ++i)
    ecosysteme.getMilieu().addMember(bestiole_factory.create_bestiole());
  ecosysteme.run();

  return 0;
}
