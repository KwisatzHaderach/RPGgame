#include "Finale.h"

using namespace std;
Finale* Finale::instance;

Finale::Finale():City("Gallifrey") {
    this->startingPlace = new FinishingPlace(NULL, "Rassilon");
}

Finale* Finale::getInstance() {
    if (!instance)
        instance = new Finale();
    return instance;
}

Finale::~Finale() {
    delete instance;
}
