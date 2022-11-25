#include "Oreilles.h"

Yeux::Yeux(double distance_min,double distance_max,double champ_vision,float capacite){
    distance_min=distance_min;
    distance_max=distance_max;
    champ_vision=champ_vision;
    capacite_detection=capacite_detection;
}

bool Oreilles::JeTePercoit(int x,int y,double orientation,const Bestiole& b) const{
   int dx= x-b.x;
   int dy= y-b.y;
   
    // Angle returned as: (ref : https://stackoverflow.com/a/62486304/18059322)
    //                      90
    //            135                45
    //
    //       180          Origin           0
    //
    //           -135                -45
    //
    //                     -90
   double angle = std::atan2(p1.y - p2.y, p1.x - p2.x);
   double dangle=angle-direction;

   dist = std::sqrt( ()*(x-b.x) + (y-b.y)*(y-b.y) );
   return ((dangle<champ_vision)& (dist <= dmax) & (dist >= dmin) );
}