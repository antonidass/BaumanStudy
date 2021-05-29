import sys

import ui
from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5.QtWidgets import QTableWidgetItem
from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter
from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPoint
from time import perf_counter, sleep

from math import fabs, copysign

WIDE = 761
HEIGHT = 651
UI_WIDE = 461
UI_HEIGHT = 11



class GUI(QtWidgets.QMainWindow, ui.Ui_GUI):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setFixedSize(self.size())
        self.graphicsView.scale(1, 1)

        self.scene = MyScene(self, 0, 0, WIDE, HEIGHT)
        self.graphicsView.setScene(self.scene)

        h = self.graphicsView.height()
        w = self.graphicsView.width()
        self.scene.setSceneRect(0, 0, w-2, h-2)


        self.pen = QPen(Qt.black)
        self.pen.setWidth(1)
        self.image = QImage(WIDE, HEIGHT, QImage.Format_RGB32)
        self.image.fill(Qt.white)


        # подключаем кнопки выбора цвета
        self.bg_colorButton.clicked.connect(self.get_bg_color)    
        self.fg_colorButton.clicked.connect(self.get_fg_color)    
        self.edge_colorButton.clicked.connect(self.get_edge_color)    


        self.clearScreenButton.clicked.connect(self.clean_screen)
        self.addPointButton.clicked.connect(self.addPoint_btn)
        self.closeButton.clicked.connect(self.lock)
        self.drawButton.clicked.connect(self.fillFigure)


        self.point_list = []
        self.edge_list = []
        self.last_point = None
        self.seed_point = [0, 0]
        self.is_locked = False


        self.bg_color = QColor(Qt.white)
        self.edge_color = QColor(Qt.black)
        self.fg_color = QColor(229, 204, 255)
        self.first_color_buttons()




    def first_color_buttons(self):
        self.bg_colorButton.setStyleSheet("background-color:rgb"
                                    + self.color_in_str(self.bg_color.getRgb()))
        self.fg_colorButton.setStyleSheet("background-color:rgb"
                                        + self.color_in_str(self.fg_color.getRgb()))
        self.edge_colorButton.setStyleSheet("background-color:rgb"
                                        + self.color_in_str(self.edge_color.getRgb()))

    def get_bg_color(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            if color == self.edge_color:
                QtWidgets.QMessageBox.critical(self, "Ошибка", "Цвет фона и цвет границы совпадают")
                return

            self.bg_color = color
            self.bg_colorButton.setStyleSheet("background-color:rgb"
                                            + self.color_in_str(self.bg_color.getRgb()))
            self.graphicsView.setStyleSheet("background-color: rgb" + self.color_in_str(self.bg_color.getRgb()))
       
    def get_fg_color(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.fg_color = color
            self.fg_colorButton.setStyleSheet("background-color:rgb"
                                            + self.color_in_str(self.fg_color.getRgb()))
             
    def get_edge_color(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            if color == self.bg_color:
                QtWidgets.QMessageBox.critical(self, "Ошибка", "Цвет фона и цвет границы совпадают")
                return

            self.edge_color = color
            self.edge_colorButton.setStyleSheet("background-color:rgb"
                                                + self.color_in_str(self.edge_color.getRgb()))
            self.pen.setColor(color)


    def addPoint_btn(self):
        try:
            x = int(self.X.text())
            y = int(self.Y.text())

        except ValueError:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Неверные координаты точки!")
            return

        if self.checkSeedPoint.isChecked():
            self.update_seed(x, y)
        else:
            self.addPoint(x, y)



    def sign(self, a):
        if a == 0:
            return 0
        return a / abs(a)

    def traceEdge(self, edge):

        dx = edge[2] - edge[0]
        dy = edge[3] - edge[1]
        x, y = edge[0], edge[1]
        sx, sy = self.sign(dx), self.sign(dy)
        dx = fabs(dx)
        dy = fabs(dy)

        swap = 0

        if dy > dx:
            swap = 1
            dx, dy = dy, dx

        e = 2 * dy - dx

        for _ in range(int(dx + 1)):
            self.image.setPixel(int(x), int(y), self.edge_color.rgb())

            if e >= 0:
                if swap == 0:
                    y += sy
                else:
                    x += sx
                e -= (2 * dx)

            if e < 0:
                if swap == 0:
                    x += sx
                else:
                    y += sy
                e += (2 * dy)

        self.redraw()
    


    def traceFigure(self):
        for edge in self.edge_list:
            self.traceEdge(edge)


    def addPoint(self, x, y):
        if ([x, y] in self.point_list):
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Точка уже имеется в данном многоугольнике!")
            return


        x_table = QTableWidgetItem(str(x))
        y_table = QTableWidgetItem(str(y))
        curr_rows = self.table.rowCount()
        self.table.insertRow(curr_rows)
        self.table.setItem(curr_rows, 0, x_table)
        self.table.setItem(curr_rows, 1, y_table)

        self.drawPolyHandler(x, y)


    def drawPolyHandler(self, x, y):
        if self.last_point is not None:
            self.scene.addLine(self.last_point[0], self.last_point[1], x, y, self.pen)
            self.edge_list.append([self.last_point[0], self.last_point[1], x, y])
        else:
            self.first_point = [x, y]

        self.last_point = [x, y]
        self.point_list.append([x, y])



    def drawEdges(self):
        pix = QPixmap()
        painter = QPainter()

        painter.begin(self.image)

        pen = QPen(Qt.black)
        pen.setWidth(1)
        painter.setPen(pen)

        for edge in self.edge_list:
            painter.drawLine(int(edge[0]), int(edge[1]), int(edge[2]), int(edge[3]))

        painter.end()

        pix.convertFromImage(self.image)
        self.scene.clear()
        self.scene.addPixmap(pix)



    def lock(self):
        if len(self.edge_list) > 1:
            last = self.edge_list[-1]
            self.scene.addLine(self.first_point[0], self.first_point[1], last[2], last[3], self.pen)
            self.last_point = None
            self.edge_list.append([self.first_point[0], self.first_point[1],  last[2], last[3]])
            self.is_locked = True




    def fillFigure(self):
        if not self.is_locked:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Для закраски необходимо замкнуть фигуру!")
            return

        self.scene.clear()
        self.traceFigure()

        stack = [[self.seed_point[0], self.seed_point[1]]]
        color = self.fg_color.rgb()
        start = perf_counter()

        while len(stack):
            if self.delayBox.isChecked():
                QtWidgets.QApplication.processEvents(QEventLoop.AllEvents, 1)

            point = stack.pop()
            self.image.setPixel(int(point[0]), int(point[1]), color)

            x, y = point[0] + 1, point[1]

            while self.image.pixelColor(int(x), int(y)).rgb() not in [self.fg_color.rgb(), self.edge_color.rgb()]:
                self.image.setPixel(int(x), int(y), color)
                x += 1

            rborder = x - 1
            x = point[0] - 1

            while self.image.pixelColor(int(x), int(y)).rgb() not in [self.fg_color.rgb(), self.edge_color.rgb()]:
                self.image.setPixel(int(x), int(y), color)
                x -= 1

            self.redraw()
            lborder = x + 1
            sign = [1, -1]

            for i in sign:
                x = lborder
                y = point[1] + i

                while x <= rborder:
                    is_exist = False
                    while self.image.pixelColor(int(x), int(y)).rgb() not in [self.fg_color.rgb(), self.edge_color.rgb()] and x <= rborder:
                        is_exist = True
                        x += 1

                    if is_exist:
                        stack.append([int(x - 1), int(y)])
                    xi = x
                    while self.image.pixelColor(int(x), int(y)).rgb() not in [self.fg_color.rgb(), self.edge_color.rgb()] and x <= rborder:
                        x += 1
                    if x == xi:
                        x += 1

        end = perf_counter()
        if not self.delayBox.isChecked():
            self.displaytime((end - start) * 1000)
        self.drawEdges()



    def clean_screen(self):        
        self.edge_list = []
        self.point_list = []
        self.scene.clear()
        self.image.fill(self.bg_color)
        self.last_point = None
        self.is_locked = False

        self.table.clear()
        self.table.setRowCount(0)


    def color_in_str(self, color):
        return str("(" + str(color[0]) + "," + str(color[1]) + "," + str(color[2]) + ")")
    


    def displaytime(self, time):
        self.timeLabel.setText("Время: {0:.0f} msc".format(time))
        return


    def update_seed(self, x, y):
        self.seed_point = [x, y]
        self.seedLabel.setText("Точка затравки: (" + str(x) + ", " + str(y) + ")")



    def redraw(self):
        self.scene.clear()
        self.scene.addPixmap(QPixmap.fromImage(self.image))


class MyScene(QtWidgets.QGraphicsScene):
    def __init__(self, win: GUI, *args):
        super().__init__(*args)
        self.window = win
        
        self.last_x = None
        self.last_y = None

    def mousePressEvent(self, event: QtWidgets.QGraphicsSceneMouseEvent) -> None:
        if event.buttons() == Qt.LeftButton:
            if self.window.checkSeedPoint.isChecked():
                self.window.update_seed(int(event.scenePos().x()), int(event.scenePos().y())) 
            else:
                posx = event.scenePos().x()
                posy = event.scenePos().y()

                if event.modifiers() == Qt.KeyboardModifier.ShiftModifier:
                    if posy != self.last_y:
                        der = (posx - self.last_x) / (posy - self.last_y)
                    else:
                        der = 2
                    if abs(der) <= 1:
                        posx = self.last_x
                    else:
                        posy = self.last_y

                self.window.addPoint(posx, posy)

                self.last_x = posx
                self.last_y = posy
        elif event.buttons() == Qt.RightButton:
            self.window.lock()
        elif event.buttons() == Qt.MidButton:
            self.window.update_seed(int(event.scenePos().x()), int(event.scenePos().y()))

  

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()







