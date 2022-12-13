#if !defined(_CAMOUFLAGE_H_)
#define _CAMOUFLAGE_H_

/* *
 * A bug with a camouflage will be more difficult to detect by other bugs.
 */
class Camouflage
{
private:
    /* the capacity of camouflage */
    float prob_detecte;
public:
    /* the Camouflage constructor */
    Camouflage(float prob_detecte);
    /* the Camouflage destructor */
    ~Camouflage();

  /*
   * Getters and Setters
   */
  void set_prob_detecte(float prob_detecte);
  float get_prob_detecte();
};

#endif // _CAMOUFLAGE_H_
