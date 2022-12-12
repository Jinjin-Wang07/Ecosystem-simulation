#include "Oreilles.h"
#include "../../include/LogUtil.h"
#include "../bestiole/Bestiole.h"

using namespace std;

Oreilles::Oreilles(double distance_min, double distance_max,
                   double capacite_detection) {
  this->distance_min = distance_min;
  this->distance_max = distance_max;
  this->capacite_detection = capacite_detection;
}

bool Oreilles::JeTePercoit(int x, int y, double orientation,
                           const Bestiole &b) const {
  auto coordinates = b.getCoordinates();
  auto bx = coordinates.first;
  auto by = coordinates.second;
  double dist = std::sqrt((x - bx) * (x - bx) + (y - by) * (y - by));
  return ((dist <= this->distance_max) && (dist >= this->distance_min) &&
          (this->capacite_detection > b.get_camouflage_coef())); //
}

unique_ptr<ICapteur> Oreilles::clone() const {
  return unique_ptr<ICapteur>(new Oreilles(
      this->distance_min, this->distance_max, this->capacite_detection));
}

void Oreilles::draw(UImg &support, double xt, double yt, double orientation) {
  T *couleur = new T[3];
  couleur[0] = 0; // 223;
  couleur[1] = 0;
  couleur[2] = 0;

  support.draw_circle(xt, yt, this->distance_max / 2., couleur, 0.05);
}