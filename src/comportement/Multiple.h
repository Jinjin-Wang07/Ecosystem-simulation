#ifndef MULTIPLE
#define MULTIPLE
#include "IComportement.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include "Gragaire.h"
#include "Peureuse.h"
#include <vector>
using namespace std;
class Multiple : public IComportement{
private:
    vector<IComportement> comportements;
public:
    Multiple();
    ~Multiple();
    void move(const Bestiole &b, vector<Bestiole> const& seen_neighbors);



};
#endif
