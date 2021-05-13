#include "Wall.h"

// Constructor
Wall::Wall() {

    upperWall.setPosition(sf::Vector2f(20.f, 20.f));
    upperWall.setSize(sf::Vector2f(18.f * 20.f, 20.f));

    lowerWall.setPosition(sf::Vector2f(20.f, 360.f));
    lowerWall.setSize(sf::Vector2f(18.f * 20.f, 20.f));

    leftWall.setPosition(sf::Vector2f(20.f, 40.f));
    leftWall.setSize(sf::Vector2f(20.f, 16 * 20.f));

    rightWall.setPosition(sf::Vector2f(360.f, 40.f));
    rightWall.setSize(sf::Vector2f(20.f, 16 * 20.f));

}

// Destructor
Wall::~Wall() {

}

void Wall::drawWalls() {

    /*srand(static_cast<unsigned>(time(0))); //FIXME: try to make random maze later

    for (int i = 1; i < 18 - 1; i++) { // Only randomizes interior, since exterior are all walls
        for (int j = 1; j < 18 - 1; j++) {
            this->wallMatrix[i].push_back(rand()%2);
        }
    }*/

}

void Wall::drawPixel() {

}

void Wall::render(sf::RenderTarget* target) {

    target->draw(upperWall);
    target->draw(lowerWall);
    target->draw(leftWall);
    target->draw(rightWall);

}