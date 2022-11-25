#if !defined(_CAMOUFLAGE_H_)
#define _CAMOUFLAGE_H_

class Camouflage
{
private:
    float prob_detecte;
public:
    Camouflage(float prob_detecte);
    ~Camouflage();

    /*
    * Getters and Setters
    */
    void set_prob_detecte(float prob_detecte);
    float get_prob_detecte();
};


#endif // _CAMOUFLAGE_H_
