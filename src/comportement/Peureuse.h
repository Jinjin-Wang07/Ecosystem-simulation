//
// Created by Lenovo on 2022/11/25.
//

#ifndef ECOSYSTEM_SIMULATION_PEUREUSE_H
#define ECOSYSTEM_SIMULATION_PEUREUSE_H

#include "IComportement.h"
#include "bestiole/Bestiole.h"

#define MAX_NEIGHBOR;

#define ESCAPE_VITESSE;

class Peureuse : public IComportement{

public:
    Peureuse();

    ~Peureuse();

    void move(const Bestiole & b, vector<Bestiole> seen_neighbors);


};
#endif //ECOSYSTEM_SIMULATION_PEUREUSE_H
