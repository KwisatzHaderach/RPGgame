#include "DeadEnd.h"

using namespace std;

DeadEnd::DeadEnd(Place* wayBack) {
    this->wayBack = wayBack;
    this->wayForth = {};
    if (rand() % 4 > 0)
        this->item = new Item(GameVariables::year);
    else this->item = NULL;
    if (rand() % 4 == 0)
        this->being = new NPC();
    else this->being = NULL;
    this->text = this->choose_text[rand() % 3];
    this->answers.push_back("Go back to previous location");
    if (this->being)
        this->answers.push_back("There is " + this->being->getName()
                                + " choose to interact with him");
    if (this->item)
        this->answers.push_back("You can see " + this->item->getName()
                                + " lying on the ground");
}

string DeadEnd::getType() {
    return "deadend";
}

vector<string> DeadEnd::choose_text = {
        "There is a room with only one way in and out.",
        "The road just ends with no way further.",
        "There is a huge hole in the ground, you can't get across."};
