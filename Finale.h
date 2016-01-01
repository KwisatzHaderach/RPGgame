#ifndef FINALE_H
#define FINALE_H

#include "City.h"
#include "FinishingPlace.h"

class Finale : public City {
private:
    static Finale* instance;

    Finale();
public:
    static Finale* getInstance();
    ~Finale();
};
#endif
