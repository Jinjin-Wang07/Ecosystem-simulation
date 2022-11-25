#if !defined(_OREILLES_H_)
#define _OREILLES_H_

class Oreilles: public ICapteur{
private:
    
    double distance_min;
    double distance_max;
    
public:
    Oreilles(double distance_min,double distance_max,double capacite_detection);
    ~Oreilles();
};

#endif // _OREILLES_H_
