#include "GameEngine.h"

int main() {
    GameEngine* game = new GameEngine;
    game->gameIsOn();
    delete game;

    return 0;
}
