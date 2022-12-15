background_image = "ciel.jpg"

import pygame    #importation de la bibliothèque

pygame.init()    # Initialisation des sous module de la bibliothèque

screen = pygame.display.set_mode((640, 455)) #definition de la taille de la fen^tre

run = True

while run:
        for event in pygame.event.get(): #syntaxe pour à vider la file d’attente des événement.
            if event.type == pygame.QUIT: #événement sortie du programme.
                run = False

        pygame.display.update() #mises à jour du jeu à l’écran

pygame.quit()
quit()