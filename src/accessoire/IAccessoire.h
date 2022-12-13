#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_

using namespace std;

class Milieu; // ??? why not aquarium...
/*
 * Interface of accessories
 */
class IAccessoire
{
private:
  /* coef */
public:
  virtual ~IAccessoire();

  /*
   * TODO : Accessoires don't have same coefficient
   */
  float get();
};

#endif