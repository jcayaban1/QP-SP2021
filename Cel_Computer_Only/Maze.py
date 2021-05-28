import random
import pygame

RESOLUTION_WIDTH = 10 # If changed, make same change in Game.py and Player.py
RESOLUTION_HEIGHT = 10 # If changed, make same change in Game.py and Player.py

WINDOW_WIDTH = 600
WINDOW_HEIGHT = 600

CW = WINDOW_WIDTH/RESOLUTION_WIDTH
CH = WINDOW_HEIGHT/RESOLUTION_HEIGHT

WW = CW/8 # Thickness of maze walls
WH = CH/8

class Maze:

    def __init__(self, num_players, window):

        self.window = window
        self.cell_list = []
        self.num_players = num_players

        for i in range(RESOLUTION_WIDTH * RESOLUTION_HEIGHT + (RESOLUTION_WIDTH + RESOLUTION_HEIGHT + 1)): # Extra term is so that list doesn't go out of range for collisions
            cell = Cell(i)
            self.cell_list.append(cell)

        self.generate()

        self.target_list = []
        for i in range(self.num_players):
            self.target_list.append((random.randrange(RESOLUTION_WIDTH), random.randrange(RESOLUTION_HEIGHT)))

        self.render(window)

    def generate(self): # Generate maze by implementing DFS alg using a stack

        w = RESOLUTION_WIDTH
        h = RESOLUTION_HEIGHT

        # Generate random start point
        startx = random.randrange(w)
        starty = random.randrange(h)

        self.cell_list[startx * w + starty].visited = True

        # Begin stack
        mazePath = [(startx, starty)]

        # print(mazePath[-1]) # for debugging

        i = 0
        while i < (w * h - 1):

            dir = random.randrange(4)
            occupied = 0
            neighborFound = False

            while occupied < 4: # Checks whether all four directions have been accounted for

                currx = mazePath[-1][0]
                curry = mazePath[-1][1]

                # Check a random direction
                if dir == 0:
                    if currx > 0 and not self.cell_list[(currx - 1) * w + curry].visited:
                        self.cell_list[(currx - 1) * w + curry].visited = True
                        self.cell_list[(currx - 1) * w + curry].isRightFree = True
                        mazePath.append((currx - 1, curry))
                        #print((currx - 1, curry), self.cell_list[(currx - 1) * w + curry].visited, sep=' ') # for debugging
                        neighborFound = True
                if dir == 1:
                    if currx < w - 1 and not self.cell_list[(currx + 1) * w + curry].visited:
                        self.cell_list[(currx + 1) * w + curry].visited = True
                        self.cell_list[currx * w + curry].isRightFree = True
                        mazePath.append((currx + 1, curry))
                        #print((currx + 1, curry), self.cell_list[(currx + 1) * w + curry].visited, sep=' ') # for debugging
                        neighborFound = True
                if dir == 2:
                    if curry > 0 and not self.cell_list[currx * w + curry - 1].visited:
                        self.cell_list[currx * w + curry - 1].visited = True
                        self.cell_list[currx * w + curry - 1].isDownFree = True
                        mazePath.append((currx, curry - 1))
                        #print((currx, curry - 1), self.cell_list[currx * w + curry - 1].visited, sep=' ') # for debugging
                        neighborFound = True
                if dir == 3:
                    if curry < h - 1 and not self.cell_list[currx * w + curry + 1].visited:
                        self.cell_list[currx * w + curry + 1].visited = True
                        self.cell_list[currx * w + curry].isDownFree = True
                        mazePath.append((currx, curry + 1))
                        #print((currx, curry + 1), self.cell_list[currx * w + curry + 1].visited, sep=' ') # for debugging
                        neighborFound = True

                if neighborFound: # If a neighboring cell is free, that cell would be added to the stack and the process will repeat
                    break
                occupied += 1
                dir = (dir + 1) % 4

            if occupied == 4: # If all neighbors are occupied, pop cells from the stack until a free cell is found
                mazePath.pop()
                continue
            else: # If neighboring cell is not free, continue looking in other directions
                i += 1

    def render(self, window):

        for i in range(self.num_players):
            pygame.draw.rect(window, (255, 0, 0), (self.target_list[i][0] * CW, self.target_list[i][1] * CH, CW, CH))

        for i in range(RESOLUTION_WIDTH * RESOLUTION_HEIGHT):
            if not self.cell_list[i].isRightFree: # Draws a wall if the right side is open
                pygame.draw.rect(window, (255, 255, 255), (int(i / RESOLUTION_WIDTH + 1) * CW - WW/2, int(i % RESOLUTION_HEIGHT) * CH, WW, CH))
            if not self.cell_list[i].isDownFree: # Draws a wall if the bottom is open
                pygame.draw.rect(window, (255, 255, 255), (int(i / RESOLUTION_WIDTH) * CW, int(i % RESOLUTION_HEIGHT + 1) * CH - WH/2, CW, WH))

class Cell:

    def __init__(self, cellnum):
        self.cellnum = cellnum # place in maze grid (e.g. for 4x4 maze, top left is 0, bottom left is 3, top right is 12, bottom right is 15)
        self.isRightFree = False
        self.isDownFree = False
        self.visited = False