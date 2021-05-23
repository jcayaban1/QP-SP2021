#include "Player.h"
#include "Game.h"
#include "maze_generator_test.h"

// Constructor
Player::Player() {

    int randxcoord = rand()%RESOLUTION_WIDTH;
    int randycoord = rand()%RESOLUTION_HEIGHT;
    float randxpos = randxcoord * WINDOW_WIDTH / RESOLUTION_WIDTH;
    float randypos = randycoord * WINDOW_HEIGHT / RESOLUTION_HEIGHT;
    this->shape.setPosition(sf::Vector2f(randxpos, randypos));

    this->initShape();
    this->initVariables();

}

// Destructor
Player::~Player() {

}

// Private
void Player::initVariables() {

    this->movementSpeed = 0.2f;

    this->velx = 0.f;
    this->vely = 0.f;

}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
}

// Public
void Player::update(const sf::RenderTarget* target) {

    this->updateInput();

    this->movePlayer();

}

void Player::updateInput() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->velx += -1.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->velx += 1.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->vely += -1.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->vely += 1.f;
    }

}

void Player::acceleratePlayer() {
    this->velx = this->accx * this->movementSpeed;
    this->vely = this->accy * this->movementSpeed;
}

void Player::movePlayer() {
    
    this->shape.move(this->velx * this->movementSpeed, 0.f);
    this->shape.move(0.f, this->vely * this->movementSpeed);
    
}

void Player::render(sf::RenderTarget* target) {

    target->draw(this->shape);

}

void Player::changePosition(float x, float y) {
    this->shape.setPosition(sf::Vector2f(x, y));
}

float Player::getPosx() {
    return this->shape.getPosition().x;
}

float Player::getPosy() {
    return this->shape.getPosition().y;
}

void Player::changeVelocity(float velxprime, float velyprime) {
    this->velx = velxprime;
    this->vely = velyprime;
}

float Player::getVelx() {
    return this->velx;
}

float Player::getVely() {
    return this->vely;
}

std::pair <int, int> Player::getCoords() {
    std::pair <int, int> coords;
    coords.first = (int)((this->getPosx() + PLAYER_WIDTH/2) * RESOLUTION_WIDTH / WINDOW_WIDTH);
    coords.second = (int)((this->getPosy() + PLAYER_HEIGHT/2) * RESOLUTION_HEIGHT / WINDOW_HEIGHT);
    return coords;
}