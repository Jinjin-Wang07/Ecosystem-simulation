#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include "../../include/HMI/UImg.h"
#include "../accessoire/IAccessoire.h"
#include "../capteur/ICapteur.h"

#include <array>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class IComportement;
class Milieu;

using Couleur = array<T, 3>;
class Bestiole {

private:
  // position variables
  int x;
  int y;
  double vitesse;
  double orientation;
  double max_vitesse;

  /**
   * fragility = [0, 1] (Probabilite de mort)
   */
  double fragility;

  double camouflage_coef;

  // affichage
  double cumulX, cumulY;
  std::vector<unique_ptr<ICapteur>> list_capteurs;

  unique_ptr<IComportement> comportement;

  bool alive = true;

public: // Forme canonique :
  int identite;
  // other variables
  int age;
  int age_limit;

  Bestiole(int x, int y, double vitesse, double max_vitesse, int age_limit,
           double fragility, double camouflage_coef,
           double orientation); // Constructeur par defaut
  Bestiole(const Bestiole &b);  // Constructeur de copies
  Bestiole(Bestiole &&b);       // Move constructeur

  Bestiole &operator=(Bestiole const &b);

  ~Bestiole(); // Destructeur                              // Operateur
               // d'affectation binaire par defaut

  void bouge(int xLim, int yLim);

  void addAccessoire(IAccessoire acc);
  void addCapteur(ICapteur *capteur);
  void setComportement(unique_ptr<IComportement> comportement);

  void action(Milieu &monMilieu);

  bool jeTePercoit(const Bestiole &b) const;
  void changeState();
  void draw(UImg &support);
  double get_camouflage_coef() const;
  void set_camouflage_coef(double) { this->camouflage_coef = camouflage_coef; };

  double getOrientation() const;
  void setOrientation(double o);

  pair<double, double> getCoordinates() const;

  void setVitesse(double o);
  double get_vitesse() const { return this->vitesse; };
  double get_max_vitesse() const { return this->max_vitesse; };

  friend bool operator==(const Bestiole &b1, const Bestiole &b2);

  void addAccessoire(double speed_multiplier, double fragility_multiplier,
                     double camouflage_mutliplier);

  void set_fragility(double f) { this->fragility = f; };
  double get_fragility() { return this->fragility; };

  void move_capteur(unique_ptr<ICapteur> &&cap);

  bool isCollidingWith(Bestiole const &b) const;
  bool isDead() const;
  void kill();

  string get_comportement_name() const;
};

bool operator!=(const Bestiole &b1, const Bestiole &b2);

#endif
