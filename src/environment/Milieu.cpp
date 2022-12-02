#include "Milieu.h"
#include "../../include/LogUtil.h"

#include <cstdlib>
#include <ctime>
#include <vector>



using namespace std;

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height)
    : UImg(_width, _height, 1, 3), width(_width), height(_height) {

  LOG_INFO("Construction du Milieu");

  std::srand(time(NULL));
}

Milieu::~Milieu(void) { LOG_INFO("Destruiction du Milieu");}

void Milieu::step(void) {

  cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
  for (std::vector<Bestiole>::iterator it = listeBestioles.begin();
       it != listeBestioles.end(); ++it) {

    it->action(*this);
    it->draw(*this);

  } 
}

int Milieu::nbVoisins(const Bestiole &b) const {

  int nb = 0;

  for (auto it = listeBestioles.cbegin(); it != listeBestioles.cend(); ++it)
    if (!(b == *it) && b.jeTePercoit(*it))
      ++nb;

  return nb;
}

vector<Bestiole const *> Milieu::getVoisins(const Bestiole &b) const {
  std::vector<Bestiole const *> voisins;

  for (auto const &autre_bestiole : listeBestioles) {
    if (b != autre_bestiole && b.jeTePercoit(autre_bestiole)) {
      voisins.push_back(&autre_bestiole);
    }
  }

  return voisins;
}