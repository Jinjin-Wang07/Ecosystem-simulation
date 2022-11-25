#include "Oreilles.h"
#include "../bestiole/Bestiole.h"
using namespace std;

Oreilles::Oreilles(double distance_min,double distance_max,double capacite_detection){
    this->distance_min=distance_min;
    this->distance_max=distance_max;
    this->capacite_detection=capacite_detection;
}

bool Oreilles::JeTePercoit(int x,int y,double orientation,const Bestiole& b) const{
    
   double dist = std::sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( (dist <= this->distance_max) & (dist >= this->distance_min) & (this->capacite_detection > b.camouflage_coef)) ;//
}