#include "./bestiole/Bestiole.h"
#include "./environment/Aquarium.h"
#include "./environment/Milieu.h"
#include "factory/BestiolFactory.h"

#include <iostream>

using namespace std;

int get_user_comportement_choose();

int main() {
  int total_num_bestiole = 20;
  int force_comportement = get_user_comportement_choose();

  Aquarium ecosysteme(640, 480, 30);
  auto &milieu = ecosysteme.getMilieu();
  BestiolFactory bestiole_factory(milieu.getWidth(), milieu.getHeight());
  bestiole_factory.force_comportement = force_comportement;
  // we use this random distribution for bestioles's comportement when force_comportement is 0
  bestiole_factory.bestioles_comportement_distribution = {
    0.33, 0.33, 0.33, 0, 0
  };
  milieu.setBestioleFactory(&bestiole_factory);

  for (int i = 1; i <= total_num_bestiole; ++i)
    ecosysteme.getMilieu().addMember(bestiole_factory.create_bestiole());
  ecosysteme.run();

  return 0;
}
/*
 * we can choose a behavior for all the bugs, which 0 represents the random, 1 for the Gragaire, 2 for the Peureuse, 3 for the Kamikaze, 4 for the Prevoiyante, 5 for the Multiple
 */
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