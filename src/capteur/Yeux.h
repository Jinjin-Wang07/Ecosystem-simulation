#if !defined(_TEUX_H_)
#define _TEUX_H_

class Yeux
{
private:
    double distance_max;
    double distance_min;
    double champ_vision;
public:
    Yeux(double dist_min, double dist_max, double champ_vision);
    ~Yeux();
};

#endif // _TEUX_H_
