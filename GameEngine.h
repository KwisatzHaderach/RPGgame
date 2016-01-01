#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include "Hero.h"
#include "City.h"
#include "Capsule.h"
#include "Finale.h"
#include "Place.h"
#include "variables.h"
#include "BeginningPlace.h"
#include "DeadEnd.h"
#include "FinishingPlace.h"

class GameEngine {
private:
    Hero* hero;
    std::vector<City*> cities;
    Capsule* tardis;
    Finale* finale;
    std::vector<std::string> cityNameStack
            {"Brno", "Prague", "London", "Paris", "Alexandria", "Pompeii",
             "San Helios", "Christmas", "Arcadia", "Darillium"};
    std::vector<std::string> npcNameStack;
    void buildCity(City* city);
    void buildPlace(Place* place, int *difficulty, int *length);
    void workWithEquip();
    void workWithInventory();
    bool walkThroughCity(Place* place);

public:
    GameEngine();
    void gameIsOn();
    ~GameEngine();
};
#endif
