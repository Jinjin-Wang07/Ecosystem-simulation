#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "../../include/HMI/UImg.h"
#include "../bestiole/Bestiole.h"
#include "../constants.h"

#include <iostream>
#include <vector>

class BestiolFactory;

class Milieu : public UImg {

private:
  static const T white[];

  int width, height;
  std::vector<Bestiole> listeBestioles;

  BestiolFactory *bestioleFac;

  void show_collision(Bestiole &b);
  void show_statistic_info();

public:
  int num_death = 0;
  int num_collision = 0;


  Milieu(int _width, int _height);
  ~Milieu(void);

  int getWidth(void) const { return width; };
  int getHeight(void) const { return (height - INFO_BAR_HEIGHT) ;};

  void step(void);

  void addMember(const Bestiole &b) { listeBestioles.push_back(b); }
  std::vector<Bestiole const *> getVoisins(const Bestiole &b) const;
  int nbVoisins(const Bestiole &b) const;
  void handleCollision(Bestiole &b);

  void setBestioleFactory(BestiolFactory *bf);
};

#endif
