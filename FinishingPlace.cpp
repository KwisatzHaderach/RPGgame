#include "FinishingPlace.h"

using namespace std;

FinishingPlace::FinishingPlace(Place* wayBack, string being_name):Place() {
    this->wayBack = wayBack;
    this->wayForth = {};
    this->item = NULL;
    this->being = new NPC(being_name);
    this->text = "This is the end of this town. To finish this city you have "
                 "to interact with ";
    this->text += this->being->getName();
    this->answers.push_back("Go back to previous location");
    this->answers.push_back("Interact with " + this->being->getName());
}

string FinishingPlace::getType() {
    return "finish";
}
