#include "BestiolFactory.h"

#include "../comportement/Gragaire.h"
#include "../comportement/Kamikaze.h"
#include "../comportement/Peureuse.h"

#include "../capteur/ICapteur.h"
#include "../capteur/Yeux.h"
#include "../capteur/Oreilles.h"

#include <cmath>
#include <cstdlib>
#include <memory>
#include <random>

using namespace std;

/*
 *   Default constructeur
 */
BestiolFactory::BestiolFactory(Milieu milieu) {

  total_num_bestiole["Basic_Bestiole"] = 50;
  curr_num_bestiole["Basic_Bestiole"] = 0;

  this->width = milieu.getWidth();
  this->height = milieu.getHeight();

  this->max_age = 100;
  this->max_vitesse = 10.0;
  // eye_champ_angulaire_limit =
  curr_bestiole_comportment_num = {
    {"Gragaire",0}, {"Kamikaze",0}, {"Peureuse",0}, {"Prevoyante", 0}, {"Multiple", 0}
    };
}

BestiolFactory::~BestiolFactory() {}

Bestiole BestiolFactory::create_bestiole() {
    int x, y;
    initCoords(x, y);

    double fragility = (rand() % 100) / 100;


    double camouflage_coef = 1;
    Bestiole new_bestiole(x, y, max_vitesse, max_age, fragility, camouflage_coef);

    IComportement* comportement = get_random_comportement();

    if (true) {
        new_bestiole.setComportement(std::unique_ptr<IComportement>(comportement));
    }

    curr_num_bestiole["Basic_Bestiole"]++;

    return new_bestiole;
}

void BestiolFactory::initCoords(int &x, int &y) {
  x = rand() % width;
  y = rand() % height;
}


IComportement* BestiolFactory::get_random_comportement(){
    
    // int index_comportement = (rand() % (num_comportement))+ 1;
    int index_comportement = (rand() % (3))+ 1;
    IComportement* comportement;

    switch(index_comportement) {
    case 1:
        comportement = new Gragaire();
        curr_bestiole_comportment_num["Gragaire"]++;
        break;
    case 2:
        comportement = new Peureuse();
        curr_bestiole_comportment_num["Peureuse"]++;
        break;
    case 3:
        comportement = new Kamikaze();
        curr_bestiole_comportment_num["Kamikaze"]++;
        break;
    // case 4:
    //     comportement = new Prevoyante();
    // curr_bestiole_comportment_num["Prevoyante"]++;
    //     break;
    // case 5:
    //     comportement = new Multiple();
    // curr_bestiole_comportment_num["Multiple"]++;
    //     break;
    default:
        throw std::runtime_error("get_random_comportement error");
    }
    return comportement;
}


/**
 *  Simple functions for adding eye for a bestiole 
 */
void BestiolFactory::add_capteur_yeux(Bestiole &b){
    // eye_distance_limit

    double min_dis = get<0>(eye_distance_limit);
    double max_dis = get<1>(eye_distance_limit);

    std::uniform_real_distribution<double> unif_dis(min_dis, max_dis);
    std::default_random_engine seed;
    double distance = unif_dis(seed);


    std::uniform_real_distribution<double> unif_ang(eye_champ_angulaire_limit.first , eye_champ_angulaire_limit.second);
    double champ_vision = unif_ang(seed);

    std::uniform_real_distribution<double> unif_cap(eye_capacite_detection_limit.first , eye_capacite_detection_limit.second);
    // champ_vision = 0;
    double capacite = unif_cap(seed);


    Yeux* yeux = new Yeux(0, distance, champ_vision, capacite);
    b.addCapteur(yeux);
}

void BestiolFactory::add_capteur_oreille(Bestiole &b){
    double distance_min = 0;
    double distance_max = 2;
    double capacite_detection = 3;

    Oreilles* oreilles = new Oreilles(distance_min, distance_max, capacite_detection);
    b.addCapteur(oreilles);
}


/**
 * Une bestiole disposant d’un camouflage sera plus difficile a detecter par les autres.
 * Camouflage_coef = 0 signifie pas de camouflage
 * Camouflage_coef = 1 signifie il ne peut pas etre detecter
 */
void BestiolFactory::add_accessoire_camouflage(Bestiole &b){
    b.set_camouflage_coef();
}

void BestiolFactory::add_accessoire_carapace(Bestiole &b){
    b.set_fragility();
    b.setVitesse();
}

/**
 *  Here we suposse that bestiol can only have one negeoire
 */
void BestiolFactory::add_accessoire_negeoire(Bestiole &b){
    // double new_vitesse = b.get_vitesse() * 
    // b.setVitesse(new_vitesse);
}


