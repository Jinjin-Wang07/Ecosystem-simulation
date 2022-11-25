#include "Yeux.h"
#include "../bestiole/Bestiole.h"
Yeux::Yeux(double distance_min,double distance_max,double champ_vision,float capacite){
    this->distance_min=distance_min;
    this->distance_max=distance_max;
    this->champ_vision=champ_vision;
    this->capacite_detection=capacite;
}

bool Yeux::JeTePercoit(int x,int y,double orientation,const Bestiole& b) const{
   int dx= x-b.x;
   int dy= y-b.y;
   
    // Angle returned as: (ref : https://stackoverflow.com/a/62486304/18059322)
    //                      pi/2
    //            3*pi/4                pi/4
    //
    //       pi          Origin           0
    //
    //           -3*pi/4                -pi/4
    //
    //                     -pi
    
    double angle = std::atan2(dy,dx);
    double dangle=angle-b.orientation;
    double dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
    return ((abs(dangle)<this->champ_vision/2) & (dist <= this->distance_max) & (dist >= this->distance_min) & (this->capacite_detection > b.camouflage_coef));
}