#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <utility>

class Wall {

    public:

        Wall();
        virtual ~Wall();

        void drawWalls();

        void render(sf::RenderTarget* target);

        float getPosx();
        float getPosy();
        float getSizex();
        float getSizey();
        void changeColor();
        void revertColor();

    private:

        std::vector<std::vector<bool> > wallMatrix;
        sf::RectangleShape upperWall, lowerWall, leftWall, rightWall;

        float coord_width;
        float coord_height;

};