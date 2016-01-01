#ifndef CAPSULE_H
#define CAPSULE_H

#include "City.h"
#include <time.h>
#include <iostream>
#include "variables.h"

class Capsule : public City {
private:
    bool working;
    static Capsule* instance;

    Capsule();
public:
    static Capsule* getInstance();
    bool getWorking();
    void setWorking(bool working);
    static int getYear();
    void setYear(int year);
    ~Capsule();
};
#endif
