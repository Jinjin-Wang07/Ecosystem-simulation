#if !defined(_OREILLES_H_)
#define _OREILLES_H_

class Oreilles: public ICapteur{
private:
    float distance_max;
    float distance_min;
    
public:
    Oreilles(float, float);
    ~Oreilles();
};

#endif // _OREILLES_H_
