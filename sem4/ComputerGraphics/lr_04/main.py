# This Python file uses the following encoding: utf-8
import sys
import os

import numpy as np
import ui
import pyqtgraph as pg
import matplotlib.pyplot as plt

from time import time
from copy import deepcopy
from PyQt5 import QtWidgets, QtCore, QtGui
from math import sin, cos, pi, radians, fabs, floor, sqrt


WIDE = 900
HEIGHT = 900

NUMBER_OF_RUNS = 20
MAX_RADIUS = 10000
STEP = 1000


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

        self.n_check.clicked.connect(self.set_n_check)
        self.step_check.clicked.connect(self.set_step_check)
        self.R_beg_check.clicked.connect(self.set_r_beg_check)
        self.R_end_check.clicked.connect(self.set_r_end_check)

        self.ellipse.clicked.connect(self.set_elipse)
        self.circle.clicked.connect(self.set_circle)

        self.drawFigureButton.clicked.connect(self.draw_figure)
        self.drawSpectrumButton.clicked.connect(self.draw_spectr)

        self.clearScreenButton.clicked.connect(self.clean_screen)
        self.compareTimeButton.clicked.connect(self.compare_algos)


    def enable_all(self):
        self.N.setEnabled(True)
        self.step.setEnabled(True)
        self.R_begin.setEnabled(True)
        self.R_end.setEnabled(True)

    def set_n_check(self):
        self.enable_all()
        self.N.setEnabled(False)

    def set_step_check(self):
        self.enable_all()
        self.step.setEnabled(False)

    def set_r_beg_check(self):
        self.enable_all()
        self.R_begin.setEnabled(False)

    def set_r_end_check(self):
        self.enable_all()
        self.R_end.setEnabled(False)
    
    def set_elipse(self):
        self.R_a_figure.setEnabled(True)
        self.R_b_figure.setEnabled(True)
        self.R_a_spectr.setEnabled(True)
        self.R_b_spectr.setEnabled(True)

        self.R_figure.setEnabled(False)
        self.R_begin.setEnabled(False)
        self.R_end.setEnabled(False)
        self.groupBox_5.setEnabled(False)

        self.N.setEnabled(True)
        self.step.setEnabled(True)

    def set_circle(self):
        self.R_a_figure.setEnabled(False)
        self.R_b_figure.setEnabled(False)
        self.R_a_spectr.setEnabled(False)
        self.R_b_spectr.setEnabled(False)

        self.R_figure.setEnabled(True)
        self.R_begin.setEnabled(True)
        self.R_end.setEnabled(True)
        self.groupBox_5.setEnabled(True)

        if self.n_check.isChecked():
            self.N.setEnabled(False)
        elif self.step_check.isChecked():
            self.step.setEnabled(False)
        elif self.R_beg_check.isChecked():
            self.R_begin.setEnabled(False)
        elif self.R_end_check.isChecked():
            self.R_end.setEnabled(False)
        

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


    def draw_point(self, x, y):
        self.scene.addLine(x, y, x, y, self.pen)


    def clean_screen(self):
        self.scene.clear()



    def lib(self, p_center, rad, draw=True):   
        self.scene.addEllipse(p_center[0] - rad[0], p_center[1] - rad[1], rad[0] * 2, rad[1] * 2, self.pen)





    def draw_points_circle(self, x_c, y_c, x, y):
        self.draw_point(x_c + x, y_c + y)
        self.draw_point(x_c - x, y_c + y)
        self.draw_point(x_c + x, y_c - y)
        self.draw_point(x_c - x, y_c - y)

        self.draw_point(x_c + y, y_c + x)
        self.draw_point(x_c - y, y_c + x)
        self.draw_point(x_c + y, y_c - x)
        self.draw_point(x_c - y, y_c - x)


    def draw_points_ellipse(self, x_c, y_c, x, y):
        self.draw_point(x_c + x, y_c + y)
        self.draw_point(x_c - x, y_c + y)
        self.draw_point(x_c + x, y_c - y)
        self.draw_point(x_c - x, y_c - y)



    def parametric_circle(self, x_c, y_c, radius, draw=True):
        step = 1 / radius
        alpha = 0

        while (alpha < pi / 4 + step):
            x = round(radius * cos(alpha))
            y = round(radius * sin(alpha))

            if draw:
                self.draw_points_circle(x_c, y_c, x, y)

            alpha += step


    def parametric_ellipse(self, x_c, y_c, r_a, r_b, draw=True):
        if (r_a > r_b):
            step = 1 / r_a
        else:
            step = 1 / r_b

        alpha = 0

        while (alpha < pi / 2 + step):
            x = round(r_a * cos(alpha))
            y = round(r_b * sin(alpha))

            if draw:
                self.draw_points_ellipse(x_c, y_c, x, y)

            alpha += step


    def canonical_circle(self, x_c, y_c, radius, draw=True):
        edge = round(radius / sqrt(2))
        r_2 = radius * radius

        for x in range(0, edge + 1):
            y = round(sqrt(r_2 - x * x))

            if draw:
                self.draw_points_circle(x_c, y_c, x, y)


    def canonical_ellipse(self, x_c, y_c, r_a, r_b, draw=True):
        ra_2 = r_a * r_a
        rb_2 = r_b * r_b

        edge = round(ra_2 / sqrt(ra_2 + rb_2))

        for x in range(0, edge + 1):
            y = round(sqrt(1 - x * x / ra_2) * r_b)

            if draw:
                self.draw_points_ellipse(x_c, y_c, x, y)


        edge = round(rb_2 / sqrt(ra_2 + rb_2))

        for y in range(0, edge + 1):
            x = round(sqrt(1 - y * y / rb_2) * r_a)

            if draw:   
                self.draw_points_ellipse(x_c, y_c, x, y)



    def mid_point_circle(self, x_c, y_c, radius, draw=True):
        x = 0
        y = radius

        delta = 1 - radius

        while x <= y:

            if draw:
                self.draw_points_circle(x_c, y_c, x, y)

            x += 1

            if delta < 0:
                delta = delta + 2 * x + 1
            else:
                y -= 1
                delta = delta + 2 * (x - y) + 1



    def mid_point_ellipse(self, x_c, y_c, r_a, r_b, draw=True):
        x = 0
        y = r_b

        r_a_2 = r_a * r_a
        r_b_2 = r_b * r_b

        edge = round(r_a / sqrt(1 + r_b_2 / r_a_2))
        delta = r_b_2 - round(r_a_2 * (r_b - 1 / 4))

        while (x <= edge):
            if draw:
                self.draw_points_ellipse(x_c, y_c, x, y)

            if (delta > 0):
                y -= 1
                delta = delta - r_a_2 * y * 2

            x += 1

            delta = delta + r_b_2 * (2 * x + 1)

        x = r_a
        y = 0

        r_a_2 = r_a * r_a
        r_b_2 = r_b * r_b

        edge = round(r_b / sqrt(1 + r_a_2 / r_b_2))
        delta = r_a_2 - round(r_b_2 * (x - 1 / 4))

        while (y <= edge):
            if draw:
                self.draw_points_ellipse(x_c, y_c, x, y)

            if (delta > 0):
                x -= 1
                delta = delta - r_b_2 * x * 2

            y += 1

            delta = delta + r_a_2 * (2 * y + 1)



    def bres_circle(self, x_c, y_c, radius, draw=True):
        x = 0
        y = radius

        d_i = 2 * (1 - radius)
        eps = 0

        while (x <= y):
            if draw:
                self.draw_points_circle(x_c, y_c, x, y)
            if (d_i <= 0):

                eps = 2 * d_i + 2 * y - 1

                if (eps < 0):
                    param = 1
                else:
                    param = 2
                    
            elif (d_i > 0):
                eps = 2 * d_i - 2 * x - 1

                if (eps < 0):
                    param = 2
                else:
                    param = 3

            if (param == 1):
                x = x + 1
                d_i = d_i + 2 * x + 1
            elif (param == 2):
                x = x + 1
                y = y - 1
                d_i = d_i + 2 * x - 2 * y + 2
            else:
                y = y - 1
                d_i = d_i - 2 * y + 1


    def bres_ellipse(self, x_c, y_c, r_a, r_b, draw=True):
        x = 0
        y = r_b

        r_a_2 = r_a * r_a
        r_b_2 = r_b * r_b

        d_i = r_b_2 - r_a_2 * (2 * y + 1)

        eps = 0

        while (y >= 0):

            if draw:
                self.draw_points_ellipse(x_c, y_c, x, y)

            if (d_i <= 0):
                eps = 2 * d_i + (2 * y + 2) * r_a_2

                if (eps < 0):
                    param = 1
                else:
                    param = 2
            elif (d_i > 0):
                eps = 2 * d_i + (- 2 * x + 2) * r_b_2

                if (eps < 0):
                    param = 2
                else:
                    param = 3
            
            if (param == 1):
                x = x + 1
                d_i = d_i + (2 * x) * r_b_2 + r_b_2
            elif (param == 2):
                x = x + 1
                y = y - 1
                d_i = d_i + (2 * x) * r_b_2 - (2 * y) * r_a_2 + (r_a_2 + r_b_2)
            else:
                y = y - 1
                d_i = d_i - (2 * y) * r_a_2 + r_a_2







    def my_add_figure(self, p_center, rad, draw=True):
        if self.algoBox.currentText() == "Библиотечная функция":
            self.lib(p_center, rad)

        elif self.algoBox.currentText() == "Параметрическое уравнение":
            if self.ellipse.isChecked():
                self.parametric_ellipse(p_center[0], p_center[1], rad[0], rad[1], draw)
            else:
                self.parametric_circle(p_center[0], p_center[1], rad[0], draw)

        elif self.algoBox.currentText() == "Алгоритм средней точки":
            if self.ellipse.isChecked():
                self.mid_point_ellipse(p_center[0], p_center[1], rad[0], rad[1], draw)
            else:
                self.mid_point_circle(p_center[0], p_center[1], rad[0], draw)

        elif self.algoBox.currentText() == "Каноническое уравнение":
            if self.ellipse.isChecked():
                self.canonical_ellipse(p_center[0], p_center[1], rad[0], rad[1], draw)
            else:
                self.canonical_circle(p_center[0], p_center[1], rad[0], draw)

        elif self.algoBox.currentText() == "Брезенхем":
            if self.ellipse.isChecked():
                self.bres_ellipse(p_center[0], p_center[1], rad[0], rad[1], draw)
            else:
                self.bres_circle(p_center[0], p_center[1], rad[0], draw)

        else:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Неверно выбран метод!")


    def draw_figure(self):
        try:
            x_c = int(self.x_centr.text())
            y_c = int(self.y_centr.text())
            
            if self.ellipse.isChecked():
                a = int(self.R_a_figure.text())
                b = int(self.R_b_figure.text())
            else:
                a = int(self.R_figure.text())
                b = a
                
        except ValueError:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Неверно заданы параметры фигуры!")
            return

        self.my_add_figure([x_c, y_c], [a, b])


    def draw_ellipse_spectr(self):
        try:
            step = float(self.step.text())
            amount = int(self.N.text())
            r_a = float(self.R_a_spectr.text())
            r_b = float(self.R_b_spectr.text())
            x_c = int(self.x_centr.text())
            y_c = int(self.y_centr.text())
        except:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Неверно заданы параметры спектра!")
            return

        if (step <= 0):
            QtWidgets.QMessageBox.critical(self, "Ошибка", "Шаг радиуса должен быть выше нуля")
            return

        if (amount <= 0):
            QtWidgets.QMessageBox.critical(self, "Ошибка", "Количество должно быть больше нуля")
            return


        dot_c = [x_c, y_c]
        i = 0
        koef = r_b / r_a


        while (i < amount):
            rad = [r_a, r_b]

            self.my_add_figure(dot_c, rad)

            r_a += step
            r_b = (r_a * koef)
            
            i += 1


    def draw_circle_spectr(self):
        try:
            step = float(self.step.text())
            amount = int(self.N.text())
            r_beg = float(self.R_begin.text())
            r_end = float(self.R_end.text())
            x_c = int(self.x_centr.text())
            y_c = int(self.y_centr.text())
        except:
            QtWidgets.QMessageBox.critical(self, "Ошибка", "Неверно заданы параметры спектра!")
            return

        # Choose combination

        if self.n_check.isChecked():
            amount = int((r_end - r_beg) / step)

        elif self.step_check.isChecked():
            step = int((r_end - r_beg) / amount)
            
        elif self.R_beg_check.isChecked():
            r_beg = float(r_end - step * amount)

        elif self.R_end_check.isChecked():
            r_end = float(r_beg + step * amount)


        if (r_beg > r_end):
            QtWidgets.QMessageBox.critical(self, "Ошибка", "Начальный радиус не может быть больше конечного")
            return

        if (step <= 0):
            QtWidgets.QMessageBox.critical(self, "Ошибка", "Шаг радиуса должен быть выше нуля")
            return

        if (amount <= 0):
            QtWidgets.QMessageBox.critical(self, "Ошибка", "Количество должно быть больше нуля")
            return

        r_a = r_beg
        r_b = r_beg

        dot_c = [x_c, y_c]
        i = 0

        while (i < amount):
            rad = [r_a, r_b]

            self.my_add_figure(dot_c, rad)

            r_a += step
            r_b += step
            i += 1


    def draw_spectr(self):
        if self.ellipse.isChecked():
            self.draw_ellipse_spectr()
        else:
            self.draw_circle_spectr()



    def compare_algos(self):
        isCircle = True
        if self.circle.isChecked():
            r_a = STEP
            r_b = r_a
            name = "Окружность"
        else:
            r_a = STEP
            r_b = STEP
            name = "Эллипс"
            isCircle = False

        time_mes = []

        dot_c = [WIDE // 2, HEIGHT // 2]

        for i in range(1, 5):

            time_start = [0] * (MAX_RADIUS // STEP)
            time_end = [0] * (MAX_RADIUS // STEP)

            for _ in range(NUMBER_OF_RUNS):

                r_a = STEP
                r_b = STEP

                for k in range(MAX_RADIUS // STEP):
                    rad = [r_a, r_b]
                    
                    time_start[k] += time()

                    if isCircle:
                        if i == 1:
                            self.canonical_circle(dot_c[0], dot_c[1], rad[0], False)
                        elif i == 2:
                            self.parametric_circle(dot_c[0], dot_c[1], rad[0], False)
                        elif i == 3:
                            self.bres_circle(dot_c[0], dot_c[1], rad[0], False)
                        elif i == 4:
                            self.mid_point_circle(dot_c[0], dot_c[1], rad[0], False)

                    else:
                        if i == 1:
                            self.canonical_ellipse(dot_c[0], dot_c[1], rad[0], rad[1], False)
                        elif i == 2:
                            self.parametric_ellipse(dot_c[0], dot_c[1], rad[0], rad[1], False)
                        elif i == 3:
                            self.bres_ellipse(dot_c[0], dot_c[1], rad[0], rad[1], False)
                        elif i == 4:
                            self.mid_point_ellipse(dot_c[0], dot_c[1], rad[0], rad[1], False)


                    time_end[k] += time()

                    r_a += STEP
                    r_b += STEP

            size = len(time_start)

            res_time = list((time_end[j] - time_start[j]) / NUMBER_OF_RUNS for j in range(size))

            time_mes.append(res_time)


        rad_arr = list(i for i in range(0, MAX_RADIUS, STEP))
        plt.figure(figsize = (14, 6))

        plt.title("Замеры времени для различных методов\nФигура: " + name)


        plt.plot(rad_arr, time_mes[0], label = "Каноническое\nуравнеие")

        plt.plot(rad_arr, time_mes[1], label = "Параметрическое\nуравнение")

        plt.plot(rad_arr, time_mes[2], label = "Брезенхем")

        plt.plot(rad_arr, time_mes[3], label = "Алгоритм\nсредней точки")


        plt.xticks(np.arange(STEP, MAX_RADIUS, STEP))
        plt.legend()

        plt.ylabel("Время")
        plt.xlabel("Величина радиуса")

        plt.show()



if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()
