from math import sin, cos, pi, radians, fabs,  floor
from utils import *
from datetime import datetime


def int_bresenham_array(xStart, xEnd, yStart, yEnd, color):
    pointsArray = []

    deltaX = xEnd - xStart
    deltaY = yEnd - yStart

    stepX = int(signum(deltaX))
    stepY = int(signum(deltaY))

    deltaX = abs(deltaX)
    deltaY = abs(deltaY)

    if deltaX < deltaY:
        deltaX, deltaY = deltaY, deltaX
        flag = True
    else:
        flag = False

    acc = deltaY + deltaY - deltaX
    curX = xStart
    curY = yStart

    for i in range(deltaX):
        pointsArray.append((color, (curX, curY)))

        if flag:
            if acc >= 0:
                curX += stepX
                acc -= (deltaX + deltaX)
            curY += stepY
            acc += deltaY + deltaY
        else:
            if acc >= 0:
                curY += stepY
                acc -= (deltaX + deltaX)
            curX += stepX
            acc += deltaY + deltaY




def wu_algorithm_array(xStart, xEnd, yStart, yEnd, color):
    pointsArray = []
    if xStart == xEnd and yStart == yEnd:
        pointsArray.append((set_intensity(color), (xStart, yStart)))
        return pointsArray

    deltaX = xEnd - xStart
    deltaY = yEnd - yStart

    stepX = int(signum(deltaX))
    stepY = int(signum(deltaY))

    deltaX = abs(deltaX)
    deltaY = abs(deltaY)

    if deltaX < deltaY:
        deltaX, deltaY = deltaY, deltaX
        flag = True
    else:
        flag = False

    tngModule = deltaY / deltaX

    acc = -1
    curX = xStart
    curY = yStart

    for i in range(deltaX):
        pointsArray.append((set_intensity(color, 1 + acc), (curX, curY)))

        pointsArray.append((set_intensity(color, -acc), (curX, curY + stepY)))
        if flag:
            if acc >= 0:
                curX += stepX
                acc -= 1
            curY += stepY
            acc += tngModule
        else:
            if acc >= 0:
                curY += stepY
                acc -= 1
            curX += stepX
            acc += tngModule
    return pointsArray



def step_bresenham_array(xStart, xEnd, yStart, yEnd, color):
    pointsArray = []
    if xStart == xEnd and yStart == yEnd:
        pointsArray.append((set_intensity(color), (xStart, yStart)))
        return pointsArray

    deltaX = xEnd - xStart
    deltaY = yEnd - yStart

    stepX = int(signum(deltaX))
    stepY = int(signum(deltaY))

    deltaX = abs(deltaX)
    deltaY = abs(deltaY)

    if deltaX < deltaY:
        deltaX, deltaY = deltaY, deltaX
        flag = True
    else:
        flag = False

    tngModule = deltaY / deltaX

    acc = 1 / 2
    correction = 1 - tngModule
    curX = xStart
    curY = yStart

    for i in range(deltaX):
        color = set_intensity(color)
        pointsArray.append((color, (curX, curY)))

        if flag:
            if acc >= correction:
                curX += stepX
                acc -= correction + tngModule
            curY += stepY
            acc += tngModule
        else:
            if acc >= correction:
                curY += stepY
                acc -= correction + tngModule
            curX += stepX
            acc += tngModule
    return pointsArray





def float_bresenham_array(xStart, xEnd, yStart, yEnd, color):
    pointsArray = []
    if xStart == xEnd and yStart == yEnd:
        pointsArray.append((color, (xStart, yStart)))
        return pointsArray

    deltaX = xEnd - xStart
    deltaY = yEnd - yStart

    stepX = int(signum(deltaX))
    stepY = int(signum(deltaY))

    deltaX = abs(deltaX)
    deltaY = abs(deltaY)

    if deltaX < deltaY:
        deltaX, deltaY = deltaY, deltaX
        flag = True
    else:
        flag = False

    tngModule = deltaY / deltaX

    acc = tngModule - 0.5
    curX = xStart
    curY = yStart

    for i in range(deltaX):
        pointsArray.append((color, (curX, curY)))
        if flag:
            if acc >= 0:
                curX += stepX
                acc -= 1
            curY += stepY
            acc += deltaY / deltaX
        else:
            if acc >= 0:
                curY += stepY
                acc -= 1
            curX += stepX
            acc += deltaY / deltaX
    return pointsArray






def dda_algorithm_array(xStart, xEnd, yStart, yEnd, color):
    pointsArray = []
    if xStart == xEnd and yStart == yEnd:
        pointsArray.append((color, (xStart, yStart)))
        return pointsArray

    deltaX = xEnd - xStart
    deltaY = yEnd - yStart

    trX = abs(deltaX)
    trY = abs(deltaY)

    length = trX if trX > trY else trY

    deltaX /= length
    deltaY /= length

    curX = xStart
    curY = yStart

    for i in range(length):
        pointsArray.append((color, (my_round(curX), my_round(curY))))
        curX += deltaX
        curY += deltaY
    return pointsArray