import serial
import pygame
import random

import Player
import Maze

WINDOW_WIDTH = 600
WINDOW_HEIGHT = 600

RESOLUTION_WIDTH = 10 # If changed, make same change in Player.py and Maze.py
RESOLUTION_HEIGHT = 10 # If changed, make same change in Player.py and Maze.py

CW = WINDOW_WIDTH/RESOLUTION_WIDTH
CH = WINDOW_HEIGHT/RESOLUTION_HEIGHT

PW = CW/1.5
PH = CH/1.5

random.seed()

bg_color = (0, 0, 0)

class Game:

    def __init__(self, num_players):

        self.ser = serial.Serial("/dev/cu.usbmodem14101") # Connect to serial port

        pygame.init()
        pygame.font.init()

        # initialize screen
        self.screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        pygame.display.set_caption('Cel')
        self.screen.fill(bg_color)

        self.num_players = num_players

        self.players = []
        for i in range(num_players): # changes depending on how many players you want
            self.players.append(Player.Player(self.screen))
        self.maze = Maze.Maze(num_players, self.screen)

        self.game_over = False

        pygame.display.update()

    def running(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
        keys = pygame.key.get_pressed()
        if keys[pygame.K_ESCAPE]:
            return False
        return True

    def update(self):
        line = self.ser.readline() # Always receive serial input first!
        #print(line.decode("utf"), end = '') # For debugging purposes

        ##### Put line parsing code here #####

        for player in self.players:
            player.xaccel = 0 # FIXME: REPLACE 0's WITH ACCELEROMETER INPUT
            player.yaccel = 0
            player.update()
        #print(player.getCoords()) # for debugging

        for player in self.players:
            self.handleOutOfBounds(player)
            self.handleCollisions(player)

        self.playerPlayerCollisions()

        if self.check_win():
            self.game_over = True


    def render(self):
        if self.game_over:
            self.screen.fill(bg_color)
            game_over_font = pygame.font.Font("joystix monospace.ttf", 70)
            game_over_label = game_over_font.render("You won!", 1, (255, 255, 255))
            self.screen.blit(game_over_label, (WINDOW_WIDTH/2 - game_over_label.get_width()/2, WINDOW_HEIGHT/2 - game_over_label.get_height()/2))
            pygame.display.update()

        else:
            self.screen.fill(bg_color)
            self.maze.render(self.screen)
            for player in self.players:
                player.render(self.screen)
            pygame.display.update()

    def check_win(self):
        num_players_on_target = 0
        for player in self.players:
            if self.player_on_target(player):
                num_players_on_target += 1
        if num_players_on_target == self.num_players:
            #print(True) # for debugging
            return True
        else:
            #print(False) # for debugging
            return False

    def player_on_target(self, player):
        for i in range(self.num_players):
            if player.getCoords()[0] == self.maze.target_list[i][0] and player.getCoords()[1] == self.maze.target_list[i][1]:
                return True
        return False

    def handleOutOfBounds(self, player):
        if player.xpos <= 0:
            player.xpos = 0
        if player.xpos + PW >= WINDOW_WIDTH:
            player.xpos = WINDOW_WIDTH - PW
        if player.ypos <= 0:
            player.ypos = 0
        if player.ypos + PH >= WINDOW_HEIGHT:
            player.ypos = WINDOW_HEIGHT - PH

    def handleCollisions(self, player):
        self.playerWindowCollision(player)
        self.playerMazeCollision(player)

    def playerWindowCollision(self, player):
        if player.xpos <= 0:
            player.xvel = 0
            
        if player.xpos + PW >= WINDOW_WIDTH:
            player.xvel = 0
            
        if player.ypos <= 0:
            player.yvel = 0
            
        if player.ypos + PH >= WINDOW_HEIGHT:
            player.yvel = 0
            

    def playerMazeCollision(self, player):
        player_Cell = player.getCoords()[0] * RESOLUTION_WIDTH + player.getCoords()[1]
        left_wall = not self.maze.cell_list[player_Cell - RESOLUTION_WIDTH].isRightFree
        right_wall = not self.maze.cell_list[player_Cell].isRightFree
        up_wall = not self.maze.cell_list[player_Cell - 1].isDownFree
        down_wall = not self.maze.cell_list[player_Cell].isDownFree

        # dir1,dir2_wall means "in the dir1 direction, there is a wall on the dir2 side"
        # eg: lu_wall means "on the left cell, there is an upper wall"
        lu_wall = not self.maze.cell_list[player_Cell - RESOLUTION_WIDTH - 1].isDownFree
        ld_wall = not self.maze.cell_list[player_Cell - RESOLUTION_WIDTH].isDownFree

        ru_wall = not self.maze.cell_list[player_Cell + RESOLUTION_WIDTH - 1].isDownFree
        rd_wall = not self.maze.cell_list[player_Cell + RESOLUTION_WIDTH].isDownFree

        ul_wall = not self.maze.cell_list[player_Cell - 1 - RESOLUTION_WIDTH].isRightFree
        ur_wall = not self.maze.cell_list[player_Cell + 1].isRightFree

        dl_wall = not self.maze.cell_list[player_Cell + 1 - RESOLUTION_WIDTH].isRightFree
        dr_wall = not self.maze.cell_list[player_Cell + 1].isRightFree



        if left_wall:
            if player.xpos <= player.getCoords()[0] * CW:
                player.xvel = 0
                player.xpos += 1
        else: # Handles corners
            if lu_wall:
                if player.xpos <= player.getCoords()[0] * CW:
                    if player.ypos <= player.getCoords()[1] * CH:
                        if player.getCoords()[0] * CW - player.xpos > player.getCoords()[1] * CH - player.ypos:
                            player.yvel = 0
                            player.ypos += 1
            if ld_wall:
                if player.xpos <= player.getCoords()[0] * CW:
                    if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                        if player.getCoords()[0] * CW - player.xpos > player.ypos + PH - (player.getCoords()[1] + 1) * CH:
                            player.yvel = 0
                            player.ypos -= 1
            if ul_wall:
                if player.xpos <= player.getCoords()[0] * CW:
                    if player.ypos <= player.getCoords()[1] * CH:
                        if player.getCoords()[0] * CW - player.xpos > player.getCoords()[1] * CH - player.ypos:
                            player.yvel = 0
                            player.ypos += 1
            if dl_wall:
                if player.xpos <= player.getCoords()[0] * CW:
                    if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                        if player.getCoords()[0] * CW - player.xpos > player.ypos + PH - (player.getCoords()[1] + 1) * CH:
                            player.yvel = 0
                            player.ypos -= 1
        
        if right_wall:
            if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                player.xvel = 0
                player.xpos -= 1
        else:
            if ru_wall:
                if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                    if player.ypos <= player.getCoords()[1] * CH:
                        if player.xpos + PW - (player.getCoords()[0] + 1) * CW > player.getCoords()[1] * CH - player.ypos:
                            player.yvel = 0
                            player.ypos += 1
            if rd_wall:
                if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                    if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                        if player.xpos + PW - (player.getCoords()[0] + 1) * CW > player.ypos + PH - (player.getCoords()[1] + 1) * CH:
                            player.yvel = 0
                            player.ypos -= 1

            if ur_wall:
                if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                    if player.ypos <= player.getCoords()[1] * CH:
                        if player.xpos + PW - (player.getCoords()[0] + 1) * CW > player.getCoords()[1] * CH - player.ypos:
                            player.yvel = 0
                            player.ypos += 1
            if dr_wall:
                if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                    if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                        if player.xpos + PW - (player.getCoords()[0] + 1) * CW > player.ypos + PH - (player.getCoords()[1] + 1) * CH:
                            player.yvel = 0
                            player.ypos -= 1

        if up_wall:
            if player.ypos <= player.getCoords()[1] * CH:
                player.yvel = 0
                player.ypos += 1
        else:
            if ul_wall:
                if player.ypos <= player.getCoords()[1] * CH:
                    if player.xpos <= player.getCoords()[0] * CW:
                        player.xvel = 0
                        player.xpos += 1
            if ur_wall:
                if player.ypos <= player.getCoords()[1] * CH:
                    if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                        player.xvel = 0
                        player.xpos -= 1
            if lu_wall:
                if player.ypos <= player.getCoords()[1] * CH:
                    if player.xpos <= player.getCoords()[0] * CW:
                        player.xvel = 0
                        player.xpos += 1
            if ru_wall:
                if player.ypos <= player.getCoords()[1] * CH:
                    if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                        player.xvel = 0
                        player.xpos -= 1

        if down_wall:
            if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                player.yvel = 0
                player.ypos -= 1
        else:
            if dl_wall:
                if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                    if player.xpos <= player.getCoords()[0] * CW:
                        player.xvel = 0
                        player.xpos += 1
            if dr_wall:
                if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                    if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                        player.xvel = 0
                        player.xpos -= 1
            if ld_wall:
                if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                    if player.xpos <= player.getCoords()[0] * CW:
                        player.xvel = 0
                        player.xpos += 1
            if rd_wall:
                if player.ypos + PH >= (player.getCoords()[1] + 1) * CH:
                    if player.xpos + PW >= (player.getCoords()[0] + 1) * CW:
                        player.xvel = 0
                        player.xpos -= 1

    def playerPlayerCollisions(self):
        for player in self.players:
            others = [x for x in self.players if x is not player]
            for other in others:
                if player.xpos < other.xpos + PW and player.xpos + PW > other.xpos: # Check overlap in x direction
                    if player.ypos < other.ypos + PH and player.ypos + PH > other.ypos: # Check overlap in y direction
                        
                        left = True
                        above = True

                        if player.xpos + PW/2 < other.xpos + PW/2: # if player is to the left of other
                            xoverlap = player.xpos + PW - other.xpos
                        else:
                            xoverlap = other.xpos + PW - player.xpos
                            left = False
                        if player.ypos + PH/2 < other.ypos + PH/2: # if player is above other
                            yoverlap = player.ypos + PH - other.ypos
                        else:
                            yoverlap = other.ypos + PH - player.ypos
                            above = False

                        if xoverlap < yoverlap: # Accounts for collision
                            if left: # if player left of other
                                if player.xvel == 0: # equivalent to checking player maze collision
                                    other.xvel = 0
                                    other.xpos = player.xpos + PW
                                else:
                                    player.xpos = other.xpos - PW
                            else: # if player right of other
                                if other.xvel == 0:
                                    player.xvel = 0
                                    player.xpos = other.xpos + PW
                                else:
                                    other.xpos = player.xpos - PW
                        else:
                            if above: # if player above other
                                if player.yvel == 0:
                                    other.yvel = 0
                                    other.ypos = player.ypos + PH
                                else:
                                    player.ypos = other.ypos - PH
                            else: # if player below other
                                if other.yvel == 0:
                                    player.yvel = 0
                                    player.ypos = other.ypos + PH
                                else:
                                    other.ypos = player.ypos - PH