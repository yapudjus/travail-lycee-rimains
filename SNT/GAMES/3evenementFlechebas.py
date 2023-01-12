background_image = "ciel.jpg"

import pygame    #importation de la bibliothèque
import time


pygame.init()    # Initialisation des sous module de la bibliothèque

screen = pygame.display.set_mode((640, 455)) #definition de la taille de la fen^tre

pygame.display.set_caption("Créer un jeu avec PyGame") #ajouter un titre

background = pygame.image.load(background_image).convert() #télécharge l’image d’arrière planconvertit l’image au même format que notre affichage.




run = True
while run:
        for event in pygame.event.get(): #boucle d'attente pour sortir prog
            if event.type == pygame.QUIT  :
                run = False
            elif event.type == pygame.KEYDOWN  :
                 run = False

        print(event)
        pygame.draw.circle(background, (250, 0, 250), (140, 60), 30) #dessiner un petit cercle
        screen.blit(background, (0, 0))
        pygame.display.update()




        time.sleep(2)
        pygame.draw.circle(background, (0, 250, 0), (140, 60), 30)
        screen.blit(background, (0, 0))
        pygame.display.update()
        time.sleep(2)

pygame.quit()