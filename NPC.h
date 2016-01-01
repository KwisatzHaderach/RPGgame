#ifndef NPC_H
#define NPC_H

#include <string>
#include <time.h>
#include <map>
#include "Person.h"
#include "Item.h"

class NPC : public Person {
private:
    int hostility;
    Item* specialItem;
    Item* weakness;
    std::string getRandomName();

public:
    static std::map<std::string, std::vector<std::string>> npcStatsStack;

    NPC();
    NPC(std::string name);
    int getHostility();
    void modifyHostility(int hostility);
    Item* getSpecialItem();
    Item* getWeakness();
    ~NPC();
};
#endif
