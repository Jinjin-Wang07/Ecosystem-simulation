#if !defined(_CARAPACE_H_)
#define _CARAPACE_H_

#include"IAccessoire.h"

class Carapace : public virtual IAccessoire
{

private:
    float coefficient_meurt;
    float facteur_vitesse;
public:
    Carapace(float coefficient_meurt, float facteur_vitesse);
    ~Carapace();

    /*
    * Getters and Setters
    */
    void set_coefficient_meurt(float coefficient_meurt);
    float get_coefficient_meurt();

    void set_facteur_vitesse(float facteur_vitesse);
    float get_facteur_vitesse();
};


#endif // _CARAPACE_H_
