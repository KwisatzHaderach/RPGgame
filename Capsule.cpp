#include "Capsule.h"

using namespace std;
Capsule* Capsule::instance;

Capsule::Capsule():City("TARDIS") {
    this->working = true;
    GameVariables::year = 2015;
}

Capsule* Capsule::getInstance() {
    if (!instance)
        instance = new Capsule();
    return instance;
}

bool Capsule::getWorking() {
    return this->working;
}

void Capsule::setWorking(bool working) {
    this->working = working;
}

int Capsule::getYear() {
    return GameVariables::year;
}

void Capsule::setYear(int year) {
    if (!this->working) {
        cout << "Your TARDIS isn't working" << endl;
        return;
    }
    GameVariables::year = year;
    srand(time(NULL));
    if (rand() % 10 == 0) {
        cout << "Your TARDIS has broken down, no time travel from now on" << endl;
        this->setWorking(false);
    }
}

Capsule::~Capsule() {
    delete instance;
}
