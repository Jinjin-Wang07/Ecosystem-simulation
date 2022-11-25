#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "../../include/HMI/UImg.h"
#include "../accessoire/IAccessoire.h"
#include "../capteur/ICapteur.h"

#include <iostream>

using namespace std;


class Milieu;


class Bestiole
{


private :
   static int next_id;
   int identite;
   
   // position variables
   int x;
   int y;
   double vitesse;
   double orientation;
   double max_vitesse;
   
   // other variables
   int age;
   int age_limit;
   double fragility;

   //affichage
   static const double AFF_SIZE;
   double            cumulX, cumulY; 
   T* couleur;
   IAccessoire* list_accessoire;
   ICapteur* list_capteurs;


private :
   void bouge( int xLim, int yLim );

public :// Forme canonique :
   Bestiole(int x,int y,double max_vitesse,int age_limit,double fragility);                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur                              // Operateur d'affectation binaire par defaut
   
   void addAccessoire(IAccessoire acc);
   void addCapteur(ICapteur capteur);

   void action( Milieu & monMilieu );

   bool jeTePercoit( const Bestiole & b ) const;
   void changeState();
   void draw( UImg & support );


   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

};


#endif
