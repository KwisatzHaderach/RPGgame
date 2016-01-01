#ifndef CITY_H
#define CITY_H

#include <string>
#include "Place.h"
#include "BeginningPlace.h"

class City {
private:
    std::string name;
    bool finished;
protected:
    Place* startingPlace;

public:
    City(std::string name);
    std::string getName();
    Place* getStartingPlace();
    void setStartingPlace(Place* place);
    bool getFinished();
    void setFinished(bool finished);
    ~City();
};
#endif
