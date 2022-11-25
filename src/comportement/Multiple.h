#include "Comportement.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include "Gregaire.h"
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