#include "Oreilles.h"

Oreilles::Oreilles(float dmin,float dmax,float capacite){
    distance_min=dmin
    distance_max=dmax
    capacite_detection=capacite
}

bool Oreilles::JeTePercoit(int x,int y,double orientation,const Bestiole& b) const{
    
   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( (dist <= dmax) & (dist >= dmin) );
}