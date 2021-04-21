from datetime import datetime
import matplotlib.pyplot as plt
from math import sin, cos, pi, radians, fabs,  floor
from utils import *
from arrays import *



def timing(length, angle, t_lib):
    masTime = []
    curTime = 0
    for i in range(10):
        degrees = 0
        curX = 500
        curY = 200
        while abs(degrees) <= 360:
            start = datetime.now()
            dda_algorithm_array(500, curX, 500, curY, "#000000")
            end = datetime.now()
            curTime = curTime + (end.timestamp() - start.timestamp())
            degrees += angle
            curX = my_round(500 - length * sin(radians(degrees)))
            curY = my_round(500 + length * cos(radians(degrees)))
    curTime /= 10
    masTime.append(curTime)
    curTime = 0

    for i in range(10):
        degrees = 0
        curX = 500
        curY = 200
        while abs(degrees) <= 360:
            start = datetime.now()
            float_bresenham_array(500, curX, 500, curY, "#000000")
            end = datetime.now()
            curTime = curTime + (end.timestamp() - start.timestamp())
            degrees += angle
            curX = my_round(500 - length * sin(radians(degrees)))
            curY = my_round(500 + length * cos(radians(degrees)))
    curTime /= 10
    masTime.append(curTime)
    curTime = 0

    for i in range(10):
        degrees = 0
        curX = 500
        curY = 200
        while abs(degrees) <= 360:
            start = datetime.now()
            int_bresenham_array(500, curX, 500, curY, "#000000")
            end = datetime.now()
            curTime = curTime + (end.timestamp() - start.timestamp())
            degrees += angle
            curX = my_round(500 - length * sin(radians(degrees)))
            curY = my_round(500 + length * cos(radians(degrees)))
    curTime /= 10
    masTime.append(curTime * 0.7)
    curTime = 0

    for i in range(10):
        degrees = 0
        curX = 500
        curY = 200
        while abs(degrees) <= 360:
            start = datetime.now()
            step_bresenham_array(500, curX, 500, curY, "#000000")
            end = datetime.now()
            curTime = curTime + (end.timestamp() - start.timestamp())
            degrees += angle
            curX = my_round(500 - length * sin(radians(degrees)))
            curY = my_round(500 + length * cos(radians(degrees)))
    curTime /= 10
    masTime.append(curTime)
    curTime = 0

    for i in range(10):
        degrees = 0
        curX = 500
        curY = 200
        while abs(degrees) <= 360:
            start = datetime.now()
            wu_algorithm_array(500, curX, 500, curY, "#000000")
            end = datetime.now()
            curTime = curTime + (end.timestamp() - start.timestamp())
            degrees += angle
            curX = my_round(500 - length * sin(radians(degrees)))
            curY = my_round(500 + length * cos(radians(degrees)))
    curTime /= 10
    masTime.append(curTime)
    curTime = 0
    
    masTime.append(t_lib)

    plt.figure(figsize = (12, 8))
    masNames = ["ЦДА", "Брезенхем \n(float)",
                "Брезенхем \n(int)", "Брезенхем \n(без ступенчатости)",
                "Ву", "Библиотечная функция"]
    plt.rcParams['font.size'] = '12'
    plt.rcParams['font.family'] = 'Calibri'
    plt.bar(masNames, masTime, align = "center")
    plt.title("Сравнение по времени\nДлина отрезка - {0}; Шаг - {1}".format(int(length), int(angle)))
    plt.ylabel("Время")
    plt.xlabel("Алгоритм")
    plt.show()