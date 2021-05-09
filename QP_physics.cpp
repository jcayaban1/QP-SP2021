#include "Game.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define PERSON_WIDTH 10.0
#define PERSON_HEIGHT 10.0

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