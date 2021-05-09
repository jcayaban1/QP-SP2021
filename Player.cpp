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

    this->movementSpeed = 5.f;

    this->velx = 0.f;
    this->vely = 0.f;

    this->canMoveLeft = true;
    this->canMoveRight = true;
    this->canMoveUp = true;
    this->canMoveDown = true;

}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setSize(sf::Vector2f(10.f, 10.f));
}

// Public
void Player::update(const sf::RenderTarget* target) {

    this->updateInput();
    this->movePlayer();
    this->updateWindowBoundsCollision(target);

}

void Player::updateInput() {

    if()

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(this->canMoveLeft) this->velx += -1.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if(this->canMoveRight) this->velx += 1.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if(this->canMoveUp) this->vely += -1.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if(this->canMoveDown) this->vely += 1.f;
    }

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target) {

    sf::FloatRect playerBounds = this->shape.getGlobalBounds();

    // Left
    if(playerBounds.left <= 0.f) {
        this->canMoveLeft = false;
        this->velx = 0.f;
    }
    else {
        this->canMoveLeft = true;
    }

    if(playerBounds.left + playerBounds.width >= target->getSize().x) {
        this->canMoveRight = false;
        this->velx = 0.f;
    }
    else {
        this->canMoveRight = true;
    }

    // Vertical
    if(playerBounds.top <= 0.f) {
        this->canMoveUp = false;
        this->vely = 0.f;
    }
    else {
        this->canMoveUp = true;
    }

    if(playerBounds.top + playerBounds.height >= target->getSize().y) {
        this->canMoveDown = false;
        this->vely = 0.f;
    }
    else {
        this->canMoveDown = true;
    }

}

void Player::movePlayer() {
    this->shape.move(this->velx * this->movementSpeed, 0.f);
    this->shape.move(0.f, this->vely * this->movementSpeed);
}

void Player::render(sf::RenderTarget* target) {

    target->draw(this->shape);

}