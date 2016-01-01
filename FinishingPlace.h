#ifndef FINISHING_PLACE_H
#define FINISHING_PLACE_H

#include "Place.h"
#include <vector>
#include <string>
#include <time.h>
#include "variables.h"

class FinishingPlace : public Place {
public:
    FinishingPlace(Place* wayBack, std::string being_name);
    std::vector<Place*> getWayForth();
    std::string getType();
};
#endif
