//
// Created by Lenovo on 2022/11/25.
//

#ifndef ECOSYSTEM_SIMULATION_ICOMPORTEMENT_H
#define ECOSYSTEM_SIMULATION_ICOMPORTEMENT_H

#include "bestiole/Bestiole.h"
/*
 * the interface for bug's behaviors
 */
class IComportement {

public:

    virtual ~IComportement(){};

    virtual void move(const Bestiole & b, vector<Bestiole> seen_neighbors) = 0;

};
#endif //ECOSYSTEM_SIMULATION_ICOMPORTEMENT_H
