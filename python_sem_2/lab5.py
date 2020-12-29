import pygame
from pygame import mixer
import math
import random
from time import *
from os import path
# import pygame_menu

from my_menu import *

pygame.init()
root = pygame.display.set_mode((1200, 800))
pygame.display.set_caption("Move")


# mixer.init()
# mixer.music.load("background/main_sound.mp3")
# mixer.music.set_volume(0.4)
# mixer.music.play()



all_imgs = {}
for i in range(74):
    all_imgs["background/"+str(i)+".gif"] = pygame.image.load("background/"+str(i)+".gif")

main_obj_pic = pygame.image.load("background/ship.jpg")

score = 0


class BombShell(pygame.sprite.Sprite):

    def __init__(self, obj, x_dest, y_dest, group, click):
        pygame.sprite.Sprite.__init__(self)  # необходимое условие спрайтов
        self.x = obj.x + obj.width
        self.y = obj.y
        self.click = click
        self.image = pygame.image.load("car1.png").convert_alpha()
        self.rect = self.image.get_rect(center=(self.x, self.y))

        self.add(group)
        self.vel = random.randint(3, 10)
        self.x_dest = x_dest
        self.y_dest = y_dest
        print(x_dest, y_dest, "******", self.x, self.y)
        self.width = 10
        self.height = 10


        # LEFT_CLICK destination
        if x_dest < main_obj.x + main_obj.width and self.click == LEFT_CLICK:
            self.alpha = 1.570796 # 90 degree
        elif y_dest > main_obj.y and self.click == LEFT_CLICK:
            self.alpha = 0
        elif self.click == LEFT_CLICK:
            self.alpha = math.atan(abs((self.y_dest - self.y) / abs((self.x_dest - self.x))))

        # RIGHT_CLICK destination
        if x_dest < main_obj.x + main_obj.width and self.click == RIGHT_CLICK:
            self.alpha = 1.570796 # 90 degree
        elif y_dest < main_obj.y and self.click == RIGHT_CLICK:
            self.alpha = 0
        elif self.click == RIGHT_CLICK:
            self.alpha = math.atan(abs((self.y_dest - self.y) / abs((self.x_dest - self.x))))

    def update(self):
        global score
        if self.click == LEFT_CLICK:
            self.rect.x += self.vel * math.cos(self.alpha)
            self.rect.y -= self.vel * math.sin(self.alpha)

        if self.click == RIGHT_CLICK:
            self.rect.x += self.vel * math.cos(self.alpha)
            self.rect.y += self.vel * math.sin(self.alpha)

        hits = pygame.sprite.spritecollide(self, uppers, True) + pygame.sprite.spritecollide(self, downs, True)
        for hit in hits:
            score += 5
            update_score(score)

            self.kill()


        if self.rect.x > 1200 or self.rect.y > 650 or self.rect.x < 0 or self.rect.y < 0:
            self.kill()

class UpObject(pygame.sprite.Sprite):

    def __init__(self, group):
        pygame.sprite.Sprite.__init__(self)
        self.x = 1100
        self.y = 100
        self.image = pygame.image.load("car1.jpg")
        self.image.set_colorkey((255, 255, 255))
        self.rect = self.image.get_rect(center=(self.x, self.y))
        self.add(group)


        self.height = 50
        self.width = 50
        self.vel = random.randint(20, 30)

    def update(self):
        global score
        if self.rect.x > 0:
            self.rect.x -= self.vel
        else:
            score -= 5
            update_score(score)
            self.kill()

class DownObject(pygame.sprite.Sprite):

    def __init__(self, group):
        pygame.sprite.Sprite.__init__(self)
        self.x = 1100
        self.y = 600
        self.image = pygame.image.load("car1.jpg")
        self.image.set_colorkey((255,255,255))
        self.rect = self.image.get_rect(center=(self.x, self.y))
        self.add(group)


        self.height = 50
        self.width = 50
        self.vel = random.randint(10, 20)

    def update(self):
        global score

        if self.rect.x > 0:
            self.rect.x -= self.vel
        else:
            score -= 5
            update_score(score)
            self.kill()

class MainObject():

    def __init__(self):
        self.width = 200
        self.height = 200
        self.vel = 5
        self.x = 400
        self.y = 300



def update_score(score):
    global font, text, textRect

    text = font.render('Your score = ' + str(score), True, (255, 255, 255), (0, 0, 0))

    textRect = text.get_rect()
    textRect.center = (200, 700)

def start_the_game():
    global main_obj, uppers, downs, bombs
    global font, text, textRect
    global LEFT_CLICK, RIGHT_CLICK
    LEFT_CLICK = 1
    RIGHT_CLICK = 2



    main_obj = MainObject()

    bombs = pygame.sprite.Group()
    downs = pygame.sprite.Group()
    uppers = pygame.sprite.Group()

    first_query = time()
    second_query = time()

    UpObject(uppers)
    DownObject(downs)


    time_for_new_upper = time()
    time_for_new_down = time()
    period_down = random.randint(3, 5)
    period_upper = random.randint(3, 5)

    i = 0
    k = 0

    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render('Your score = 0', True, (255, 255, 255), (0, 0, 0))

    textRect = text.get_rect()
    textRect.center = (200, 700)


    while (True):

        root.fill((0, 0, 0))




        main_obj_pic.set_colorkey((255, 255, 255, 255))
        root.blit(all_imgs["background/"+str(i%74)+".gif"], (0, 0))


        if k % 5 == 0:
            i += 1
            k += 1
        else:
            k += 1




        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit()


        keys = pygame.key.get_pressed()
        clicks = pygame.mouse.get_pressed()

        # if pressed left mouse key
        if clicks[0] and time() - first_query > 0.1:
            first_query = time()
            x_dest, y_dest = pygame.mouse.get_pos()
            print(root.get_at((x_dest, y_dest)))
            BombShell(main_obj, x_dest, y_dest, bombs, LEFT_CLICK)

        # if pressed right mouse key
        if clicks[2] and time() - second_query > 0.1:
            second_query = time()
            x_dest, y_dest = pygame.mouse.get_pos()
            print(root.get_at((x_dest, y_dest)))
            BombShell(main_obj, x_dest, y_dest, bombs, RIGHT_CLICK)


        if time() - time_for_new_down > period_down:
            DownObject(downs)
            time_for_new_down = time()
            period_down = random.randint(2, 3)

        if time() - time_for_new_upper > period_upper:
            UpObject(uppers)
            time_for_new_upper = time()
            period_upper = random.randint(2, 3)




        if keys[pygame.K_LEFT] and main_obj.x > 0:
            main_obj.x -= main_obj.vel

        if keys[pygame.K_RIGHT] and main_obj.x < 1200 - main_obj.width:
            main_obj.x += main_obj.vel



        root.blit(main_obj_pic, (main_obj.x, main_obj.y))
        root.blit(text, textRect)

        bombs.draw(root)
        downs.draw(root)
        uppers.draw(root)

        pygame.display.update()
        pygame.time.delay(10)
        bombs.update()
        downs.update()
        uppers.update()


    pygame.quit()

start_the_game()
