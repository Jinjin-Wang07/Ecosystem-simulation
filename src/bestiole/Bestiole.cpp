#include "Bestiole.h"

#include "../comportement/IComportement.h"
#include "../constants.h"
#include "../environment/Milieu.h"
#include "../../include/LogUtil.h"


#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>



using namespace std;

int Bestiole::next_id = 0;

Bestiole::Bestiole(int x, int y, 
                    double vitesse, double max_vitesse, int age_limit, double fragility,
                    double camouflage_coef, double orientation){

  identite = ++next_id;

  // Initialization
  this->x = x;
  this->y = y;

  this->vitesse = vitesse;
  this->max_vitesse = max_vitesse;
  this->age_limit = age_limit;
  this->fragility = fragility;
  this->camouflage_coef = camouflage_coef;
  this->orientation = orientation;
  
  this->age = 0;

  std::vector<std::unique_ptr<ICapteur>> list_capteurs;

  LOG_DEBUG("Construire Bestiole[%d] par default", this->identite);

  cumulX = cumulY = 0.;

  couleur = new T[3];
  couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
}

// TODO move construteur
Bestiole::Bestiole(const Bestiole &b) {
  // TODO : update
  identite = b.identite;

  LOG_DEBUG("Construire Bestiole[%d] par copy", this->identite);

  x = b.x;
  y = b.y;
  cumulX = cumulY = 0.;

  this->vitesse = b.vitesse;

  // other variables
  this->age = b.age;
  this->age_limit = b.age_limit;
  this->fragility = b.fragility;


   //TODO : copy list_accesoire
   //list_accessoire = b.list_accessoire;
   
  //  vector<std::unique_ptr<ICapteur>> new_capteurs;
   for (auto const& capteur : b.list_capteurs) {
      list_capteurs.push_back(move(capteur->clone()));
   }//clone all the capteurs

  if (b.comportement) {
    comportement = b.comportement->clone();
  }//clone the comportement

  orientation = b.orientation;
  vitesse = b.vitesse;
  couleur = new T[3];
  memcpy(couleur, b.couleur, 3 * sizeof(T));
}

Bestiole::~Bestiole(void) {
  delete[] couleur;
  LOG_DEBUG("Destruire Bestiole[%d]", this->identite);
}


// Move Constructeur
Bestiole::Bestiole(Bestiole&& b): identite(b.identite), x(b.x), y(b.y),vitesse(b.vitesse) {

  LOG_DEBUG("Construire Bestiole[%d] par move", this->identite);
  
  cumulX = cumulY = 0.;

  

  // other variables
  this->age = b.age;
  this->age_limit = b.age_limit;
  this->fragility = b.fragility;

  // vector<std::unique_ptr<ICapteur>> new_capteurs;
  // for (auto const& capteur : b.list_capteurs) {
  //     list_capteurs.push_back(move(capteur));
      
  //  }//clone all the capteurs

  list_capteurs = move(b.list_capteurs);

  comportement = std::move(b.comportement);

  orientation = b.orientation;
  vitesse = b.vitesse;
  couleur = b.couleur;


  b.couleur = NULL;
}


void Bestiole::bouge(int xLim, int yLim) {

  double nx, ny;
  double dx = cos(orientation) * vitesse;
  double dy = -sin(orientation) * vitesse;
  int cx, cy;

  cx = static_cast<int>(cumulX);
  cumulX -= cx;
  cy = static_cast<int>(cumulY);
  cumulY -= cy;

  nx = x + dx + cx;
  ny = y + dy + cy;

  if ((nx < 0) || (nx > xLim - 1)) {
    orientation = M_PI - orientation;
    cumulX = 0.;
  } else {
    x = static_cast<int>(nx);
    cumulX += nx - x;
  }

  if ((ny < 0) || (ny > yLim - 1)) {
    orientation = -orientation;
    cumulY = 0.;
  } else {
    y = static_cast<int>(ny);
    cumulY += ny - y;
  }
}

void Bestiole::setComportement(unique_ptr<IComportement> comportement) {
  this->comportement = move(comportement);
}

void Bestiole::action(Milieu &monMilieu) {
  const auto seen_neighbors = monMilieu.getVoisins(*this);

  if (comportement) {
    comportement->move(*this, seen_neighbors);
  }

  bouge(monMilieu.getWidth(), monMilieu.getHeight());
}

void Bestiole::draw(UImg &support) {

  double xt = x + cos(orientation) * AFF_SIZE / 2.1;
  double yt = y - sin(orientation) * AFF_SIZE / 2.1;
  
  for (auto const& capteur : list_capteurs){
    capteur->draw(support,xt,yt,orientation);
  }
  
  support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                       -orientation / M_PI * 180., couleur);
  support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);
}

bool operator==(const Bestiole &b1, const Bestiole &b2) {
  return (b1.identite == b2.identite);
}

bool operator!=(const Bestiole &b1, const Bestiole &b2) { return !(b1 == b2); }

bool Bestiole::jeTePercoit(const Bestiole &b) const {
   for (auto const& capteur : list_capteurs) {
      if (capteur->JeTePercoit(
         this->x,
         this->y,
         this->orientation,
         b
      )){
         return true;
      }
   }  
   return false;
}

double Bestiole::getOrientation() const { return this->orientation; }

void Bestiole::setOrientation(double o) { this->orientation = o; }

pair<double, double> Bestiole::getCoordinates() const { return {x, y}; }

void Bestiole::setVitesse(double v) { this->vitesse = v; }

double Bestiole::get_camouflage_coef() const { return this->camouflage_coef; }


/**
 * Fonction pour modifier les parametre par ajouter les accessoire
 */



/**
 * Fonction for adding the capteurs
 */
void Bestiole::move_capteur(unique_ptr<ICapteur>&& cap){
  this->list_capteurs.push_back(move(cap));
  
}
