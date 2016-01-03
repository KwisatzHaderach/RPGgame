#include "Item.h"

using namespace std;

string Item::getRandomName() {
    int number = rand() % 5;
    switch (number)
    {
        case 0: return "Rock";
        case 1: return "Pointy stick";
        case 2: return "Keyboard";
        case 3: return "Small statue";
        case 4: return "Umbrella";
    }
    return "Sonic trowel";
}

int Item::getClosestYear(int year) {
    if (year < -500) return 0; // -20000
    else if (year < 1500) return 1; // 500
    else if (year < 2500) return 2; // 2000
    else return 3; // 10000
}

int Item::getSign(int number) {
    if (number < 0) return -1;
    else return 1;
}

Item::Item() {
    this->name = this->getRandomName();
    this->strengthMod = rand() % 3 + 1;
    this->charismaMod = 0;
    this->speedMod = rand() % 3;
    this->special = "";
    this->specialHidden = "";
    this->type = "hand";
}

Item::Item(string name) {
    this->name = name;
    this->strengthMod = stoi(namedItemStatsStack[name][0]);
    this->charismaMod = stoi(namedItemStatsStack[name][1]);
    this->speedMod = stoi(namedItemStatsStack[name][2]);
    this->special = namedItemStatsStack[name][3];
    this->specialHidden = namedItemStatsStack[name][4];
    this->type = namedItemStatsStack[name][5];
}

Item::Item(int year) {
    int closestYear = this->getClosestYear(year);
    this->name = this->yearItemNamesStack[closestYear][rand() %
            this->yearItemNamesStack[closestYear].size()];
    this->strengthMod = rand() % 3 - (year % 5 * this->getSign(year));
    this->charismaMod = rand() % 3 + (year % 5 * this->getSign(year));
    this->speedMod = year % 5;
    this->special = "";
    this->specialHidden = to_string(year);
    this->type = "hand";
}

string Item::getName() {
    return this->name;
}

string Item::getType() {
    return this->type;
}

int Item::getStrengthMod() {
    return this->strengthMod;
}

int Item::getCharismaMod() {
    return this->charismaMod;
}

int Item::getSpeedMod() {
    return this->speedMod;
}

string Item::getSpecial() {
    return this->special;
}

string Item::getSpecialHidden() {
    return this->specialHidden;
}

void Item::printInfo() {
    cout << this->getName() << ": " << this->getStrengthMod() << "/";
    cout << this->getCharismaMod() << "/" << this->getSpeedMod() << "/";
    cout << this->getSpecial() << "/" << this->getType() << endl;
}

map<string, vector<string>> Item::namedItemStatsStack =
        {{"RingOfRassilon", {"20", "0", "5", "immortality", "stone", "hand"}},
         {"TheKeyToTime", {"0", "10", "20", "repair capsule", "win the game",
                                     "neck"}},
         {"SonicScrewdriver", {"2", "22", "11", "sonic", "", "hand"}},
         {"SonicGlasses", {"2", "22", "11", "sonic", "", "head"}},
         {"MireHelmet", {"12", "3", "0", "vision", "", "head"}},
         {"MireChip", {"8", "16", "4", "immortality", "boredom", "neck"}},
         {"DeadParrot", {"5", "9", "6", "nailed", "dead", "hand"}},
         {"Albatros", {"6", "7", "3", "Albatros!", "", "head"}},
         {"RHCE", {"1", "13", "2", "Certified!", "", "body"}},
         {"4thScarf", {"5", "9", "4", "7 meters", "Time Lords be tripping",
                               "body"}},
         {"Fez", {"1", "7", "2", "walk past a fez", "never", "head"}},
         {"Hoverboard", {"2", "2", "12", "flying", "", "body"}},
         {"BowlerHat", {"0", "6", "1", "protection", "", "head"}},
         {"SpyGlass", {"3", "4", "3", "vision", "", "hand"}},
         {"Excalibur", {"15", "5", "5", "rule england", "", "hand"}},
         {"FangNecklace", {"4", "7", "2", "magic", "", "neck"}},
         {"PDA", {"2", "8", "1", "mans best friend", "", "hand"}},
         {"EthernalFlame", {"6", "12", "2", "fire", "burn with me", "head"}},
         {"SharkSkin", {"7", "6", "1", "fireproof", "", "body"}},
         {"DiamondNecklace", {"4", "9", "4", "shiny", "metal ass", "neck"}}
        }; // name, {strength, charisma, speed, special, special hidden, type}

vector<vector<string>> Item::yearItemNamesStack =
        {{"StoneKnife", "BigWood", "Lizard", "FlintStone", "MammothBone"},
         {"Scepter", "RustySword", "SmallKnife", "Flask", "Ring",
                 "LeatherBracelet"},
         {"DigitalWatch", "Key", "DigitalBracelet", "Gun", "Tamagochi",
                 "Compass", "Pen", "LeatherSuitcase", "Torch", "BottleOfGin"},
         {"MasterControl", "LaserGun", "Communicator", "PersonalComputer",
                 "HolographicRing", "AlienDevice", "HeadInAJar"}};
