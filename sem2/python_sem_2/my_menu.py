import pygame
from pygame import mixer
import math
import random
from time import *
from os import path
import pygame_menu



def create_my_menu():
    mytheme = pygame_menu.themes.THEME_ORANGE.copy()
    mytheme.title_background_color=(0, 0, 0)

    menu = pygame_menu.Menu(400, 500, 'Hello', theme=mytheme)
    menu.add_button('Play', start_the_game)
    menu.add_selector('Difficulty : ', [('Hard', 1), ('Easy', 2)], onchange=set_dificulty)

    menu.add_button('Quit', pygame_menu.events.EXIT)
    menu.mainloop(root)
