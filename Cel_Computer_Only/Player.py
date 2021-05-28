import random
import pygame

RESOLUTION_WIDTH = 10 # If changed, make same change in Game.py and Maze.py
RESOLUTION_HEIGHT = 10 # If changed, make same change in Game.py and Maze.py

WINDOW_WIDTH = 600
WINDOW_HEIGHT = 600

CW = WINDOW_WIDTH/RESOLUTION_WIDTH
CH = WINDOW_HEIGHT/RESOLUTION_HEIGHT

PW = CW/1.5 # Size of player should be slightly less than size of each cell (MUST BE SAME AS Game.py)
PH = CH/1.5

class Player:

    def __init__(self, window):
        randxcoord = random.randrange(RESOLUTION_WIDTH)
        randycoord = random.randrange(RESOLUTION_HEIGHT)

        self.xpos = randxcoord * CW
        self.ypos = randycoord * CH

        self.mvspeed = 0.2 # 60 * Pixels/sec

        self.xvel = 0
        self.yvel = 0

        self.xaccel = 0
        self.yaccel = 0

        self.render(window)

    def update(self):
        self.updateInput()
        self.acceleratePlayer()
        self.movePlayer()

    def render(self, window):
        pygame.draw.rect(window, (0, 255, 0), (self.xpos, self.ypos, PW, PH))

    def updateInput(self):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]: # Accesses dictionary and checks if true
            self.xvel += -1
        if keys[pygame.K_RIGHT]:
            self.xvel += 1
        if keys[pygame.K_UP]:
            self.yvel += -1
        if keys[pygame.K_DOWN]:
            self.yvel += 1
        if keys[pygame.K_SPACE]:
            self.xvel = 0
            self.yvel = 0

    def acceleratePlayer(self):
        self.xvel += self.xaccel
        self.yvel += self.yaccel

    def movePlayer(self):
        self.xpos += self.mvspeed * self.xvel
        self.ypos += self.mvspeed * self.yvel

    def getCoords(self):
        xcoord = int((self.xpos + PW/2) * 1/CW)
        ycoord = int((self.ypos + PH/2) * 1/CH)
        return (xcoord, ycoord)