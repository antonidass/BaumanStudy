# This Python file uses the following encoding: utf-8
import sys
import os

import numpy as np
import ui
import pyqtgraph as pg
import matplotlib.pyplot as plt

from time import time
from time_compare import *
from copy import deepcopy
from PyQt5 import QtWidgets, QtCore, QtGui
from math import sin, cos, pi, radians, fabs, floor

from utils import *

class GUI(QtWidgets.QMainWindow, ui.Ui_GUI):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.graphicsView.scale(1, 1)
        self.scene = QtWidgets.QGraphicsScene()
        self.graphicsView.setScene(self.scene)
        h = self.graphicsView.height()
        w = self.graphicsView.width()
        self.scene.setSceneRect(0, 0, w-2, h-2)
        self.pen = QtGui.QPen(QtCore.Qt.black)
        self.pen.setWidth(0)


        self.black_back.clicked.connect(self.set_black_bg)
        self.white_back.clicked.connect(self.set_white_bg)
        self.yellow_back.clicked.connect(self.set_yellow_bg)
        
        self.white_fg.clicked.connect(self.set_white_pen)
        self.blue_fg.clicked.connect(self.set_blue_pen)
        self.black_fg.clicked.connect(self.set_black_pen)
        self.blue_fg_2.clicked.connect(self.set_red_pen)

        self.drawLineButton.clicked.connect(self.draw_line)
        self.drawSpectrumButton.clicked.connect(self.draw_spectr)

        self.clearScreenButton.clicked.connect(self.clean_screen)

        self.stepAllButton.clicked.connect(self.compare_steps)
        self.stepOneButton.clicked.connect(self.compare_steps_single)
        self.compareTimeButton.clicked.connect(self.whole_timing)



    def set_black_bg(self):
        self.graphicsView.setStyleSheet("background-color: black")

    def set_white_bg(self):
        self.graphicsView.setStyleSheet("background-color: white")

    def set_yellow_bg(self):
        self.graphicsView.setStyleSheet("background-color: grey")


    def set_black_pen(self):
        self.pen.setColor(QtCore.Qt.black)

    def set_white_pen(self):
        self.pen.setColor(QtCore.Qt.white)
    
    def set_blue_pen(self):
        self.pen.setColor(QtCore.Qt.blue)
    
    def set_red_pen(self):
        self.pen.setColor(QtCore.Qt.red)


    def clean_screen(self):
        self.scene.clear()


    def check_error(self, p_start, p_end, draw):
        if p_start[0] == p_end[0] and p_start[1] == p_end[1]:
            if draw:
                self.draw_point(round(p_start[0]), round(p_start[1]))
                QtWidgets.QMessageBox.critical(self, "Информация!", 
                                                     "Нарисована только одна точка, так как координаты начала и конца отрезка совпадают")
            return -1

        return 0
        

    def draw_point(self, x, y, light=255):
        color = self.pen.color()
        QtGui.QColor.setAlpha(color, light)
        self.pen.setColor(color)
        self.scene.addLine(x, y, x, y, self.pen)




    def bresenham_float(self, p_start, p_end, draw=True, steps=False):
        if (self.check_error(p_start, p_end, draw)):
            return
        
        dx = p_end[0] - p_start[0]
        dy = p_end[1] - p_start[1]
        
        s_x = signum(dx)
        s_y = signum(dy)
        
        dx = abs(dx)
        dy = abs(dy)
        
        if (dy >= dx):
            dx, dy = dy, dx
            change = 1
        else:
            change = 0
        
        m = float(dy / dx)
        e = m - 0.5
        
        x = round(p_start[0])
        y = round(p_start[1])
        
        i = 1
        step = 1
        x_buf = x
        y_buf = y
        
        while i <= dx + 1:
            if draw:
                self.draw_point(x, y)
            
            if e >= 0:
                if change == 1:
                    x += s_x
                else:
                    y += s_y
                e -= 1
            
            if e <= 0:
                if change == 1:
                    y += s_y
                else:
                    x += s_x
                e += m 
            i += 1
            
            if steps:
                if not((x_buf == x and y_buf != y) or
                    (x_buf != x and y_buf == y)):
                    step += 1
                x_buf = x
                y_buf = y
        
        if steps:
            return step
    

    def bresenham_int(self, p_start, p_end, draw=True, steps=False):
        if (self.check_error(p_start, p_end, draw)):
            return
        
        dx = p_end[0] - p_start[0]
        dy = p_end[1] - p_start[1]
        
        s_x = signum(dx)
        s_y = signum(dy)
        
        dx = abs(dx)
        dy = abs(dy)
        
        if (dy >= dx):
            dx, dy = dy, dx
            change = 1
        else:
            change = 0
        
        m = 2 * dy
        m1 = 2 * dx
        e = 2 * dy - dx
        
        x = round(p_start[0])
        y = round(p_start[1])
        
        i = 1
        step = 1
        x_buf = x
        y_buf = y
        
        while i <= dx + 1:
            if (draw):
                self.draw_point(x, y)
            
            if e >= 0:
                if change == 1:
                    x += s_x
                else:
                    y += s_y
                e -= m1
            
            if e <= 0:
                if change == 1:
                    y += s_y
                else:
                    x += s_x
                e += m
            i += 1
            
            if steps:
                if not((x_buf == x and y_buf != y) or
                    (x_buf != x and y_buf == y)):
                    step += 1
                x_buf = x
                y_buf = y
        
        if steps:
            return step


    def bresenham_smooth(self, p_start, p_end, draw=True, steps=False):
        I = 255
        
        if (self.check_error(p_start, p_end, draw)):
            return
        
        dx = p_end[0] - p_start[0]
        dy = p_end[1] - p_start[1]
        
        s_x = signum(dx)
        s_y = signum(dy)
        
        dx = abs(dx)
        dy = abs(dy)
        
        if (dy >= dx):
            dx, dy = dy, dx
            change = 1
        else:
            change = 0
        
        m = dy / dx
        e = I / 2
        
        x = round(p_start[0])
        y = round(p_start[1])
        
        m *= I
        W = I - m
        if draw:
            self.draw_point(x, y, round(e))
        i = 1
        step = 1
        x_buf = x
        y_buf = y
        
        while i <= dx:
            if e < W:
                if change == 0:
                    x += s_x
                else:
                    y += s_y
                e += m
            else:
                x += s_x
                y += s_y
                e -= W
            
            if draw:
                self.draw_point(x, y, round(e))
            
            if steps:
                if not((x_buf == x and y_buf != y) or
                    (x_buf != x and y_buf == y)):
                    step += 1
                x_buf = x
                y_buf = y
            i += 1
        
        if steps:
            return step

        
    def dda(self, p_start, p_end, draw=True, steps=False):
        if (self.check_error(p_start, p_end, draw)):
            return
        
        dx = p_end[0] - p_start[0]
        dy = p_end[1] - p_start[1]
        
        if abs(dx) > abs(dy):
            length = abs(dx)
        else:
            length = abs(dy)

        sx = (p_end[0] - p_start[0]) / length
        sy = (p_end[1] - p_start[1]) / length

        x = p_start[0]
        y = p_start[1]
        i = 1
        step = 1
        
        while i <= length + 1:
            if (draw):
                self.draw_point(round(x), round(y))
            
            if steps and i <= length:
                if not((round(x + sx) == round(x) and 
                        round(y + sy) != round(y)) or 
                        (round(x + sx) != round(x) and 
                        round(y + sy) == round(y))):
                    step += 1
            x += sx
            y += sy
            i += 1
        
        if steps:
            return step
    

    def WU(self, p_start, p_end, draw=True, steps=False):
        Imax = 255
        
        if (self.check_error(p_start, p_end, draw)):
            return
        
        dx = p_end[0] - p_start[0]
        dy = p_end[1] - p_start[1]
        
        m = 1
        stepping = 1
        step = 1
        
        if fabs(dy) > fabs(dx):
            if dy != 0:
                m = dx / dy
            m1 = m
            
            if p_start[1] > p_end[1]:
                m1 *= -1
                stepping *= -1
            
            for y in range(round(p_start[1]), round(p_end[1]) + 1, stepping):
                d1 = p_start[0] - floor(p_start[0])
                d2 = 1 - d1
                if draw:
                    self.draw_point(int(p_start[0]), y, round(fabs(d2) * Imax))
                    self.draw_point(int(p_start[0]) + 1, y, round(fabs(d1) * Imax))
                
                if steps and y < round(p_end[1]):
                    if int(p_start[0]) != int(p_start[0] + m):
                        step += 1
                p_start[0] += m1
        else:
            if dx != 0:
                m = dy / dx
            m1 = m
            
            if p_start[0] > p_end[0]:
                stepping *= -1
                m1 *= -1
            
            for x in range(round(p_start[0]), round(p_end[0]) + 1, stepping):
                d1 = p_start[1] - floor(p_start[1])
                d2 = 1 - d1
                if draw:
                    self.draw_point(x, int(p_start[1]), round(fabs(d2) * Imax))
                    self.draw_point(x, int(p_start[1]) + 1, round(fabs(d1) * Imax))
                
                if steps and x < round(p_end[0]):
                    if int(p_start[1]) != int(p_start[1] + m):
                        step += 1
                p_start[1] += m1
        
        if steps:
            return step


    def lib(self, p_start, p_end):
        if (self.check_error(p_start, p_end, True)):
            return
   
        self.scene.addLine(round(p_start[0]), round(p_start[1]), 
                           round(p_end[0]), round(p_end[1]), self.pen)







    def my_addline(self, p_start, p_end, draw=True):
        if self.cda.isChecked():
            self.dda(p_start, p_end, draw=draw)

        elif self.bres_float.isChecked():
            self.bresenham_float(p_start, p_end, draw=draw)

        elif self.bres_int.isChecked():
            self.bresenham_int(p_start, p_end, draw=draw)

        elif self.bres_step.isChecked():
            self.bresenham_smooth(p_start, p_end, draw=draw)

        elif self.wu.isChecked():
            self.WU(p_start, p_end, draw=draw)

        else:
            self.lib(p_start, p_end)

    def draw_line(self):
        try:
            x_start = int(self.x_beg.text())
            x_end = int(self.x_end.text())
            y_start = int(self.y_beg.text())
            y_end = int(self.y_end.text())
        except ValueError:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Координаты начала и конца отрезка должны быть "
                                                     "целыми числами!")
            return
        self.my_addline([x_start, y_start], [x_end, y_end])



    def draw_spectr(self, buf=False, draw=True):
        try:
            angle = int(self.step.text())
            length = int(self.radius.text())
        except ValueError:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", 
                    "Шаг и радиус должны быть целыми числами!")
            return 
        
        if angle <= 0:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Шаг должен быть положительным!")
            return 
        
        if length <= 0:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Радиус должен быть положительным!")
            return
        
        alpha = 0
        
        h = self.graphicsView.height()
        w = self.graphicsView.width()
        
        while alpha < 2 * pi - 0.001:
            x = w // 2 + length * cos(alpha)
            y = h // 2 + length * sin(alpha)
            self.my_addline([w // 2, h // 2], [x, y], draw=draw)
            alpha += radians(angle)



    def get_length_and_angle(self):
        try:
            angle = int(self.step.text())
            length = int(self.radius.text())
        except ValueError:
            length = 250
            angle = 1

        return length, angle


    def whole_timing(self):
        length, angle = self.get_length_and_angle()
        if length is None or angle is None:
            return
        
        h = self.graphicsView.height()
        w = self.graphicsView.width()
        self.library.toggle()
        
        start = time()
        
        for _ in range(10):
            alpha = 0
            while alpha < 2 * pi - 0.001:
                x = w // 2 + length * cos(alpha)
                y = h // 2 + length * sin(alpha)
                self.scene.addLine(w // 2, h // 2, x, y)
                alpha += radians(angle)
        
        t_lib = ((time() - start) / 10)
        
        self.scene.clear()
        
        timing(length, angle, t_lib)



    def compare_steps(self):
        try:
            angle = float(self.step.text())
            length = float(self.radius.text())
        except:
            length = 10
            angle = 5
        h = self.graphicsView.height()
        w = self.graphicsView.width()
        cda = []
        b_float = []
        b_int = []
        b_smooth = []
        wu = []

        alpha = 0
        angle = [i for i in range(0, 91, 1)]
        while alpha <= pi / 2 + 0.01:
            x = w // 2 + length * cos(alpha)
            y = h // 2 + length * sin(alpha)
            cda.append(self.dda([w // 2, h // 2], [x, y], False, True))
            b_float.append(self.bresenham_float([w // 2, h // 2], [x, y], False, True))
            b_int.append(self.bresenham_int([w // 2, h // 2], [x, y], False, True))
            b_smooth.append(self.bresenham_smooth([w // 2, h // 2], [x, y], False, True))
            wu.append(self.WU([w // 2, h // 2], [x, y], False, True))
            alpha += radians(1)

        plt.figure(figsize=(12, 8))
        plt.rcParams['font.size'] = '14'
        plt.rcParams['font.family'] = 'Calibri'
        plt.plot(angle, cda, label='ЦДА')
        plt.plot(angle, b_float, label='Брезенхем\n(float/int)')
        plt.plot(angle, b_smooth, label='Брезенхем\n(без ступечатости)', linestyle='-.')
        plt.plot(angle, wu, label='Ву', linestyle=':')
        plt.title("Исследование ступенчатости\nДлина отрезка - {0}".format(length))
        plt.legend()
        plt.ylabel("Количество ступенек")
        plt.xlabel("Угол (в градусах)")
        plt.show()


    def compare_steps_single(self):
        try:
            angle = float(self.step.text())
            length = float(self.radius.text())
        except:
            length = 10
            angle = 5
        
        h = self.graphicsView.height()
        w = self.graphicsView.width()
        
        cda = []
        b_float = []
        b_smooth = []
        wu = []

        alpha = 0
        angle = [i for i in range(0, 91, 1)]
        
        while alpha <= pi / 2 + 0.01:
            x = w // 2 + length * cos(alpha)
            y = h // 2 + length * sin(alpha)
            
            if (self.cda.isChecked()):
                cda.append(self.dda([w // 2, h // 2], [x, y], False, True))
            elif (self.bres_float.isChecked() or
                  self.bres_int.isChecked()):
                b_float.append(self.bresenham_float([w //2, h // 2], [x, y], False, True))
            elif (self.bres_step.isChecked()):
                b_smooth.append(self.bresenham_smooth([w //2, h // 2], [x, y], False, True))
            elif (self.wu.isChecked()):
                wu.append(self.WU([w // 2, h // 2], [x, y], False, True))
            elif (self.library.isChecked()):
                QtWidgets.QMessageBox.critical(self, "Ошибка!", "Нельзя исследовать библиотечную функцию на ступенчатость")
                return
            alpha += radians(1)

        plt.figure(figsize=(12, 8))
        plt.rcParams['font.size'] = '14'
        plt.rcParams['font.family'] = 'Calibri'
        if (self.cda.isChecked()):
            plt.plot(angle, cda, label='ЦДА')
        elif (self.bres_float.isChecked() or
              self.bres_int.isChecked()):
            plt.plot(angle, b_float, label='Брезенхем\n(float/int)')
        elif (self.bres_step.isChecked()):
            plt.plot(angle, b_smooth, label='Брезенхем\n(сглаживание)')
        elif (self.wu.isChecked()):
            plt.plot(angle, wu, label='Ву')
        
        plt.title("Исследование ступенчатости\nДлина отрезка - {0}".format(int(length)))
        plt.legend()
        plt.ylabel("Количество ступенек")
        plt.xlabel("Угол (в градусах)")
        plt.show()




if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()
