#include "./bestiole/Bestiole.h"
#include "./environment/Aquarium.h"
#include "./environment/Milieu.h"
#include "factory/BestiolFactory.h"

#include <iostream>

using namespace std;

int get_user_comportement_choose();

int main() {
  int total_num_bestiole = 20;
  int index_comportement = get_user_comportement_choose();

  Aquarium ecosysteme(640, 480, 30);
  BestiolFactory bestiole_factory(ecosysteme.getMilieu(), index_comportement);

  for (int i = 1; i <= total_num_bestiole; ++i)
    ecosysteme.getMilieu().addMember(bestiole_factory.create_bestiole());
  ecosysteme.run();

  return 0;
}

int get_user_comportement_choose() {
  int index_comportement = 0;
  cout << "============================================" << endl;
  cout << "============================================" << endl;
  cout << "[Default 0] : Random" << endl;
  cout << "[1] : Gragaire - Orange" << endl;
  cout << "[2] : Peureuse - Blue" << endl;
  cout << "[3] : Kamikaze - Red" << endl;
  // cout << "[4] : Prevoiyante - Green" << endl;
  // cout << "[5] : Multiple - White" << endl;
  cout << "Please choose a comportement ： " << endl;
  cin >> index_comportement; // if wrong num, index will be 0;
  cout << "Your choose is:  " << index_comportement << endl;
  cout << "============================================" << endl;
  cout << "============================================" << endl;

  return index_comportement;
}