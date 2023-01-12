from decimal import ROUND_HALF_DOWN
import pygame
import sys
import random
import time

def getcolor(x, y):
    return (grid[x][y])

def drawGrid():
    for x in range(0, int(maxX)):
        for y in range(0, int(maxY)):
            rect = pygame.Rect(x*blockSize, y*blockSize, blockSize, blockSize)
            if [x, y] in posToKeep:
                pygame.draw.rect(SCREEN, getcolor(x, y) , rect, width=int((blockSize-2)/2))
            else:
                pygame.draw.rect(SCREEN, getcolor(x, y) , rect, width=int((blockSize)))

if __name__ == "__main__":
    blockSize = 80  #Set the size of the grid block

    CLOCK = pygame.time.Clock()
    pygame.init()
    difficulty = int(input("What difficulty would you like to play? (1-5):"))
    
    maxX = random.randint(3, 3*difficulty+3)
    maxY = random.randint(3, 3*difficulty+3)

    WINDOW_WIDTH = int(maxX*blockSize)
    WINDOW_HEIGHT = int(maxY*blockSize)

    SCREEN = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("color game")

    grid = []
    originalgrid = []

    posToKeep =  ([0, 0], [maxX-1, 0], [0, maxY-1], [maxX-1, maxY-1])

    for i in range(maxX):
        grid.append([])
        originalgrid.append([])
        for j in range(maxY):
            if i > j:
                grid[i].append(((int(i/maxX*255), int((maxX-i)/maxX*255), int(j/maxX*255))))
                originalgrid[i].append(((int(i/maxX*255), int((maxX-i)/maxX*255), int(j/maxX*255))))
            else:
                originalgrid[i].append(((int(i/maxY*255), int((maxY-j)/maxY*255), int(j/maxY*255))))
                grid[i].append(((int(i/maxY*255), int((maxY-j)/maxY*255), int(j/maxY*255))))

    firstclick = True
    # show initial grid
    drawGrid()
    pygame.display.update()
    #scramble grid
    time.sleep(2)
    xmlist = list(range(maxX))
    ymlist = list(range(maxY))

    random.shuffle(xmlist)
    for i in xmlist:
        random.shuffle(ymlist)
        for j in ymlist:
            # print([i, j])
            if not ([i, j] in posToKeep):
                if firstclick == True:
                    firstclick = False
                    firstpos = (i, j)
                else :
                    secondpos = (i, j)
                    temp = grid[firstpos[0]][firstpos[1]]
                    grid[firstpos[0]][firstpos[1]] = grid[secondpos[0]][secondpos[1]] 
                    grid[secondpos[0]][secondpos[1]]  = temp
                    drawGrid()
                    pygame.display.flip()
                    firstclick = True
            else:
                print("skipping")
    firstclick = True
    print(grid==originalgrid)
    # main game loop
    while True:
        drawGrid()
        pygame.display.update()
        if grid == originalgrid:
            print("You win!")
            break
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                x = int(event.pos[0]/blockSize)
                y = int(event.pos[1]/blockSize)
                if not ([x, y] in posToKeep):
                    if firstclick == True:
                        print(f"First click at {x}, {y}")
                        firstclick = False
                        firstpos = (x, y)
                    else :
                        print(f"Second click at {x}, {y}")
                        secondpos = (x, y)
                        # print(grid[x][y], originalgrid[x][y])
                        # swap grid[firstpos[0]][firstpos[1]]  and grid[secondpos[0]][secondpos[1]]
                        temp = grid[firstpos[0]][firstpos[1]]
                        grid[firstpos[0]][firstpos[1]] = grid[secondpos[0]][secondpos[1]] 
                        grid[secondpos[0]][secondpos[1]]  = temp
                        # print(grid[x][y])
                        firstclick = True
