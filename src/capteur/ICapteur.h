
#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

using namespace std;

class Bestiole;
class ICapteur
{
   
public:
    float distance;
    float capacite_detection;
    //virtual ~ICapteur();
    virtual bool JeTePercoit(int x,int y,double orientation,const Bestiole& b) const = 0 ;

};

#endif