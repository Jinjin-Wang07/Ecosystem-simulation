#include "gmock/gmock.h"  // Brings in gMock.
#include "../src/bestiole/Bestiole.h"



class MockBestiole : public Bestiole {
 public:
  MockBestiole(int x, int y, double vitesse, double max_vitesse, int age_limit,
           double fragility, double camouflage_coef,
           double orientation): Bestiole(x, y, vitesse, max_vitesse, age_limit,
           fragility, camouflage_coef,
           orientation){}

  MOCK_METHOD(double, get_camouflage_coef, (), (const, override));
  MOCK_METHOD((pair<double, double>), getCoordinates, (), (const, override));
};