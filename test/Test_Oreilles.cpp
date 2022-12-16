#include<gtest/gtest.h>
#include <vector>
#include <array>
#include <iostream>
#include <memory>
// #include "../src/capteur/Oreilles.h"
#include "MockBestiole.h"

using ::testing::Return;

bool JeTePercoit(int x, int y, double orientation,
                           const Bestiole &b){
  double distance_min = 10;
  double distance_max = 20;

  double capacite_detection = 1;


  auto coordinates = b.getCoordinates();
  auto bx = coordinates.first;
  auto by = coordinates.second;
  double dist = std::sqrt((x - bx) * (x - bx) + (y - by) * (y - by));
  return ((dist <= distance_max) && (dist >= distance_min) &&
          (capacite_detection > b.get_camouflage_coef())); //
}

TEST(OreillesTest, JeTePercoitTest){
    int x_b1 = 0;
    int y_b1 = 0;
    double orientation_b1 = M_PI/4;

    int x_b2 = 10;
    int y_b2 = 10;
    pair<double, double> coord = make_pair(x_b2, y_b2);

    double vitesse = 10;
    double max_vitesse = 20;
    double age_limit = 1000;
    double fragility = 0;
    double camouflage_coef = 1;
    double orientation = 0;


    MockBestiole mock_bestiole(x_b2, y_b2, vitesse, max_vitesse, age_limit,
           fragility, camouflage_coef,
           orientation);

    EXPECT_CALL(mock_bestiole, get_camouflage_coef())
    .WillRepeatedly(Return(1));

    EXPECT_CALL(mock_bestiole, getCoordinates())
    .WillRepeatedly(Return(coord));

    EXPECT_FALSE(JeTePercoit(x_b1, y_b1, orientation_b1, mock_bestiole));
}

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}