#if !defined(_BESTIOL_FACTORY_H_)
#define _BESTIOL_FACTORY_H_

#include <iostream>
#include <string.h>
#include <map>

#include "../bestiole/Bestiole.h"

using namespace std;

class BestiolFactory
{
    private:

    public:
        map<string,double> total_num_bestiole;
        map<string,double> curr_num_bestiole; // {specie_name : number}
        tuple<float, float> eye_champ_angulaire_limit;
        tuple<float, float> eye_distance_limit;
        tuple<float, float> eye_capacite_detection_limit;

        tuple<float, float> ear_distance_limit;
        tuple<float, float> ear_capacite_detection_limit;

        float nageoire_speed_coef_max;
        float carapace_resistance_coef_max;
        float carapace_speed_coef_max;

        float camouflage_coef_max;

        int max_age;

        float birth_rate;
        float clone_probability;

        float bestioles_comportement_distribution[5];

    public:
        /*
        * Create a bestiolFactory with all default value
        */
        BestiolFactory();
        ~BestiolFactory();


        /*
        *   create a default bestiole
        */
        Bestiole create_bestiole();

        /*
        *   Reset the factory variables to default
        */
        void reset_factory();
};

#endif // _BESTIOL_FACTORY_H_
