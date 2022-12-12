#include "Yeux.h"
#include "../../include/LogUtil.h"
#include "../bestiole/Bestiole.h"
Yeux::Yeux(double distance_min, double distance_max, double champ_vision,
           float capacite) {
  this->distance_min = distance_min;
  this->distance_max = distance_max;
  this->champ_vision = champ_vision;
  this->capacite_detection = capacite;
}

bool Yeux::JeTePercoit(int x, int y, double orientation,
                       const Bestiole &b) const {
  auto coordinates = b.getCoordinates();
  auto bx = coordinates.first;
  auto by = coordinates.second;
  int dx = x - bx;
  int dy = y - by;

  // Angle returned as: (ref : https://stackoverflow.com/a/62486304/18059322)
  //                      pi/2
  //            3*pi/4                pi/4
  //
  //       pi          Origin           0
  //
  //           -3*pi/4                -pi/4
  //
  //                     -pi

  double angle = std::atan2(dy, dx);
  double dangle = angle - b.getOrientation();
  double dist = std::sqrt((x - bx) * (x - bx) + (y - by) * (y - by));
  return ((abs(dangle) < this->champ_vision / 2) &&
          (dist <= this->distance_max) && (dist >= this->distance_min) &&
          (this->capacite_detection > b.get_camouflage_coef()));
}

unique_ptr<ICapteur> Yeux::clone() const {
  return unique_ptr<ICapteur>(new Yeux(this->distance_min, this->distance_max,
                                       this->champ_vision,
                                       this->capacite_detection));
}

void Yeux::draw(UImg &support, double xt, double yt, double orientation) {
  T *couleur = new T[3];
  couleur[0] = 223;
  couleur[1] = 0;
  couleur[2] = 0;

  double xt2 = xt + champ_vision * std::cos(orientation / 2);
  double yt2 = yt + champ_vision * std::sin(orientation / 2);

  double xt3 = xt - champ_vision * std::cos(orientation / 2);
  double yt3 = yt - champ_vision * std::sin(orientation / 2);

  support.draw_triangle(xt, yt, xt2, yt2, xt3, yt3, couleur, 0.2);
}