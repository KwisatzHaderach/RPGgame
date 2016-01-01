#include "GameEngine.h"

using namespace std;

void GameEngine::buildPlace(Place *place, int *difficulty, int *length) {
    srand(time(NULL));
    if (*length > GameVariables::gameDifficulty) {
        place->addWayForth(new FinishingPlace(
                place, this->npcNameStack[rand()%(npcNameStack.size()-1)+1]));
        return;
    }
    int max = rand() % 3 + 1;
    *difficulty += max - 1;
    *length += 1;
    for (unsigned int i = 0; i < max; ++i)
        if (rand() % 4 == 0 and *difficulty > 1) {
            place->addWayForth(new DeadEnd(place));
            *difficulty -= 1;
        }
        else {
            Place* new_place = new Place(place);
            place->addWayForth(new_place);
            this->buildPlace(new_place, difficulty, length);
        }
    place->setText();
}

void GameEngine::buildCity(City *city) {
    if (city->getStartingPlace()) return;
    srand(time(NULL));
    int *difficulty, *length;
    BeginningPlace *start = new BeginningPlace();
    city->setStartingPlace(start);
    Place *start_place1 = new Place(start), *start_place2 = new Place(start);
    start->addWayForth(start_place1);
    start->addWayForth(start_place2);
    *difficulty = 2;
    *length = 1;
    this->buildPlace(start_place1, difficulty, length);
    this->buildPlace(start_place2, difficulty, length);
}

void GameEngine::workWithEquip() {
    this->hero->printEquipped();
    char answer = 'a';
    while (answer != 'y' and answer != 'n') {
        cout << "Would like to unequip any item? (y/n): ";
        cin >> answer;
    }
    if (answer == 'y') {
        string item_name;
        cout << "Write the name of item you would like to uneqip: ";
        cin >> item_name;
        this->hero->unsetEquipped(item_name);
    }
}

void GameEngine::workWithInventory() {
    this->hero->inventory->printInventory();
    char answer = 'a';
    while (answer != 'y' and answer != 'n') {
        cout << "Would you like to equipp any item? (y/n): ";
        cin >> answer;
    }
    if (answer == 'y') {
        string item_name;
        cout << "Write the name of item you would like to eqipp: ";
        cin >> item_name;
        this->hero->setEquipped(this->hero->inventory->getItem(item_name));
    }
    answer = 'a';
    while (answer != 'y' and answer != 'n') {
        cout << "Would you like to remove any item? (y/n): ";
        cin >> answer;
    }
    if (answer == 'y') {
        string item_name;
        cout << "Write the name of item you would like to remove: ";
        cin >> item_name;
        this->hero->inventory->removeItem(item_name);
    }
}

bool GameEngine::walkThroughCity(Place *place) {
    bool solved = false;
    while (!solved) {
        if (place->getBeing() and
                place->getBeing()->getHostility() > this->hero->getCharisma() * 2) {
            cout << "Enemy on this place is too aggressive, "
                            "you are being attacked." << endl;
            if (this->hero->fightWithNPC(place->getBeing())) {
                place->removeBeing();
                if (place->getType() == "finish") return true;
            } else if (place->getType() == "finish") return false;
        }
        place->printTextWithAnswers();
        int answers_size = place->getAnswersSize();
        cout << answers_size << ") Look into your inventory." << endl;
        cout << answers_size + 1 << ") Look at your equipped items." << endl;
        int choice = 0;
        while (choice < 1 or choice > answers_size + 1) {
            cout << "What action would you like to perform? (1-" <<
            answers_size + 1 << "): ";
            cin >> choice;
        }
        if (choice == 1) break;
        else if (place->getBeing() and choice == 2) {
            if (this->hero->talkWithNPC(place->getBeing())) {
                place->removeBeing();
                if (place->getType() == "finish") return true;
            } else if (place->getType() == "finish") return false;
        }
        else if ((!place->getBeing() and place->getItem() and choice == 2) or
                 (place->getBeing() and place->getItem() and choice == 3)) {
            this->hero->inventory->addItem(place->getItem());
            place->removeItem();
        }
        else if (choice > answers_size - place->getWayForth().size() and
                 choice <= answers_size) {
            solved = this->walkThroughCity(place->getWayForth()
                            [choice - answers_size +
                            place->getWayForth().size() - 1]);
        }
        else if (choice == answers_size) {
            this->workWithInventory();
        }
        else if (choice == answers_size + 1) {
            this->workWithEquip();
        }
    }
    return solved;
}

GameEngine::GameEngine() {
    int difficulty = 0;
    while (difficulty < 1 or difficulty > 5) {
        cout << "What level of difficulty would you like to play on? (1-5): ";
        cin >> difficulty;
    }
    GameVariables::gameDifficulty = difficulty*10;
    this->hero = new Hero();
    for (unsigned int i = 0; i < difficulty*2; ++i)
        this->cities.push_back(new City(this->cityNameStack[i]));
    this->tardis = Capsule::getInstance();
    this->finale = Finale::getInstance();
    for(map<string,vector<string>>::iterator it = Item::namedItemStatsStack.begin();
            it != Item::namedItemStatsStack.end(); ++it) {
        this->npcNameStack.push_back(it->first);
    }
}

void GameEngine::gameIsOn() {
    int cities_unfinished = (int)this->cities.size();
    int num_cities = (int)this->cities.size();
    while (true) {
        cout << "You have " << cities_unfinished << " cities remaining to go through.";
        cout << endl << "Your options are:" << endl;
        cout << "0) Quit this game." << endl;
        for (unsigned int i = 0; i < num_cities; ++i)
            cout << i+1 << ") Visit city " << this->cities[i]->getName() << endl;
        cout << num_cities+1 << ") Go to your TARDIS and change year." << endl;
        cout << num_cities+2 << ") Look into your inventory." << endl;
        cout << num_cities+3 << ") Look at your equipped items." << endl;
        if (cities_unfinished <= 0)
            cout << num_cities+4 << ") Visit finale" << endl;
        int choice = -1;
        while (choice < 0 or (choice > num_cities+3 and cities_unfinished > 0)
                or (choice > num_cities+4 and cities_unfinished <= 0)) {
            cout << "Your choice is(0-";
            if (cities_unfinished > 0)
                cout << num_cities+3 << "): ";
            else cout << num_cities+4 << "): ";
            cin >> choice;
        }
        if (choice == 0) {
            cout << "Bye!" << endl;
            break;
        }
        else if (choice <= num_cities) {
            this->buildCity(this->cities[choice-1]);
            if (this->walkThroughCity(this->cities[choice-1]->getStartingPlace())) {
                if (!this->cities[choice-1]->getFinished())
                    cities_unfinished -= 1;
                this->cities[choice-1]->setFinished(true);
            }
        }
        else if (choice == num_cities+1) {
            int new_year;
            cout << "What year would you like to travel to? ";
            cin >> new_year;
            this->tardis->setYear(new_year);
        }
        else if (choice == num_cities+2) {
            this->workWithInventory();
        }
        else if (choice == num_cities+3) {
            this->workWithEquip();
        }
        else if (choice == num_cities+4) {
            if (this->walkThroughCity(this->finale->getStartingPlace())) {
                cout << "You have won this game!!!" << endl;
                break;
            }
        }
    }
}

GameEngine::~GameEngine() {
    delete this->hero;
    delete this->tardis;
    if (this->finale)
        delete finale;
    for (unsigned int i = 0; i < this->cities.size(); ++i)
        delete this->cities[i];
}
