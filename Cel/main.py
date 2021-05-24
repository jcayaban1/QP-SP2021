import serial
import pygame
import random

import Game

FPS = 60

# initialize Game object
game = Game.Game()

clock = pygame.time.Clock()

# game loop
while game.running():

    clock.tick(FPS)

    game.update()
    game.render()