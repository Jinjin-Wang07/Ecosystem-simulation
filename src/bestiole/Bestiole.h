#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "../../include/HMI/UImg.h"
#include "accessoire/IAccessoire.h"
#include "capteur/ICapteur.h"

#include <iostream>

using namespace std;


class Milieu;


class Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static int              next;

private :
   int               identite;
   int               x, y;            // position pixel
   double            cumulX, cumulY; // c'est pour affichage
   double            orientation;
   double            vitesse;

   T               * couleur;

private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   ~Bestiole( void );                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );

   /*
      add accessoire
   */
   bool add_accessoire(IAccessoire acc);

   /*
      add capteur
   */
   bool add_capteur(ICapteur capteur);


   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

};


#endif
