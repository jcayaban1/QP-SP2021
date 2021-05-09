#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Player {

    public:

        // Constructors and Destructors
        Player(float x = 0.f, float y = 0.f);
        virtual ~Player();

        void updateWindowBoundsCollision(const sf::RenderTarget* target);
        void updateInput();
        void movePlayer();
        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

    private:

        sf::RectangleShape shape;

        void initVariables();
        void initShape();

        float movementSpeed;

        float velx;
        float vely;
        float accx;
        float accy;

        bool canMoveLeft;
        bool canMoveRight;
        bool canMoveUp;
        bool canMoveDown;

};