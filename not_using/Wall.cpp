#include "Wall.h"
#include "Game.h"
#include "maze_generator_test.h" //FIXME: delete after finishing maze gen alg

// Constructor
Wall::Wall() {

    /*upperWall.setPosition(sf::Vector2f(20.f, 20.f));
    upperWall.setSize(sf::Vector2f(18.f * 20.f, 20.f));

    lowerWall.setPosition(sf::Vector2f(20.f, 360.f));
    lowerWall.setSize(sf::Vector2f(18.f * 20.f, 20.f));

    leftWall.setPosition(sf::Vector2f(20.f, 40.f));
    leftWall.setSize(sf::Vector2f(20.f, 16 * 20.f));

    rightWall.setPosition(sf::Vector2f(360.f, 40.f));
    rightWall.setSize(sf::Vector2f(20.f, 16 * 20.f));*/

    upperWall.setPosition(sf::Vector2f(60.f, 60.f));
    upperWall.setSize(sf::Vector2f(200.f, 100.f));

    this->coord_width = WINDOW_WIDTH / RESOLUTION_WIDTH;
    this->coord_height = WINDOW_HEIGHT / RESOLUTION_HEIGHT;

}

// Destructor
Wall::~Wall() {

}

void Wall::drawWalls() {

    srand(static_cast<unsigned>(time(0)));

    std::vector<std::vector <bool> > visited(RESOLUTION_WIDTH, std::vector<bool>(RESOLUTION_HEIGHT, false)); // initialize WIDTHxHEIGHT matrix

    std::stack<std::pair<int, int> > mazePath;

    std::pair<int, int> start (rand() % RESOLUTION_WIDTH, rand() % RESOLUTION_HEIGHT);

    visited[start.first][start.second] = true;
    mazePath.push(start);

    int i = 0;
    while(i < RESOLUTION_WIDTH * RESOLUTION_HEIGHT - 1) { // i = dimx * dimy -> entire grid is filled; -1 because first space is already filled
        int dir = rand()%4;
        int occupied = 0;
        bool neighborFound = false;
        while(occupied < 4) {

            // Search for neighbor
            switch(dir) {
                case 0: if(mazePath.top().first > 0 && !visited[mazePath.top().first - 1][mazePath.top().second]) { // Check left
                        visited[mazePath.top().first - 1][mazePath.top().second] = true;
                        std::pair<int, int> neighbor (mazePath.top().first - 1, mazePath.top().second);
                        mazePath.push(neighbor);
                        std::cout << "Neighbor pushed: " << neighbor.first << ' ' << neighbor.second << std::endl;
                        neighborFound = true;
                        break;
                    }
                case 1: if(mazePath.top().first < RESOLUTION_WIDTH - 1 && !visited[mazePath.top().first + 1][mazePath.top().second]) { // Check right
                        visited[mazePath.top().first + 1][mazePath.top().second] = true;
                        std::pair<int, int> neighbor (mazePath.top().first + 1, mazePath.top().second);
                        mazePath.push(neighbor);
                        std::cout << "Neighbor pushed: " << neighbor.first << ' ' << neighbor.second << std::endl;
                        neighborFound = true;
                        break;
                    }
                case 2: if(mazePath.top().second > 0 && !visited[mazePath.top().first][mazePath.top().second - 1]) { // Check up
                        visited[mazePath.top().first][mazePath.top().second - 1] = true;
                        std::pair<int, int> neighbor (mazePath.top().first, mazePath.top().second - 1);
                        mazePath.push(neighbor);
                        std::cout << "Neighbor pushed: " << neighbor.first << ' ' << neighbor.second << std::endl;
                        neighborFound = true;
                        break;
                    }
                case 3: if(mazePath.top().second < RESOLUTION_HEIGHT - 1 && !visited[mazePath.top().first][mazePath.top().second + 1]) { // Check down
                        visited[mazePath.top().first][mazePath.top().second + 1] = true;
                        std::pair<int, int> neighbor (mazePath.top().first, mazePath.top().second + 1);
                        mazePath.push(neighbor);
                        std::cout << "Neighbor pushed: " << neighbor.first << ' ' << neighbor.second << std::endl;
                        neighborFound = true;
                        break;
                }
                default:;
            }
            if(neighborFound) break;
            occupied++; // Increments if all cases are false
            dir = (dir + 1) % 4; // Change direction
        }

        if(occupied == 4) {
            // Pop top of stack and continue
            mazePath.pop();
            continue;
        }
        else {
            i++;
        }
    }
}

void Wall::render(sf::RenderTarget* target) {

    target->draw(upperWall);
    /*target->draw(lowerWall);
    target->draw(leftWall);
    target->draw(rightWall);*/

}

float Wall::getPosx() {
    return this->upperWall.getPosition().x;
}

float Wall::getPosy() {
    return this->upperWall.getPosition().y;
}

float Wall::getSizex() {
    return this->upperWall.getSize().x;
}

float Wall::getSizey() {
    return this->upperWall.getSize().y;
}

void Wall::changeColor() {
    this->upperWall.setFillColor(sf::Color::Green);
}

void Wall::revertColor() {
    this->upperWall.setFillColor(sf::Color::White);
}