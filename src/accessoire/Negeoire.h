#if !defined(_NEGEOIRE_H_)
#define _NEGEOIRE_H_

#include"IAccessoire.h"

class Negeoire : public virtual IAccessoire
{
private:
    float coef_vitesse;

public:
    Negeoire(float coef_vitesse);
    ~Negeoire();

    float get_coef_vitesse();
    void set_coef_vitesse(float coef_vitesse);
};


#endif // _NEGEOIRE_H_


