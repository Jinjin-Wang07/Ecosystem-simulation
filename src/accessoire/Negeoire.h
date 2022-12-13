#if !defined(_NEGEOIRE_H_)
#define _NEGEOIRE_H_

#include"IAccessoire.h"
/* *
 * A bug with a Negeoire will move faster.
 */
class Negeoire : public virtual IAccessoire
{
private:
    /* the multiplier coefficient of the speed*/
    float coef_vitesse;

public:
    /*
     * the Negeoire constructor with coef_vitesse parameter
     */
    Negeoire(float coef_vitesse);
    /*
     * the Negeoire destructor
     */
    ~Negeoire();

    /*
    * Getters and Setters for the coef_vitesse parameter
    */
    float get_coef_vitesse();
    void set_coef_vitesse(float coef_vitesse);
};

#endif // _NEGEOIRE_H_
