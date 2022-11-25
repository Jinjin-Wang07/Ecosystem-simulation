#include "Bestiole.h"

#include "../environment/Milieu.h"

#include <cstdlib>
#include <cmath>



int               Bestiole::next_id = 0;


Bestiole::Bestiole(int x,int y,double max_vitesse,int age_limit,double fragility)
{
   identite = ++next_id;
   // position variables
   x =x;
   y=y;

   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
   

   max_vitesse_with_acc=max_vitesse;
   
   // other variables
   age=0;
   age_limit=age_limit;
   fragility=fragility;

   //affichage
   AFF_SIZE=10
   double            cumulX, cumulY; 
 
   std::vector<IAccessoire> list_accessoire;
   std::vector<ICapteur> list_capteurs;
   identite = ++next;

   cout << "const PreviousBestiole (" << identite << ") par defaut" << endl;


   cumulX = cumulY = 0.;
   
   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

}


Bestiole::Bestiole(const Bestiole & b)
{
   //TODO : update
   identite = ++next;

   cout << "const PreviousBestiole (" << identite << ") par copie" << endl;

   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   couleur = new T[ 3 ];
   memcpy( couleur, b.couleur, 3*sizeof(T) );

}


Bestiole::~Bestiole( void )
{

   delete[] couleur;
   cout << "dest PreviousBestiole" << endl;

}


// void Bestiole::initCoords( int xLim, int yLim )
// {

//    x = rand() % xLim;
//    y = rand() % yLim;

// }


void Bestiole::bouge( int xLim, int yLim )
{
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;


   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }

}


void Bestiole::action( Milieu & monMilieu )
{

   bouge( monMilieu.getWidth(), monMilieu.getHeight() );

}


void Besiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{

   return ( b1.identite == b2.identite );

}


bool Bestiole::jeTePercoit( const Bestiole & b )
{
   double         dist;
   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= LIMITE_VUE );

}

double Bestiole::getOrientation() {
   return this.orientation;
}

void Bestiole::setOrientation(double o) {
   this.orientation = o;
}

void Bestiole::setVitesse(double o) {
    this->vitesse = o;
}
