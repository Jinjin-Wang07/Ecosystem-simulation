#if !defined(_CARAPACE_H_)
#define _CARAPACE_H_

#include"IAccessoire.h"
/* *
 * A bug equipped with a carapace is more resistant to a collision with another bug
 * other insect.However, the speed of movement is reduced/
 */
class Carapace : public virtual IAccessoire
{

private:
    /* the probability of death when a conflict happens*/
    float coefficient_meurt;
    /* the ratio of speed reduction*/
    float facteur_vitesse;
public:
    /* the Carapace constructor with coefficient_meurt and facteur_vitesse parameters*/
    Carapace(float coefficient_meurt, float facteur_vitesse);
    /* the Carapace destructor */
    ~Carapace();

    /*
    * Getters and Setters for the coefficient_meurt parameter
    */
    void set_coefficient_meurt(float coefficient_meurt);
    float get_coefficient_meurt();

    /*
     * Getters and Setters for the facteur_vitesse parameter
     */
    void set_facteur_vitesse(float facteur_vitesse);
    float get_facteur_vitesse();
};

#endif // _CARAPACE_H_
