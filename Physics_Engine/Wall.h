#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <stdlib.h>
#include <time.h>

class Wall {

    public:

    Wall();
    virtual ~Wall();

    void drawWalls();
    void drawPixel();

    void render(sf::RenderTarget* target);

    private:

    std::vector<std::vector<bool> > wallMatrix;
    sf::RectangleShape upperWall, lowerWall, leftWall, rightWall;

};