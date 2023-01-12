background_image = "ciel.jpg"

import pygame
from pygame.locals import *

pygame.init()
screen = pygame.display.set_mode((640, 455))

pygame.display.set_caption("Créer un jeu")
background = pygame.image.load(background_image).convert()


x, y = 0, 0                 #initalisation variable
move_x, move_y = 0, 0



run = True
while run:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

        if event.type == KEYDOWN:           #attente d'appui
            if event.key == K_LEFT or event.key == K_q:         #choix en fonction de l'appui
                move_x = -10
            elif event.key == K_RIGHT or event.key == K_d:
                move_x = +10
            elif event.key == K_UP or event.key == K_z:
                move_y = -10
            elif event.key == K_DOWN or event.key == K_s:
                move_y = +10
        elif event.type == KEYUP:            #attente relachement
            if event.key == K_LEFT or event.key == K_q:          #choix en fonction du relachement
                move_x = 0
            elif event.key == K_RIGHT or event.key == K_d:
                move_x = 0
            elif event.key == K_UP or event.key == K_z:
                move_y = 0
            elif event.key == K_DOWN or event.key == K_s:
                move_y = 0
        x += move_x
        y += move_y
        screen.fill((255, 255, 255))
        screen.blit(background, (x, y))
        pygame.display.update()

pygame.quit()
quit()