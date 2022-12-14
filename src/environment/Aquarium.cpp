#include "Aquarium.h"

#include "../../include/LogUtil.h"
#include "Milieu.h"

#include <unistd.h>

Aquarium::Aquarium(int width, int height, int _delay)
    : CImgDisplay(), delay(_delay) {

  int screenWidth = 1280;  // screen_width();
  int screenHeight = 1024; // screen_height();

  sleep_time = 10000;


  LOG_INFO("Construiction de l'Aquarium");

  flotte = new Milieu(width, height);
  assign(*flotte, "Simulation d'ecosysteme");

  move(static_cast<int>((screenWidth - width) / 2),
       static_cast<int>((screenHeight - height) / 2));
}

Aquarium::~Aquarium(void) {
  delete flotte;
  LOG_INFO("Destruiction de l'Aquarium");
}

void Aquarium::run(void) {
  LOG_INFO("Running l'Aquarium");
  bool stop = false;


  while (!is_closed()) {

    // cout << "iteration de la simulation" << endl;

    if (is_key()) {
      if(is_keyS()){
        stop = true;
        continue;
      }
      if(is_keyC()){
        stop = false;
        continue;
      }

      // cout << "Vous avez presse la touche "
          //  << static_cast<unsigned char>(key());
      // cout << " (" << key() << ")" << endl;
      if (is_keyESC()){
        close();
      }

      if(is_keyARROWDOWN() && sleep_time<=60000){
          this->sleep_time += 500; 
          LOG_INFO("Slow down the simulation speed : %d", sleep_time);
      } else if (is_keyARROWUP() && sleep_time>=10000){
          this->sleep_time -= 500;
          LOG_INFO("Speed up the simulation speed : %d", sleep_time);
      }
    }
    if(stop){
      usleep(10000);
      continue;
    }

    flotte->step();
    display(*flotte);

    // same effet...
    usleep(sleep_time);
    wait(delay);

  } // while
}
