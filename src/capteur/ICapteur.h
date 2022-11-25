#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

using namespace std;

class Milieu; // ??? why not aquarium...

class ICapteur
{
private:
    /* coef */
    float distance;
    float capacite_detection;
    
public:
    virtual ~ICapteur();

    /*
    * Return the distance coefficient
    */
    virtual float get_distance();

    /*
    * Return the distance coefficient
    */
    virtual float get_capacite_detection();

};

#endif