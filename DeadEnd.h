#ifndef DEAD_END_H
#define DEAD_END_H

#include "Place.h"
#include <vector>
#include <time.h>
#include <string>
#include "variables.h"

class DeadEnd : public Place {
public:
    static std::vector<std::string> choose_text;

    DeadEnd(Place* wayBack);
    std::vector<Place*> getWayForth();
    std::string getType();
};
#endif
