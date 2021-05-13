#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Wall.h"

class Game {
    public:

        // Constructors and Destructors
        Game();
        ~Game();

        // Accessors

        // Modifiers

        // Functions

        const bool running() const;

        void update();
        void render();
        void pollEvents();

        void handleOutOfBounds();

        void handleCollisions();
        void playerWallCollision();

    private:

        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        bool endGame;

        sf::Event ev;

        void initVariables();
        void initWindow();

        Player player;
        Wall wall;
};