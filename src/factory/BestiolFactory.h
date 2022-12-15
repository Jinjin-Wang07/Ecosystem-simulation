#ifndef _BESTIOL_FACTORY_H_
#define _BESTIOL_FACTORY_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string.h>

#include "../bestiole/Bestiole.h"
#include "../comportement/Gragaire.h"
#include "../comportement/IComportement.h"
#include "../comportement/Kamikaze.h"
#include "../comportement/Multiple.h"
#include "../comportement/Peureuse.h"
#include "../comportement/Prevoyante.h"

// Desactivate les random functions
#define NO_RANDOM false

class BestiolFactory {
private:
  static int next_id;

public:
  map<string, double> total_num_bestiole;

  int const num_comportement = 5;

  pair<double, double> eye_champ_angulaire_limit;
  pair<double, double> eye_distance_limit;
  pair<double, double> eye_capacite_detection_limit;

  pair<double, double> ear_distance_limit;
  pair<double, double> ear_capacite_detection_limit;

  double nageoire_speed_coef_max;
  double carapace_resistance_coef_max;
  double carapace_speed_coef_max;

  pair<double, double> camouflage_coef_max; // should be smaller than 1

  int max_age;
  double max_vitesse;

  int width, height; // size of the aquarium

  double birth_rate;
  double clone_probability;

  array<double, 5> bestioles_comportement_distribution = {0.2, 0.2, 0.2,
                                                          0.2, 0.2};

  int force_comportement = 0;

private:
  void initCoords(int &, int &);

  Couleur get_random_color();

  unique_ptr<IComportement> get_comportement();

  // function for adding capteurs and accessoires
  void add_capteur_yeux(Bestiole &b);
  void add_capteur_oreille(Bestiole &b);
  void add_accessoire_camouflage(Bestiole &b);
  void add_accessoire_carapace(Bestiole &b);
  void add_accessoire_negeoire(Bestiole &b);

  std::random_device rd;
  std::mt19937 gen;

public:
  /*
   * Create a bestiolFactory with all default value
   */
  BestiolFactory(int width, int height);
  ~BestiolFactory();

  double get_ramdom_value(double, double);
  int get_random_int(int, int);

  /*
   *   create a default bestiole
   */
  Bestiole create_bestiole();
  Bestiole clone_bestiole(Bestiole const &b);

  /*
   *   Reset the factory variables to default
   */
  void reset_factory();

  void set_ramdom_capteur(Bestiole &b);
  void set_random_accessoire(Bestiole &b);

  // Check if the current number of bestiole smaller than limit
  bool can_add_bestiole(int nbBestioles);
};

#endif // _BESTIOL_FACTORY_H_
