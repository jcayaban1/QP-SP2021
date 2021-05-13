#include "Player.h"

// Constructor
Player::Player(float x, float y) {

    this->shape.setPosition(sf::Vector2f(195.f, 195.f));

    this->initShape();
    this->initVariables();

}

// Destructor
Player::~Player() {

}

//Private
void Player::initVariables() {

    this->movementSpeed = 0.5f;

    this->velx = 0.f;
    this->vely = 0.f;

}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setSize(sf::Vector2f(20.f, 20.f));
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