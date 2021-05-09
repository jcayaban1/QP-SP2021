#include "Game.h"

// Private Functions
void Game::initWindow() {

    this->videoMode = sf::VideoMode(400, 400);
    this->window = new sf::RenderWindow(this->videoMode, "Physics Engine", sf::Style::Close | sf::Style::Titlebar);
    this->window->setKeyRepeatEnabled(false);

    this->window->setFramerateLimit(60);

}

void Game::initVariables() {

    this->endGame = false;

}

// Constructors
Game::Game() {

    this->initVariables();
    this->initWindow();

}

// Destructors
Game::~Game() {

    delete this->window;

}

// Functions
const bool Game::running() const {
    return this->window->isOpen();
}

void Game::render() {

    this->window->clear();

    // Render stuff
    this->player.render(this->window);

    this->window->display();

}

void Game::update() {

    this->pollEvents();

    this->player.update(this->window);

}

void Game::pollEvents() {
    while(this->window->pollEvent(ev)) {

        switch(this->ev.type) {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape) this->window->close();
                break;

        }

    }
}