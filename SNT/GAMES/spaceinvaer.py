<<<<<<< HEAD
import pygame
from pygame.locals import *
import time
import math


WINDOW_WIDTH = int(1920)
WINDOW_HEIGHT = int(1080)

enemies = [
    [1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1],
    [1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1]
]

me = [WINDOW_WIDTH/2, WINDOW_HEIGHT-50, 250] # [x, y, shooting_delay(ms)]
bullets = []
def create_new_bullet(me, speed=35, id=len(bullets)+1):
    bullets.append([id, [me[0], me[1]+50], 35])# [id, (x, y), speed(px/ticks)]


scroll_enemy = 0
scroll_right = True

def draw_enemies(screen, enemies):
    for y in range(len(enemies)):
        for x in range(len(enemies[y])):
            if enemies[y][x] == 1:
                pygame.draw.rect(screen, (255,255,255), (x*80+15+scroll_enemy, y*80+15, 50, 50))

def draw_bullets(screen, bullets):
    for bullet in bullets:
        pygame.draw.rect(screen, (255,255,255), (bullet[1][0], bullet[1][1], 5, 5))

def draw_me(screen, me):
    pygame.draw.rect(screen, (255,255,255), (me[0], me[1], 50, 50))

# def get_enemy_length(enemies):
#     enemy_length = []
#     y = -1
#     for enemy_row in enemies:
#         y+=1
#         x = -1
#         for enemy_cell in enemy_row:
#             x+=1
#             if enemy_cell == 1:
#                 enemy_length[y] = x
#     return math.max(enemy_length)

if __name__ == "__main__":
    CLOCK = pygame.time.Clock()
    pygame.init()

    SCREEN = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("space invaders")
    while True:
        # events handling
        for event in pygame.event.get():
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                pygame.quit()
                exit()
            if (event.type == KEYDOWN and event.key == K_SPACE) or (event.type == MOUSEBUTTONDOWN and event.button == 1):
                create_new_bullet(me)
            if event.type == KEYDOWN and event.key == K_RIGHT:
                me[0] += 15
            if event.type == KEYDOWN and event.key == K_LEFT:
                me[0] -= 15
        # game logic
        # bullet handle
        for bullet in bullets:
            bullet[1][1] -= bullet[2]
            if bullet[1][1] < 0:
                bullets.remove(bullet)
        
        # screen handle
        SCREEN.fill((0,0,0))
        draw_enemies(SCREEN, enemies)
        draw_bullets(SCREEN, bullets)
        draw_me(SCREEN, me)

        

        pygame.display.update()
        CLOCK.tick(60)
        
        # if scroll_right:
        #     scroll_enemy += 15
        # else:
        #     scroll_enemy -= 15
        # if scroll_enemy > WINDOW_WIDTH :
        #     scroll_right = False
        # if scroll_enemy < 0:
        #     scroll_right = True
=======
import pygame
from pygame.locals import *
import time
import math


WINDOW_WIDTH = int(1920)
WINDOW_HEIGHT = int(1080)

enemies = [
    [1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1],
    [1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1]
]

me = [WINDOW_WIDTH/2, WINDOW_HEIGHT-50, 250] # [x, y, shooting_delay(ms)]
bullets = []
def create_new_bullet(me, speed=35, id=len(bullets)+1):
    bullets.append([id, [me[0], me[1]+50], 35])# [id, (x, y), speed(px/ticks)]


scroll_enemy = 0
scroll_right = True

def draw_enemies(screen, enemies):
    for y in range(len(enemies)):
        for x in range(len(enemies[y])):
            if enemies[y][x] == 1:
                pygame.draw.rect(screen, (255,255,255), (x*80+15+scroll_enemy, y*80+15, 50, 50))

def draw_bullets(screen, bullets):
    for bullet in bullets:
        pygame.draw.rect(screen, (255,255,255), (bullet[1][0], bullet[1][1], 5, 5))

def draw_me(screen, me):
    pygame.draw.rect(screen, (255,255,255), (me[0], me[1], 50, 50))

# def get_enemy_length(enemies):
#     enemy_length = []
#     y = -1
#     for enemy_row in enemies:
#         y+=1
#         x = -1
#         for enemy_cell in enemy_row:
#             x+=1
#             if enemy_cell == 1:
#                 enemy_length[y] = x
#     return math.max(enemy_length)

if __name__ == "__main__":
    CLOCK = pygame.time.Clock()
    pygame.init()

    SCREEN = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("space invaders")
    while True:
        # events handling
        for event in pygame.event.get():
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                pygame.quit()
                exit()
            if (event.type == KEYDOWN and event.key == K_SPACE) or (event.type == MOUSEBUTTONDOWN and event.button == 1):
                create_new_bullet(me)
            if event.type == KEYDOWN and event.key == K_RIGHT:
                me[0] += 15
            if event.type == KEYDOWN and event.key == K_LEFT:
                me[0] -= 15
        # game logic
        # bullet handle
        for bullet in bullets:
            bullet[1][1] -= bullet[2]
            if bullet[1][1] < 0:
                bullets.remove(bullet)
        
        # screen handle
        SCREEN.fill((0,0,0))
        draw_enemies(SCREEN, enemies)
        draw_bullets(SCREEN, bullets)
        draw_me(SCREEN, me)

        

        pygame.display.update()
        CLOCK.tick(60)
        
        # if scroll_right:
        #     scroll_enemy += 15
        # else:
        #     scroll_enemy -= 15
        # if scroll_enemy > WINDOW_WIDTH :
        #     scroll_right = False
        # if scroll_enemy < 0:
        #     scroll_right = True
>>>>>>> refs/remotes/github/master
