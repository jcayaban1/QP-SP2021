import serial
import pygame
import random

import Game

print("Welcome to CEL!")

num_players = 0

while(True): # Ask for number of players
    num_players = input("Please input the amount of players (1 - 4): ")
    if int(num_players) >= 1 and int(num_players) <= 4:
        break
    print("ERROR: Invalid number")

FPS = 60

# initialize Game object
game = Game.Game(int(num_players))

# initialize clock
clock = pygame.time.Clock()

# game loop
while game.running():

    clock.tick(FPS)

    game.update()
    game.render()