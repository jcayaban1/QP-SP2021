#include "maze_generator_test.h"
#include "Game.h"

//Const and Dest

Maze::Maze() {

    this->cell = new Cell [RESOLUTION_WIDTH * RESOLUTION_HEIGHT]; // allocate memory for w*h cells
    // Matrix elements will be accessed in the form "cell[x * width + y]"

    for(int i = 0; i < RESOLUTION_WIDTH * RESOLUTION_HEIGHT; i++) { // init cell[] attributes to false
        this->cell[i].visited = false;
        this->cell[i].isRightFree = false;
        this->cell[i].isDownFree = false;

        // Set wall sizes and positions //FIXME: need to adjust a bit for corners
        float cw = (float)(WINDOW_WIDTH / RESOLUTION_WIDTH);
        float ch = (float)(WINDOW_HEIGHT / RESOLUTION_HEIGHT);

        this->cell[i].rightWall.setSize(sf::Vector2f(cw/15.f, ch)); //denom of cw/num determines thickness of walls
        this->cell[i].downWall.setSize(sf::Vector2f(cw, ch/15.f));

        this->cell[i].rightWall.setPosition(sf::Vector2f(cw * (i/RESOLUTION_WIDTH + 1) - (cw/40.f), ch * (i%RESOLUTION_HEIGHT)));
        this->cell[i].downWall.setPosition(sf::Vector2f(cw * (i/RESOLUTION_WIDTH), ch * (i%RESOLUTION_HEIGHT + 1) - (ch/40.f)));
    }

}

Maze::~Maze() {

}

void Maze::generate() {

    int w = RESOLUTION_WIDTH;
    int h = RESOLUTION_HEIGHT;

    srand(static_cast<unsigned>(time(0)));

    //std::vector<std::vector <bool> > visited(RESOLUTION_WIDTH, std::vector<bool>(RESOLUTION_HEIGHT, false)); // initialize WIDTHxHEIGHT matrix

    std::stack<std::pair<int, int> > mazePath;

    std::pair<int, int> start (rand() % w, rand() % h);

    this->cell[start.first * w + start.second].visited = true;
    mazePath.push(start);

    std::cout << start.first << ' ' << start.second << std::endl; // for debugging

    int i = 0;
    while(i < w * h - 1) { // i = dimx * dimy -> entire grid is filled; -1 because first space is already filled
        int dir = rand()%4;
        int occupied = 0;
        bool neighborFound = false;
        while(occupied < 4) {

            int currx = mazePath.top().first;
            int curry = mazePath.top().second;

            // Search for neighbor
            switch(dir) {
                case 0: if(currx > 0 && !this->cell[(currx - 1) * w + curry].visited) { // Check left
                        this->cell[(currx - 1) * w + curry].visited = true;
                        this->cell[(currx - 1) * w + curry].isRightFree = true;
                        mazePath.push(std::make_pair(currx - 1, curry));
                        std::cout << currx - 1 << ' ' << curry << std::endl; // for debugging
                        neighborFound = true;
                        break;
                    }
                case 1: if(currx < w - 1 && !this->cell[(currx + 1) * w + curry].visited) { // Check right
                        this->cell[(currx + 1) * w + curry].visited = true;
                        this->cell[currx * w + curry].isRightFree = true;
                        mazePath.push(std::make_pair(currx + 1, curry));
                        std::cout << currx + 1 << ' ' << curry << std::endl; // for debugging
                        neighborFound = true;
                        break;
                    }
                case 2: if(curry > 0 && !this->cell[currx * w + curry - 1].visited) { // Check up
                        this->cell[currx * w + curry - 1].visited = true;
                        this->cell[currx * w + curry - 1].isDownFree = true;
                        mazePath.push(std::make_pair(currx, curry - 1));
                        std::cout << currx << ' ' << curry - 1 << std::endl; // for debugging
                        neighborFound = true;
                        break;
                    }
                case 3: if(curry < h - 1 && !this->cell[currx * w + curry + 1].visited) { // Check down
                        this->cell[currx * w + curry + 1].visited = true;
                        this->cell[currx * w + curry].isDownFree = true;
                        mazePath.push(std::make_pair(currx, curry + 1));
                        std::cout << currx << ' ' << curry + 1 << std::endl; // for debugging
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

    for(int i = 0; i < RESOLUTION_WIDTH * RESOLUTION_HEIGHT; i++) {// for debugging
        std::cout << i/RESOLUTION_WIDTH << ' ' << i%RESOLUTION_HEIGHT << ": ";
        if(this->cell[i].isRightFree) std::cout << "R ";
        if(this->cell[i].isDownFree) std::cout << "D ";
        std::cout << std::endl;
    }
}

void Maze::render(sf::RenderTarget* target) {

    for(int i = 0; i < RESOLUTION_WIDTH * RESOLUTION_HEIGHT; i++) {
        if(!this->cell[i].isRightFree) target->draw(this->cell[i].rightWall);
        if(!this->cell[i].isDownFree) target->draw(this->cell[i].downWall);
    }

}