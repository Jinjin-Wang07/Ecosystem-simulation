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
  // move already
  void draw(UImg &support, double xt, double yt, double orientation) override;
  bool JeTePercoit(int x, int y, double orientation,
                   const Bestiole &b) const override;

  std::unique_ptr<ICapteur> clone() const override;
};

#endif // _TEUX_H_
