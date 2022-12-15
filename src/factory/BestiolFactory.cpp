#include "BestiolFactory.h"

#include "../../include/LogUtil.h"

#include "../comportement/Gragaire.h"
#include "../comportement/Kamikaze.h"
#include "../comportement/Multiple.h"
#include "../comportement/Peureuse.h"
#include "../comportement/Prevoyante.h"

#include "../capteur/ICapteur.h"
#include "../capteur/Oreilles.h"
#include "../capteur/Yeux.h"

using namespace std;
int BestiolFactory::next_id = 0;
/*
 *   Default constructor
 */
BestiolFactory::BestiolFactory(int width, int height) : gen(rd()) {

  total_num_bestiole["Basic_Bestiole"] = 50;

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
  this->max_vitesse = 10.0;

  birth_rate = 0.05; // 100 step 1 birth
  clone_probability = 0.02;
}

BestiolFactory::~BestiolFactory() {}

/*
 * crete a bug with random parameter which doesn't exceed the max setting
 */
Bestiole BestiolFactory::create_bestiole() {
  int x, y;
  initCoords(x, y);

  double camouflage_coef = 0; // TODO : make it ramdom
  double fragility = get_ramdom_value(0, 1);
  double orientation = get_ramdom_value(0, 2. * M_PI);
  double vitesse = get_ramdom_value(max_vitesse / 2, max_vitesse);

  unique_ptr<IComportement> comportement = get_comportement();

  // Couleur color = comportement->get_color();

  int individu_max_age = get_ramdom_value(100, max_age);
  Bestiole new_bestiole(x, y, vitesse, max_vitesse, individu_max_age, fragility,
                        camouflage_coef, orientation);
  new_bestiole.identite = ++next_id;

  if (true) {
    new_bestiole.setComportement(move(comportement));
  }

  // Add ramdomly the yeux / oreille
  set_ramdom_capteur(new_bestiole);

  // Add ramdomly the accessoires
  set_random_accessoire(new_bestiole);

  return new_bestiole;
}
/*
 * initialize a bug's coordination
 */
void BestiolFactory::initCoords(int &x, int &y) {
  x = rand() % width;
  y = rand() % height;
}

/**
 * Get randomly a comportement
 * return : Pointer of a Comportement that implemented IComportement
 *  TODO : Prevoyante and Multiple aren't implemented
 */
/*
 * choose a bug's behavior by the force_comportement parameter, if the parameter
 * is default, choose a behavior randomly
 */
unique_ptr<IComportement> BestiolFactory::get_comportement() {

  // int index_comportement = (rand() % (num_comportement))+ 1;
  switch (force_comportement) {
  case 1:
    return unique_ptr<Gragaire>(new Gragaire());
  case 2:
    return unique_ptr<Peureuse>(new Peureuse());
  case 3:
    return unique_ptr<Kamikaze>(new Kamikaze());
  case 4:
    return unique_ptr<Prevoyante>(new Prevoyante());
  case 5:
    return unique_ptr<Multiple>(new Multiple());
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
      return unique_ptr<Gragaire>(new Gragaire());
    } else if (randomV <= distribution_cumul[1]) {
      return unique_ptr<Peureuse>(new Peureuse());
    } else if (randomV <= distribution_cumul[2]) {
      return unique_ptr<Kamikaze>(new Kamikaze());
    } else if (randomV <= distribution_cumul[3]) {
      return unique_ptr<Prevoyante>(new Prevoyante());
    } else if (randomV <= distribution_cumul[4]) {
      return unique_ptr<Multiple>(new Multiple());
    } else {
      throw std::runtime_error{"Bad bestiole distribution"};
    }
  }
}

/*
 *  add an eye captor to a bug and set the random value of distance,
 * champ_vision, capacity parameters for the eye captor
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


/*
 *  add an ear captor to a bug and set the random value of capacite_detection,
 * distance_min, distance_max parameters for the ear captor
 */
void BestiolFactory::add_capteur_oreille(Bestiole &b) {
  double distance_min = ear_distance_limit.first;
  double distance_max =
      get_ramdom_value(ear_distance_limit.first, ear_distance_limit.second);

  double capacite_detection = get_ramdom_value(
      ear_capacite_detection_limit.first, ear_capacite_detection_limit.second);

  unique_ptr<ICapteur> oreille = unique_ptr<ICapteur>(
      new Oreilles(distance_min, distance_max, capacite_detection));
  b.move_capteur(move(oreille));
}

/*
 *  add a camouflage accessory to a bug and set the random value of
 * camouflage_coef for the camouflage accessory
 */
void BestiolFactory::add_accessoire_camouflage(Bestiole &b) {
  double coef =
      get_ramdom_value(camouflage_coef_max.first, camouflage_coef_max.second);
  b.set_camouflage_coef(coef);
}
/*
 *  add a carapace accessory to a bug and set the random value of fragility_coef
 * and new_vitesse for the carapace accessory
 */
void BestiolFactory::add_accessoire_carapace(Bestiole &b) {
  double coef_fra = get_ramdom_value(0, carapace_resistance_coef_max);
  double new_fra = b.get_fragility() / coef_fra;
  b.set_fragility(new_fra);

  double coef_v = get_ramdom_value(1, carapace_speed_coef_max);
  double new_vitesse = b.get_vitesse() / coef_v;
  b.setVitesse(new_vitesse);
}

/*
 *  add a negeoire accessory to a bug and set the random value of new_vitesse
 * for the negeoire accessory.Here we suposse that bug can only have one
 * negeoire
 */
void BestiolFactory::add_accessoire_negeoire(Bestiole &b) {
  double coef_v = get_ramdom_value(1, nageoire_speed_coef_max);
  double new_vitesse = b.get_vitesse() * coef_v;
  b.setVitesse(new_vitesse);
}

/*
 * Set random capteurs for a bug
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

/*
 * Set random accessoires  for a bug
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

/*
 * get a uniform random double value between the min and max
 */
double BestiolFactory::get_ramdom_value(double min, double max) {
  if (NO_RANDOM)
    return max;
  // Will be used to obtain a seed for the random number engine
  // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

/*
 * get a uniform random int value between the min and max
 */
int BestiolFactory::get_random_int(int min, int max) {
  if (NO_RANDOM)
    return max;
  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}

/*
 * clone a bug with a different id
 */
Bestiole BestiolFactory::clone_bestiole(Bestiole const &b) {
  auto clone = b;

  // clone has a different identite
  clone.setOrientation(get_ramdom_value(0, 2 * M_PI));
  clone.identite = ++next_id;
  clone.age = 0;
  return clone;
}

bool BestiolFactory::can_add_bestiole(int nbBestioles){
  return nbBestioles <= total_num_bestiole["Basic_Bestiole"];
}