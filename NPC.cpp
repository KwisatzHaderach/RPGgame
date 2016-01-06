#include "NPC.h"

using namespace std;

string NPC::getRandomName() {
    int number = rand() % 5;
    switch(number)
    {
        case 0: return "Dog";
        case 1: return "Drunk";
        case 2: return "Troll";
        case 3: return "HugeCat";
        case 4: return "GiantWorm";
    }
    return "Johny";
}

NPC::NPC() {
    this->setName(this->getRandomName());
    this->hostility = rand() % GameVariables::gameDifficulty + 5;
    this->setCharisma(rand() % GameVariables::gameDifficulty);
    this->setSpeed(rand() % GameVariables::gameDifficulty + 2);
    this->setStrength(rand() % GameVariables::gameDifficulty + 5);
    this->specialItem = NULL;
    this->weakness = new Item();
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
        {{"Rassilon", {"100", "RingOfRassilon", "TheKeyToTime", "23", "8", "42"}},
         {"PetShopOwner", {"4", "DeadParrot", "Albatros", "8", "2", "4"}},
         {"KingArthur", {"8", "Excalibur", "", "9", "8", "14"}},
         {"Bond,JamesBond", {"14", "PDA", "SpyGlass", "15", "9", "11"}},
         {"RobinsonCrusoe", {"2", "SpyGlass", "DeadParrot", "2", "4", "6"}},
         {"R2D2", {"6", "MireChip", "BowlerHat", "12", "4", "6"}},
         {"Dalek", {"20", "TheKeyToTime", "Fez", "2", "5", "13"}},
         {"QueenElizabeth", {"10", "DiamondNecklace", "FangNecklace", "14", "3", "4"}},
         {"Eru", {"4", "EthernalFlame", "", "22", "16", "18"}},
         {"DoctorWatson", {"6", "BowlerHat", "SpyGlass", "8", "3", "4"}},
         {"MilosZeman", {"50", "SharkSkin", "Hoverboard", "1", "1", "1"}},
         {"Aramis", {"15", "MireHelmet", "DiamondNecklace", "8", "6", "5"}},
         {"LinusTorvalds", {"10", "RHCE", "4thScarf", "13", "6", "10"}},
         {"BillGates", {"15", "PDA", "RHCE", "9", "8", "9"}},
         {"Mofftiss", {"14", "Fez", "SonicScrewdriver", "15", "12", "8"}},
         {"Cleopatra", {"19", "DiamondNecklace", "Fez", "7", "11", "9"}}
        }; // name, {hostility, item, weakness, charisma, speed, strength}
