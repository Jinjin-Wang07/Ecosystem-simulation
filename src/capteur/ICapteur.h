#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

using namespace std;


class ICapteur
{
private:
    /* coef */
    double capacite_detection;
    
public:
    virtual ~ICapteur();
    virtual bool jeTePercoit(int x,int y ,double orientation,const Bestiole&);
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