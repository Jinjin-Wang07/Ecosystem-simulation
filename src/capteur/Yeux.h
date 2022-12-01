#if !defined(_TEUX_H_)
#define _TEUX_H_

class Yeux {
private:
  float champ_vision;

public:
  Yeux(float, float, float);
  ~Yeux();

  float set_champ_vision(float);
  float get_champ_vision();
};

#endif // _TEUX_H_
