#include "Milieu.h"
#include "../../include/LogUtil.h"
#include "../factory/BestiolFactory.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height)
    : UImg(_width, _height, 1, 3), width(_width), height(_height) {

  LOG_INFO("Construction du Milieu");

  std::srand(time(NULL));
}

Milieu::~Milieu(void) { LOG_INFO("Destruiction du Milieu"); }

void Milieu::step(void) {

  cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
  std::vector<Bestiole> clones;
  bool createNewBestioles =
      bestioleFac &&
      bestioleFac->can_add_bestiole(listeBestioles.size()) &&
      bestioleFac->birth_rate > bestioleFac->get_ramdom_value(0, 1);
  for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ++it) {
    it->action(*this);
    if (createNewBestioles && bestioleFac &&
        bestioleFac->clone_probability > bestioleFac->get_ramdom_value(0, 1)) {
      auto clone = bestioleFac->clone_bestiole(*it);
      while (clone.isCollidingWith(*it)) {
        clone.bouge(getWidth(), getHeight());
      }
      clones.push_back(move(clone));
    }
  } // for
  for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ++it) {
    for (auto it2 = next(it); it2 != listeBestioles.end(); ++it2) {
      if (it->isCollidingWith(*it2)) {
        show_collision(*it);
        num_collision++;
        handleCollision(*it);
        handleCollision(*it2);
      }
    }
  }
  for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ++it) {
    it->draw(*this);
  }


  auto firstBestioleToErase =
      remove_if(listeBestioles.begin(), listeBestioles.end(),
                [](Bestiole const &b) { return b.isDead(); });

  for(auto it = firstBestioleToErase; it!=listeBestioles.end(); ++it){
    num_death++;
  }
  
  listeBestioles.erase(firstBestioleToErase, listeBestioles.end());


  listeBestioles.insert(listeBestioles.end(),
                        make_move_iterator(clones.begin()),
                        make_move_iterator(clones.end()));

  if (createNewBestioles) {
    listeBestioles.emplace_back(bestioleFac->create_bestiole());
  }

  show_statistic_info();
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

void Milieu::handleCollision(Bestiole &b) {
  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0, 1);
  bool kill = b.get_fragility() > dis(gen);

  if (kill) {
    b.kill();
    return;
  }

  b.setOrientation(b.getOrientation() + M_PI);
  b.bouge(getWidth(), getHeight());
}

void Milieu::setBestioleFactory(BestiolFactory *bf) { this->bestioleFac = bf; }

void Milieu::show_collision(Bestiole &b){
  Couleur color = {139, 0, 0};
  draw_circle(b.getCoordinates().first, b.getCoordinates().second,  10, color.data());
}

void Milieu::show_statistic_info(){
  int h = 30;
  Couleur color = {0, 0, 0};
  // draw_text(0, INFO_BAR_HEIGHT, "Hello", 0, 0, 1);
  if(bestioleFac != nullptr){
    std::string c = "Number of bestiole : " + to_string(listeBestioles.size());
    draw_text(0,MILIEU_HEIGHT+h, c.c_str() , color.data(),0,1,24);
    h+=30;
    // show the number of bestiole of each comportement
    std::unordered_map<std::string, int> countComportement;
    for (auto const& b : listeBestioles) {
      countComportement[b.get_comportement_name()]++;
    }
    for(auto const& elem : countComportement)
    {
      std::string info = elem.first + " : " + to_string(elem.second);
      draw_text(0, MILIEU_HEIGHT+h, info.c_str(), color.data(),0,1,24);
      h+=30;
    }
    // show the number of death and collision
    std::string n_death = "Number of death : " + to_string(num_death);
    std::string n_collision = "Number of collision : " + to_string(num_collision);
    draw_text(350, MILIEU_HEIGHT+30, n_death.c_str() , color.data(),0,1,24);
    draw_text(350, MILIEU_HEIGHT+60, n_collision.c_str() , color.data(),0,1,24);

  }
}