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
#include "../environment/Milieu.h"

// Desactivate les random functions
#define NO_RANDOM true

class BestiolFactory {
private:
public:
  map<string, double> total_num_bestiole;
  map<string, double> curr_num_bestiole; // {specie_name : number}

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

  map<string, int> curr_bestiole_comportment_num;
  double bestioles_comportement_distribution[5];

  int index_comportement;

private:
  double get_ramdom_value(double, double);
  int get_random_int(int, int);

  void initCoords(int &, int &);

  Couleur get_color(int index_comportement);
  Couleur get_random_color();

  IComportement *get_comportement(int index_comportement);

  // function for adding capteurs and accessoires
  void add_capteur_yeux(Bestiole &b);
  void add_capteur_oreille(Bestiole &b);
  void add_accessoire_camouflage(Bestiole &b);
  void add_accessoire_carapace(Bestiole &b);
  void add_accessoire_negeoire(Bestiole &b);

public:
  /*
   * Create a bestiolFactory with all default value
   */
  BestiolFactory(Milieu milieu, int index_comportement);
  ~BestiolFactory();

  /*
   *   create a default bestiole
   */
  Bestiole create_bestiole();

  /*
   *   Reset the factory variables to default
   */
  void reset_factory();

  void set_ramdom_capteur(Bestiole &b);
  void set_random_accessoire(Bestiole &b);
};

#endif // _BESTIOL_FACTORY_H_
