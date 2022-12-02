#include "BestiolFactory.h"

#include "../comportement/Gragaire.h"
#include "../comportement/Kamikaze.h"
#include "../comportement/Peureuse.h"

#include "../capteur/ICapteur.h"
#include "../capteur/Yeux.h"
#include "../capteur/Oreilles.h"



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
    double distance = get_ramdom_value(eye_distance_limit.first, eye_distance_limit.second);

    double champ_vision = get_ramdom_value(eye_champ_angulaire_limit.first , eye_champ_angulaire_limit.second);

    double capacite = get_ramdom_value(eye_capacite_detection_limit.first , eye_capacite_detection_limit.second);

    Yeux* yeux = new Yeux(0, distance, champ_vision, capacite);
    b.addCapteur(yeux);
}

void BestiolFactory::add_capteur_oreille(Bestiole &b){
    double distance = get_ramdom_value(ear_distance_limit.first, ear_distance_limit.second);

    double capacite_detection = get_ramdom_value(ear_capacite_detection_limit.first,
                                                ear_capacite_detection_limit.second);

    Oreilles* oreilles = new Oreilles(0, distance, capacite_detection);
    b.addCapteur(oreilles);
}


/**
 * Une bestiole disposant d’un camouflage sera plus difficile a detecter par les autres.
 * Camouflage_coef = 0 signifie pas de camouflage
 * Camouflage_coef = 1 signifie il ne peut pas etre detecter
 */
void BestiolFactory::add_accessoire_camouflage(Bestiole &b){
    double coef = get_ramdom_value(0, camouflage_coef_max);
    b.set_camouflage_coef(coef);
}

void BestiolFactory::add_accessoire_carapace(Bestiole &b){
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
void BestiolFactory::add_accessoire_negeoire(Bestiole &b){
    double coef_v = get_ramdom_value(1, nageoire_speed_coef_max);
    double new_vitesse = b.get_vitesse() * coef_v;
    b.setVitesse(new_vitesse);
}


/** 
 * Set randomly capteurs
 * Probablility(get_ramdom_value(0,1)>0.5) == 50%
 */ 
void BestiolFactory::set_ramdom_capteur(Bestiole &b){
    bool have_yeux = get_ramdom_value(0,1)>0.5;
    bool have_oreille = get_ramdom_value(0,1)>0.5;

    if(have_yeux) add_capteur_yeux(b);
    if(have_oreille) add_capteur_oreille(b);
}

/** 
 * Set randomly accessoires
 * Probablility(get_ramdom_value(0,1)>0.5) == 50%
 */ 
void BestiolFactory::set_random_accessoire(Bestiole &b){
    bool have_carapace = get_ramdom_value(0,1)>0.5;
    bool have_camouflage = get_ramdom_value(0,1)>0.5;
    bool have_negeoire = get_ramdom_value(0,1)>0.5;

    if(have_carapace) add_accessoire_carapace(b);
    if(have_camouflage) add_accessoire_camouflage(b);
    if(have_negeoire) add_accessoire_negeoire(b);
}


// fonction genere valeure ramdom uniform distribuate between [min, max]
double BestiolFactory::get_ramdom_value(double min, double max){
    std::uniform_real_distribution<double> unif(min, max);
    std::default_random_engine seed;
    return unif(seed);
}