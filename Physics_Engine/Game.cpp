#include "Game.h"

// Private Functions
void Game::initWindow() {

    this->videoMode = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->window = new sf::RenderWindow(this->videoMode, "Cel", sf::Style::Close | sf::Style::Titlebar);
    this->window->setKeyRepeatEnabled(false);

    this->window->setFramerateLimit(FRAMERATE);

}

void Game::initVariables() {

    this->endGame = false;
    //this->wall.drawWalls();
    this->maze.generate();

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

    this->maze.render(this->window);


    
    this->player.render(this->window);

    /*/////////////////////////////////////// FIXME: Restore when finished with maze generator
    this->wall.render(this->window);
    *////////////////////////////////////////

    
    this->window->display();
    

}

void Game::update() {

    this->pollEvents();




    this->player.update(this->window);

    this->handleOutOfBounds();

    this->handleCollisions();





    // Check to see if getting correct coordinates
    // std::cout << this->player.getCoords().first << ' ' << this->player.getCoords().second << std::endl;

}

void Game::pollEvents() {
    while(this->window->pollEvent(ev)) {

        switch(this->ev.type) {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape) this->window->close();
                else if(this->ev.key.code == sf::Keyboard::Space) player.changeVelocity(0.f, 0.f);
                break;

            default:;

        }

    }
}

void Game::handleOutOfBounds() {
    if(player.getPosx() <= 0.f) player.changePosition(0.f, player.getPosy());
    if(player.getPosx() + PLAYER_WIDTH >= WINDOW_WIDTH) player.changePosition(WINDOW_WIDTH - PLAYER_WIDTH, player.getPosy());
    if(player.getPosy() <= 0.f) player.changePosition(player.getPosx(), 0.f);
    if(player.getPosy() + PLAYER_HEIGHT >= WINDOW_HEIGHT) player.changePosition(player.getPosx(), WINDOW_HEIGHT - PLAYER_HEIGHT);
}

void Game::handleCollisions() {
    playerWindowCollision();
    //playerWallCollision(); //FIXME: Only works for single rectangular wall. Need to update for maze walls
    playerMazeCollision();
}

void Game::playerWindowCollision() {
    // Horizontal
    if(player.getPosx() <= 0.f) {
        player.changeVelocity(0.f, player.getVely());
    }

    if(player.getPosx() + PLAYER_WIDTH >= WINDOW_WIDTH) {
        player.changeVelocity(0.f, player.getVely());
    }

    // Vertical
    if(player.getPosy() <= 0.f) {
        player.changeVelocity(player.getVelx(), 0.f);
    }

    if(player.getPosy() + PLAYER_HEIGHT >= WINDOW_HEIGHT) {
        player.changeVelocity(player.getVelx(), 0.f);
    }
}

/*void Game::playerWallCollision() { // NOT IN USE
    if(Game::playerWallOverlap()) {
        wall.changeColor();

        float wallmidx = (wall.getSizex()/2.f) + wall.getPosx();
        float wallmidy = (wall.getSizey()/2.f) + wall.getPosy();
        float playermidx = (PLAYER_WIDTH/2.f) + player.getPosx();
        float playermidy = (PLAYER_HEIGHT/2.f) + player.getPosy();

        float overlapx;
        float overlapy;

        if(wallmidx > playermidx) { // Player left of box
            overlapx = (player.getPosx() + PLAYER_WIDTH) - wall.getPosx();
        }
        else { // Player right of box
            overlapx = (wall.getPosx() + wall.getSizex()) - player.getPosx();
        }

        if(wallmidy > playermidy) { // Player above box
            overlapy = (player.getPosy() + PLAYER_HEIGHT) - wall.getPosy();
        }
        else { // Player below box
            overlapy = (wall.getPosy() + wall.getSizey()) - player.getPosy();
        }

        if(overlapx > overlapy) player.changeVelocity(player.getVelx(), -player.getVely());
        else player.changeVelocity(-player.getVelx(), player.getVely());
    }
    else wall.revertColor();
}*/

/*bool Game::playerWallOverlap() { // NOT IN USE
    if((player.getPosx() < (wall.getPosx() + wall.getSizex())) && ((player.getPosx() + PLAYER_WIDTH) > wall.getPosx())) {
        if((player.getPosy() < (wall.getPosy() + wall.getSizey())) && ((player.getPosy() + PLAYER_HEIGHT) > wall.getPosy())) return true;
    }
    return false;
}*/

void Game::playerMazeCollision() {
    int player_Cell = this->player.getCoords().first * RESOLUTION_WIDTH + this->player.getCoords().second;
    bool left_wall = !this->maze.cell[player_Cell - RESOLUTION_WIDTH].isRightFree;
    bool right_wall = !this->maze.cell[player_Cell].isRightFree;
    bool up_wall = !this->maze.cell[player_Cell - 1].isDownFree;
    bool down_wall = !this->maze.cell[player_Cell].isDownFree;

    float cw = WINDOW_WIDTH/RESOLUTION_WIDTH; // Cell width
    float ch = WINDOW_HEIGHT/RESOLUTION_HEIGHT; // Cell height

    // Check to see if getting correct coordinates
    std::cout << left_wall << ' ' << player_Cell << std::endl;

    if(left_wall) {
        if(player.getPosx() <= player.getCoords().first * cw + cw/30.f) {
            player.changeVelocity(0.f, player.getVely());

            if(!(player.getCoords().first * cw - player.getPosx() > PLAYER_WIDTH/2)) { // handles phasing through walls

                player.changePosition(player.getCoords().first * cw + cw/30.f, player.getPosy()); // stop player from moving
            }
        }
    }
    if(right_wall) {
        if(player.getPosx() + PLAYER_WIDTH >= (player.getCoords().first + 1) * cw - cw/30.f) {
            player.changeVelocity(0.f, player.getVely());

            if(!(player.getPosx() - ((player.getCoords().first + 1) * cw - PLAYER_WIDTH) > PLAYER_WIDTH/2)) {

                player.changePosition((player.getCoords().first + 1) * cw  - cw/30.f - PLAYER_WIDTH, player.getPosy());
            }
        }
    }
    if(up_wall) {
        if(player.getPosy() <= player.getCoords().second * ch + ch/30.f) {
            player.changeVelocity(player.getVelx(), 0.f);

            if(!(player.getCoords().second * ch - player.getPosy() > PLAYER_HEIGHT/2)) {

                player.changePosition(player.getPosx(), player.getCoords().second * ch + cw/30.f);
            }
        }
    }
    if(down_wall) {
        if(player.getPosy() + PLAYER_HEIGHT >= (player.getCoords().second + 1) * cw - ch/30.f) {
            player.changeVelocity(player.getVelx(), 0.f);

            if(!(player.getPosy() - ((player.getCoords().second + 1) * cw - PLAYER_HEIGHT) > PLAYER_HEIGHT/2)) {

                player.changePosition(player.getPosx(), (player.getCoords().second + 1) * cw - ch/30.f - PLAYER_HEIGHT);
            }
        }
    }
    
}