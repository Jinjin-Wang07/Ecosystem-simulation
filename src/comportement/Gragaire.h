//
// Created by Lenovo on 2022/11/25.
//

#ifndef ECOSYSTEM_SIMULATION_GRAGAIRE_H
#define ECOSYSTEM_SIMULATION_GRAGAIRE_H

#include "IComportement.h"

class Gragaire :  public IComportement{

public:
    Gragaire( void );

     ~Gragaire( void ) override;

    void move( Bestiole & b, std::vector<Bestiole const*> const& seen_neighbors) override;
    std::unique_ptr<IComportement> clone() const override;

private:

    double calculateAverageDirection (double my_orientation, std::vector<Bestiole const*> const& seen_neighbors);

};
#endif //ECOSYSTEM_SIMULATION_GRAGAIRE_H
