#include "Place.h"

using namespace std;

int Place::getClosestYear(int year) {
    if (year < -500) return 0; //-20000
    else if (year < 1500) return 1; //500
    else if (year < 2500) return 2; //2000
    else return 3; //10000
}

Place::Place(Place* wayBack) {
    this->wayBack = wayBack;
    this->wayForth = {};
    if (rand() % 2)
        this->item = new Item(GameVariables::year);
    else this->item = NULL;
    if (rand() % 2)
        this->being = new NPC();
    else this->being = NULL;
    this->answers.push_back("Go back to previous location");
    if (this->being)
        this->answers.push_back("There is " + this->being->getName()
                                + " choose to interact with him");
    if (this->item)
        this->answers.push_back("You can see " + this->item->getName()
                                + " lying on the ground");
}

Place::Place() { }

Place* Place::getWayBack() {
    return this->wayBack;
}

vector<Place*> Place::getWayForth() {
    return this->wayForth;
}

void Place::addWayForth(Place *place) {
    this->wayForth.push_back(place);
}

Item* Place::getItem() {
    return this->item;
}

void Place::removeItem() {
    this->item = NULL;
    if (this->being)
        this->answers.erase(this->answers.begin()+2);
    else this->answers.erase(this->answers.begin()+1);
}

NPC* Place::getBeing() {
    return this->being;
}

void Place::removeBeing() {
    delete this->being;
    this->being = NULL;
    this->answers.erase(this->answers.begin()+1);
}

void Place::printTextWithAnswers() {
    cout << this->text << endl;
    for (unsigned int i = 0; i < this->answers.size(); ++i)
        cout << i+1 << ") " << this->answers[i] << endl;
}

int Place::getAnswersSize() {
    return (int) this->answers.size();
}

void Place::setText() {
    int index = this->getClosestYear(GameVariables::year);
    int choice = rand() % this->choose_text[index].size();
    this->text = this->choose_text[index][choice];
    for (unsigned int i = 0; i < this->wayForth.size(); ++i)
        this->answers.push_back(this->choose_answers[index][i]);
}

string Place::getType() {
    return "place";
}

Place::~Place() {
    delete this->item;
    delete this->being;
    for (unsigned int i = 0; i < this->wayForth.size(); ++i)
        delete this->wayForth[i];
}

vector<vector<string>> Place::choose_text = {
        {"There is a shrine by the road.",
         "You can see a hut nearby, with smoking camp fire.",
         "You are coming to place with animal pelts "
                 "stretched on wooden frames.",
         "You can see a cave with many mysterious murals.",
         "There is a ford nearby."}, //-20000
        {"You are passing by a pub.",
         "You are on a square and you see a broken down fountain.",
         "There is a pier by a river with an anchored ship.",
         "You found yourself by stables.",
         "There is a shrine by the road."}, //500
        {"You see a train station with some vehicles outside.",
         "There is a nice garden behind fence.",
         "You pass by a public library.",
         "There is a church by your side.",
         "You find yourself on an empty road."}, //2000
        {"You see an unused space port close by.",
         "You see a holoprojector running in a nearby pub.",
         "There is a computer terminal, but it's offline.",
         "There is a road with many floating cars parked "
                 "by the side.",
         "You walk by the Ministry of Silly Walks"} //10000
};

vector<vector<string>> Place::choose_answers = {
        {"You can go straight ahead",
         "Choose the way to your left",
         "Or the small path to your right"}, //-20000
        {"You can choose to continue on this road ahead",
         "Take the road to your left",
         "Or the small path to your right"}, //500
        {"You can continue by the large road you're on",
         "Take the smaller path to your left",
         "Or take the road to your right"}, //2000
        {"You can follow this road further on",
         "Take the small path to your left",
         "Or the road to your right"}}; //10000
