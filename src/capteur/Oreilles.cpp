#include "Oreilles.h"

Oreilles::Oreilles(double distance_min,double distance_max,double capacite_detection){
    distance_min=distance_min;
    distance_max=distance_max;
    capacite_detection=capacite_detection;
}

bool Oreilles::JeTePercoit(int x,int y,double orientation,const Bestiole& b) const{
    
   dist = std::sqrt((x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( (dist <= dmax) & (dist >= dmin) );
}