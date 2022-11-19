#include "./environment/Aquarium.h"
#include "./environment/Milieu.h"
#include "./bestiole/Bestiole.h"

#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );

   for ( int i = 1; i <= 20; ++i )
      ecosysteme.getMilieu().addMember( Bestiole() );
   ecosysteme.run();


   return 0;

}
