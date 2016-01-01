#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>
#include <utility>
#include "Person.h"
#include "Inventory.h"
#include "Item.h"
#include "NPC.h"

class Hero : public Person {
private:
    int max_start_power = 10;
    int money;
    std::vector<Item*> equipped; //head, neck, body, 2*hand
    int getAction();

public:
    Inventory* inventory;
    static std::vector<std::string> questions;
    static std::vector<std::pair<std::string, int>> answers;

    Hero();
    int getMoney();
    void addMoney(int money);
    int getStrength();
    int getCharisma();
    int getSpeed();
    std::vector<Item*> getEquipped();
    void setEquipped(Item* item);
    void unsetEquipped(std::string name);
    void printEquipped();
    bool fightWithNPC(NPC* being);
    bool talkWithNPC(NPC* being);
    void resetHero();
    ~Hero();
};
#endif
