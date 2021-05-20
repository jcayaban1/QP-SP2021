#include "Game.h"

int main() {

    // Initialize Random Seed
    srand(static_cast<unsigned>(time(0)));

    // Initialize Game Object

    Game game;

    // Game loop
    while(game.running()) {

        game.update();
        game.render();

    }

    // End
    return 0;

}