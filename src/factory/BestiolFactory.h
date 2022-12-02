#ifndef _BESTIOL_FACTORY_H_
#define _BESTIOL_FACTORY_H_

#include <iostream>
#include <map>
#include <string.h>

#include "../bestiole/Bestiole.h"
#include "../environment/Milieu.h"
#include "../comportement/IComportement.h"
#include "../comportement/Gragaire.h"
#include "../comportement/Kamikaze.h"
#include "../comportement/Peureuse.h"
#include "../comportement/Prevoyante.h"
#include "../comportement/Multiple.h"

class BestiolFactory {
private:
public:
    map<string, double> total_num_bestiole;
    map<string, double> curr_num_bestiole; // {specie_name : number}

    int const num_comportement = 5;

    pair<double, double> eye_champ_angulaire_limit;
    tuple<double, double> eye_distance_limit;
    pair<double, double> eye_capacite_detection_limit;

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

    map<string, int> curr_bestiole_comportment_num;
    float bestioles_comportement_distribution[5];

private:
    void initCoords(int &, int &);

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

  
  IComportement* get_random_comportement();
//   void add_accessoire(Bestiole &b);

};

#endif // _BESTIOL_FACTORY_H_
