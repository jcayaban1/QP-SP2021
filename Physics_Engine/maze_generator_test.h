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

#define RESOLUTION_WIDTH 15
#define RESOLUTION_HEIGHT 15

class Cell { // must go before Maze
    public:

    bool isRightFree; //isRightFree and isDownFree needed for drawing maze
    bool isDownFree;
    bool visited;

    sf::RectangleShape rightWall;
    sf::RectangleShape downWall;

    private:

};

class Maze {
    public:

        //Const and Dest
        Maze();
        ~Maze();

        void render(sf::RenderTarget* target);

        Cell* cell; // array of cells; allocation is in constructor

        void generate();


    private:
};