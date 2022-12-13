#include "BestiolFactory.h"

#include "../comportement/Gragaire.h"
#include "../comportement/Kamikaze.h"
#include "../comportement/Peureuse.h"

#include "../capteur/ICapteur.h"
#include "../capteur/Oreilles.h"
#include "../capteur/Yeux.h"

using namespace std;
int BestiolFactory::next_id = 0;
/*
 *   Default constructeur
 */
BestiolFactory::BestiolFactory(int width, int height) : gen(rd()) {

  total_num_bestiole["Basic_Bestiole"] = 50;
  curr_num_bestiole["Basic_Bestiole"] = 0;

  this->width = width;
  this->height = height;

  // eye_champ_angulaire_limit =

  eye_champ_angulaire_limit = make_pair(0, 2 * M_PI);
  eye_distance_limit = make_pair(20, 80);
  eye_capacite_detection_limit = make_pair(0, 1);

  ear_distance_limit = make_pair(20, 100);
  ear_capacite_detection_limit = make_pair(0, 1);

  nageoire_speed_coef_max = 10;
  carapace_resistance_coef_max = 10;
  carapace_speed_coef_max = 10;

  camouflage_coef_max = make_pair(0.1, 0.9);

  this->max_age = 1000; // 1000 = 1s
  this->max_vitesse = 5.0;

  birth_rate = 0.1; // 10 step 1 birth
  clone_probability = 0.05;

  curr_bestiole_comportment_num = {{"Gragaire", 0},
                                   {"Kamikaze", 0},
                                   {"Peureuse", 0},
                                   {"Prevoyante", 0},
                                   {"Multiple", 0}};
}

BestiolFactory::~BestiolFactory() {}

Bestiole BestiolFactory::create_bestiole() {
  int x, y;
  initCoords(x, y);

  double camouflage_coef = 0; // TODO : make it ramdom
  double fragility = get_ramdom_value(0, 1);
  double orientation = get_ramdom_value(0, 2. * M_PI);
  double vitesse = get_ramdom_value(max_vitesse / 2, max_vitesse);

  unique_ptr<IComportement> comportement = get_comportement();
  Couleur color = comportement->get_color();

  Bestiole new_bestiole(x, y, vitesse, max_vitesse, max_age, fragility,
                        camouflage_coef, orientation, color);
  new_bestiole.identite = ++next_id;

  if (true) {
    new_bestiole.setComportement(move(comportement));
  }

  // Add ramdomly the yeux / oreille
  set_ramdom_capteur(new_bestiole);

  // Add ramdomly the accessoires
  set_random_accessoire(new_bestiole);

  curr_num_bestiole["Basic_Bestiole"]++;

  return new_bestiole;
}

void BestiolFactory::initCoords(int &x, int &y) {
  x = rand() % width;
  y = rand() % height;
}

/**
 * Get randomly a comportement
 * return : Pointer of a Comportement that implemented IComportement
 *  TODO : Prevoyante and Multiple aren't implemented
 */
unique_ptr<IComportement> BestiolFactory::get_comportement() {

  // int index_comportement = (rand() % (num_comportement))+ 1;
  switch (force_comportement) {
  case 1: 
    curr_bestiole_comportment_num["Gragaire"]++;
    return unique_ptr<Gragaire>(new Gragaire());
  case 2:
    curr_bestiole_comportment_num["Peureuse"]++;
    return unique_ptr<Peureuse>(new Peureuse());
  case 3:
    curr_bestiole_comportment_num["Kamikaze"]++;
    return unique_ptr<Kamikaze>(new Kamikaze());
  // case 4:
  //     comportement = new Prevoyante();
  // curr_bestiole_comportment_num["Prevoyante"]++;
  //     break;
  // case 5:
  //     comportement = new Multiple();
  // curr_bestiole_comportment_num["Multiple"]++;
  //     break;
  default:
    // generate random based on distribution
    double distribution_cumul[5];
    double sum = 0;
    for (int i = 0; i < 5; ++i) {
      sum += bestioles_comportement_distribution[i];
      distribution_cumul[i] = sum;
    }
    auto randomV = get_ramdom_value(0, sum);
    if (randomV <= distribution_cumul[0]) {
    curr_bestiole_comportment_num["Gragaire"]++;
      return unique_ptr<Gragaire>(new Gragaire());
    } else if (randomV <= distribution_cumul[1]) {
    curr_bestiole_comportment_num["Peureuse"]++;
      return unique_ptr<Peureuse>(new Peureuse());
    } else if (randomV <= distribution_cumul[2]) {
    curr_bestiole_comportment_num["Kamikaze"]++;
      return unique_ptr<Kamikaze>(new Kamikaze());
    } else {
      throw std::runtime_error{"Bad bestiole distribution"};
    }
  }
}

/**
 *  Simple functions for adding eye for a bestiole
 */
void BestiolFactory::add_capteur_yeux(Bestiole &b) {
  // eye_distance_limit
  double distance =
      get_ramdom_value(eye_distance_limit.first, eye_distance_limit.second);

  double champ_vision = get_ramdom_value(eye_champ_angulaire_limit.first,
                                         eye_champ_angulaire_limit.second);

  double capacite = get_ramdom_value(eye_capacite_detection_limit.first,
                                     eye_capacite_detection_limit.second);

  Yeux *yeux = new Yeux(0, distance, champ_vision, capacite);
  b.move_capteur(move(unique_ptr<ICapteur>(yeux)));
}

void BestiolFactory::add_capteur_oreille(Bestiole &b) {
  double distance_min = ear_distance_limit.first;
  double distance_max =
      get_ramdom_value(ear_distance_limit.first, ear_distance_limit.second);

  double capacite_detection = get_ramdom_value(
      ear_capacite_detection_limit.first, ear_capacite_detection_limit.second);

  unique_ptr<ICapteur> oreille = unique_ptr<ICapteur>(
      new Oreilles(distance_min, distance_max, capacite_detection));
  // Oreilles* oreilles = new Oreilles(distance_min, distance_max,
  // capacite_detection);
  b.move_capteur(move(oreille));
}

/**
 * Une bestiole disposant d’un camouflage sera plus difficile a detecter par les
 * autres. Camouflage_coef = 0 signifie pas de camouflage Camouflage_coef = 1
 * signifie il ne peut pas etre detecter
 */
void BestiolFactory::add_accessoire_camouflage(Bestiole &b) {
  double coef =
      get_ramdom_value(camouflage_coef_max.first, camouflage_coef_max.second);
  b.set_camouflage_coef(coef);
}

void BestiolFactory::add_accessoire_carapace(Bestiole &b) {
  double coef_fra = get_ramdom_value(0, carapace_resistance_coef_max);
  double new_fra = b.get_fragility() / coef_fra;
  b.set_fragility(new_fra);

  double coef_v = get_ramdom_value(1, carapace_speed_coef_max);
  double new_vitesse = b.get_vitesse() / coef_v;
  b.setVitesse(new_vitesse);
}

/**
 *  Here we suposse that bestiol can only have one negeoire
 */
void BestiolFactory::add_accessoire_negeoire(Bestiole &b) {
  double coef_v = get_ramdom_value(1, nageoire_speed_coef_max);
  double new_vitesse = b.get_vitesse() * coef_v;
  b.setVitesse(new_vitesse);
}

/**
 * Set randomly capteurs
 * Probablility(get_ramdom_value(0,1)>0.5) == 50%
 */
void BestiolFactory::set_ramdom_capteur(Bestiole &b) {
  bool have_yeux = get_ramdom_value(0, 1) > 0.5;
  bool have_oreille = get_ramdom_value(0, 1) > 0.5;

  if (have_yeux)
    add_capteur_yeux(b);
  if (have_oreille)
    add_capteur_oreille(b);
}

/**
 * Set randomly accessoires
 * Probablility(get_ramdom_value(0,1)>0.5) == 50%
 */
void BestiolFactory::set_random_accessoire(Bestiole &b) {
  bool have_carapace = get_ramdom_value(0, 1) > 0.5;
  bool have_camouflage = get_ramdom_value(0, 1) > 0.5;
  bool have_negeoire = get_ramdom_value(0, 1) > 0.5;

  if (have_carapace)
    add_accessoire_carapace(b);
  if (have_camouflage)
    add_accessoire_camouflage(b);
  if (have_negeoire)
    add_accessoire_negeoire(b);
}

// fonction genere valeure ramdom double value uniform distribuate between [min,
// max]
double BestiolFactory::get_ramdom_value(double min, double max) {
  if (NO_RANDOM)
    return max;
 // Will be used to obtain a seed for the random number engine
   // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

// fonction genere valeure ramdom int value uniform distribuate between [min,
// max]
int BestiolFactory::get_random_int(int min, int max) {
  if (NO_RANDOM)
    return max;
  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}

Bestiole BestiolFactory::clone_bestiole(Bestiole const &b) const {
  auto clone = b;
  // clone has a different identite
  clone.identite = ++next_id;
  clone.age = 0;
  return clone;
}
