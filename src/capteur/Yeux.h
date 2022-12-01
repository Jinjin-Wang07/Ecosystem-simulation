#if !defined(_TEUX_H_)
#define _TEUX_H_
#include "ICapteur.h"

class Yeux : public ICapteur {
private:
  double distance_min;
  double distance_max;
  float champ_vision;

public:
  Yeux(double distance_min, double distance_max, double champ_vision,
       float capacite);
  ~Yeux() override = default;
  bool JeTePercoit(int x, int y, double orientation,
                   const Bestiole &b) const override;
};

#endif // _TEUX_H_
