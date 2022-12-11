#include "Aquarium.h"

#include "../../include/LogUtil.h"
#include "Milieu.h"

Aquarium::Aquarium(int width, int height, int _delay)
    : CImgDisplay(), delay(_delay) {

  int screenWidth = 1280;  // screen_width();
  int screenHeight = 1024; // screen_height();

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

  while (!is_closed()) {

    // cout << "iteration de la simulation" << endl;

    if (is_key()) {
      cout << "Vous avez presse la touche "
           << static_cast<unsigned char>(key());
      cout << " (" << key() << ")" << endl;
      if (is_keyESC())
        close();
    }

    flotte->step();
    display(*flotte);

    wait(delay);

  } // while
}
