#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

#include "../../include/HMI/CImg.h"
#include <iostream>
#include <map>
#include <string.h>

using namespace std;
using namespace cimg_library;

class Milieu;

class Aquarium : public CImgDisplay {

private:
  Milieu *flotte;

  unsigned int sleep_time;

  int delay;

public:
  Aquarium(int width, int height, int _delay);
  ~Aquarium(void);

  void run(void);

  Milieu &getMilieu(void) { return *flotte; }

  /*
   * Summary : show statistic informations
   * Return : statistic informations
   */
  void showInfo();

  /*
   * Summary : return statistic informations
   * Parameter: Reference of a map to store information
   * Return : success
   */
  bool getInfo(map<string, float> &info);
};

#endif
