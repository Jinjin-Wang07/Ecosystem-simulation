#if !defined(_OREILLES_H_)
#define _OREILLES_H_
#include "ICapteur.h"

class Oreilles : public ICapteur {
private:
    double distance_min;
    double distance_max;
    
public:
    Oreilles(double distance_min,double distance_max,double capacite_detection);
    //~Oreilles();
    bool JeTePercoit(int x,int y,double orientation,const Bestiole& b) const override;
};

#endif // _OREILLES_H_
