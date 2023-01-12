background_image = "ciel.jpg"

import random
import pygame    #importation de la bibliothèque

pygame.init()    # Initialisation des sous modules de la bibliothèque

screen = pygame.display.set_mode((640, 455)) #definition de la taille de la fenêtre

pygame.display.set_caption("i killed a cat yesterday") #ajouter un titre

background = pygame.image.load(background_image).convert() #télécharge l’image d’arrière planconvertit l’image au même format que notre affichage.




run = True
clickpos = (0, 0)
while run:
	for event in pygame.event.get():
		if event.type == pygame.MOUSEBUTTONDOWN:
			clickpos = pygame.mouse.get_pos()

		if event.type == pygame.QUIT:
			run = False
	pygame.draw.circle(background, (0, 78, 69), clickpos, random.randrange(15,70)) #dessiner un petit cercle
	screen.blit(background, (0, 0))

	pygame.display.update()

pygame.quit()