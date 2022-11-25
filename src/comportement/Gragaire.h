//
// Created by Lenovo on 2022/11/25.
//

#ifndef ECOSYSTEM_SIMULATION_GRAGAIRE_H
#define ECOSYSTEM_SIMULATION_GRAGAIRE_H

#include "IComportement.h"
#include "bestiole/Bestiole.h"

class Gragaire :  public IComportement{

public:
    Gragaire( void );

    ~Gragaire( void );

    void move(const Bestiole & b, vector<Bestiole> seen_neighbors);

private:

    double calculateAverageDirection (vector<Bestiole> seen_neighbors);

};
#endif //ECOSYSTEM_SIMULATION_GRAGAIRE_H
