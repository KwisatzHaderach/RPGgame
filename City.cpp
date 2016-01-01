#include "City.h"

using namespace std;

City::City(string name) {
    this->name = name;
    this->finished = false;
    this->startingPlace = NULL;
}

string City::getName() {
    return this->name;
}

Place* City::getStartingPlace() {
    return this->startingPlace;
}

void City::setStartingPlace(Place *place) {
    this->startingPlace = place;
}

bool City::getFinished() {
    return this->finished;
}

void City::setFinished(bool finished) {
    this->finished = finished;
}

City::~City() {
    delete this->startingPlace;
}
