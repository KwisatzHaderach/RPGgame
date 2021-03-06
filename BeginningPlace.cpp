#include "BeginningPlace.h"

using namespace std;

BeginningPlace::BeginningPlace():Place() {
    int choice = rand() % 3;
    this->wayForth = {};
    this->wayBack = NULL;
    if (rand() % 3 - choice > 0)
        this->being = new NPC();
    else this->being = NULL;
    if (rand() % 3 > 0)
        this->item = new Item(GameVariables::year);
    else this->item = NULL;
    this->text = this->choose_text[choice];
    this->answers.push_back("Go to some other city");
    if (this->being)
        this->answers.push_back("There is " + this->being->getName()
                                + " choose to interact with him");
    if (this->item)
        this->answers.push_back("You can see " + this->item->getName()
                                + " lying on the ground");
    for (unsigned int i = 0; i < this->choose_answers[choice].size(); ++i)
        this->answers.push_back(this->choose_answers[choice][i]);
}

string BeginningPlace::getType() {
    return "beginning";
}

vector<string> BeginningPlace::choose_text = {
        "You find yourself at the entrance to the city.",
        "You see a small village spreading ahead of you.",
        "You see a large tunel entrance ahead of you."};
vector<vector<string>> BeginningPlace::choose_answers = {
        {"You can go through main street straight ahead",
         "Choose a small side street"},
        {"Go towards village center",
         "Go through side street on the side"},
        {"Tunnel divides after few meters, you can go left",
         "or you can go right"}};
