#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <utility>

#define PLAYER_WIDTH 20.f //FIXME: Need to be able to scale player size with maze cell size. Note that Game.cpp contains these defines.
#define PLAYER_HEIGHT 20.f

class Player {

    public:

        // Constructors and Destructors
        Player();
        virtual ~Player();

        void updateInput();
        void movePlayer();
        void acceleratePlayer();
        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

        void changePosition(float x, float y);
        float getPosx();
        float getPosy();
        void changeVelocity(float velxprime, float velyprime);
        float getVelx();
        float getVely();

        std::pair <int, int> getCoords();

    private:

        sf::RectangleShape shape;

        void initVariables();
        void initShape();

        float movementSpeed;

        float velx;
        float vely;
        float accx;
        float accy;

};