#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Player {

    public:

        // Constructors and Destructors
        Player(float x = 0.f, float y = 0.f);
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