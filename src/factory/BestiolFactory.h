#ifndef _BESTIOL_FACTORY_H_
#define _BESTIOL_FACTORY_H_

#include <iostream>
#include <map>
#include <string.h>

#include "../bestiole/Bestiole.h"
#include "../environment/Milieu.h"

class BestiolFactory {
private:
public:
  map<string, double> total_num_bestiole;
  map<string, double> curr_num_bestiole; // {specie_name : number}
  tuple<float, float> eye_champ_angulaire_limit;
  tuple<float, float> eye_distance_limit;
  tuple<float, float> eye_capacite_detection_limit;

  tuple<float, float> ear_distance_limit;
  tuple<float, float> ear_capacite_detection_limit;

  float nageoire_speed_coef_max;
  float carapace_resistance_coef_max;
  float carapace_speed_coef_max;

  float camouflage_coef_max;

  int max_age;
  double max_vitesse;

  int width, height; // size of the aquarium

  float birth_rate;
  float clone_probability;

  float bestioles_comportement_distribution[5];

public:
  /*
   * Create a bestiolFactory with all default value
   */
  BestiolFactory(Milieu milieu);
  ~BestiolFactory();

  /*
   *   create a default bestiole
   */
  Bestiole create_bestiole();

  /*
   *   Reset the factory variables to default
   */
  void reset_factory();

  void initCoords(int &, int &);
};

#endif // _BESTIOL_FACTORY_H_
