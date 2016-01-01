#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

class Item {
private:
    std::string getRandomName();
    int getClosestYear(int year);
    int getSign(int number);
    std::string name;
    int strengthMod;
    int charismaMod;
    int speedMod;
    std::string special;
    std::string specialHidden;
    std::string type;

public:
    static std::map<std::string, std::vector<std::string>> namedItemStatsStack;
    static std::vector<std::vector<std::string>> yearItemNamesStack;

    Item();
    Item(int year);
    Item(std::string name);
    std::string getName();
    std::string getType();
    int getStrengthMod();
    int getCharismaMod();
    int getSpeedMod();
    std::string getSpecial();
    std::string getSpecialHidden();
    void printInfo();
};
#endif
