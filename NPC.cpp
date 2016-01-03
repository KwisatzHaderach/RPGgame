#include "NPC.h"

using namespace std;

string NPC::getRandomName() {
    srand(time(NULL));
    int number = rand() % 5;
    switch(number)
    {
        case 0: return "Dog";
        case 1: return "Drunk";
        case 2: return "Troll";
        case 3: return "Huge cat";
        case 4: return "Giant worm";
    }
    return "Johny";
}

NPC::NPC() {
    srand(time(NULL));
    this->setName(this->getRandomName());
    this->hostility = rand() % 15 + 5;
    this->setCharisma(rand() % 5);
    this->setSpeed(rand() % 10 + 10);
    this->setStrength(rand() % 20 + 10);
}

NPC::NPC(string name) {
    this->setName(name);
    map<string,vector<string>>::iterator it = this->npcStatsStack.begin();
    for(; it != this->npcStatsStack.end(); ++it)
        if (it->first == name) break;
    if (it == this->npcStatsStack.end()) return;
    this->hostility = stoi(it->second[0]);
    this->specialItem = new Item(it->second[1]);
    if (it->second[2] != "")
        this->weakness = new Item(it->second[2]);
    this->setCharisma(stoi(it->second[3]));
    this->setSpeed(stoi(it->second[4]));
    this->setStrength(stoi(it->second[5]));
}

int NPC::getHostility() {
    return this->hostility;
}

void NPC::modifyHostility(int hostility) {
    this->hostility += hostility;
}

Item* NPC::getSpecialItem() {
    return this->specialItem;
}

Item* NPC::getWeakness() {
    return this->weakness;
}

NPC::~NPC() {
    delete this->specialItem;
    delete this->weakness;
}

map<string, vector<string>> NPC::npcStatsStack =
        {{"Rassilon", {"100", "Ring of Rassilon", "The Key To Time",
                              "23", "8", "42"}},
         {"Pet Show owner", {"4", "Dead parrot", "Albatros", "8", "2", "4"}},
         {"King Arthur", {"8", "Excalibur", "", "9", "8", "14"}},
         {"Bond, James Bond", {"14", "PDA", "Spy glass", "15", "9", "11"}},
         {"Robinson Crusoe", {"2", "Spy glass", "Dead parrot", "2", "4", "6"}},
         {"R2D2", {"6", "Mire chip", "Bowler hat", "12", "4", "6"}},
         {"Dalek", {"20", "The Key To Time", "Fez", "2", "5", "13"}},
         {"Queen Elizabeth", {"10", "Diamond necklace", "Fang necklace", "14",
                                     "3", "4"}},
         {"Eru", {"4", "Ethernal flame", "", "22", "16", "18"}},
         {"Doctor Watson", {"6", "Bowler hat", "Spy glass", "8", "3", "4"}},
         {"Milos Zeman", {"50", "Shark skin", "Hoverboard", "1", "1", "1"}},
         {"Aramis", {"15", "Mire helmet", "Diamond necklace", "8", "6", "5"}},
         {"Linus Torvalds", {"10", "RHCE", "4th scarf", "13", "6", "10"}},
         {"Bill Gates", {"15", "PDA", "RHCE", "9", "8", "9"}},
         {"Mofftiss", {"14", "Fez", "Sonic screwdriver", "15", "12", "8"}},
         {"Cleopatra", {"19", "Diamond necklace", "Fez", "7", "11", "9"}}
        }; // name, {hostility, item, weakness, charisma, speed, strength}
