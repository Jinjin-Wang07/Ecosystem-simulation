
#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

using namespace std;
#include <../../include/HMI/UImg.h>
#include <memory>

class Bestiole;
class ICapteur {

public:
  // float distance;
  float capacite_detection;
  virtual ~ICapteur() = default;
  virtual bool JeTePercoit(int x, int y, double orientation,
                           const Bestiole &b) const = 0;
  virtual std::unique_ptr<ICapteur> clone() const = 0;
  virtual void draw(UImg &support, double xt, double yt,
                    double orientation) = 0;
  /*
   * Return the distance coefficient
   */
  float get_capacite_detection() { return capacite_detection; }
};

#endif