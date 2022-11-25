#include "BestiolFactory.h"

#include <cstdlib>
#include <cmath>

/*
*   Default constructeur
*/
BestiolFactory::BestiolFactory(Milieu milieu)
{

    total_num_bestiole["Basic_Bestiole"] = 20;
    curr_num_bestiole["Basic_Bestiole"] = 0;

    this->width = milieu.getWidth();
    this->height = milieu.getHeight();

    this->max_age = 100;
    this->max_vitesse = 10.0;
    // eye_champ_angulaire_limit = 
}

BestiolFactory::~BestiolFactory()
{
}

Bestiole BestiolFactory::create_bestiole(){
    int x, y;
    initCoords(x, y);
    std::cout<<"===========================  initial x y "<<x<<"     "<<y<<std::endl;

    double fragility = (rand()%100)/100;

    printf("==========: %d, %d=========================", x, y);
    Bestiole new_bestiole(x, y, max_vitesse, max_age, fragility);

    return new_bestiole;
// void addMember( const Bestiole & b ) { listeBestioles.push_back(b); listeBestioles.back().initCoords(width, height); }

}


void BestiolFactory::initCoords(int& x, int& y)
{
    x = rand() % width;
    y = rand() % height;
}
