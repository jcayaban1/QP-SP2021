#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Wall.h"
#include "maze_generator_test.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define FRAMERATE 60

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
        void playerWindowCollision();
        void playerWallCollision();
        bool playerWallOverlap();

    private:

        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        bool endGame;

        sf::Event ev;

        void initVariables();
        void initWindow();

        Player player;
        Wall wall;
        Maze maze;
};