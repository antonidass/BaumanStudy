import sys
import os

import ui
from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5.QtWidgets import QTableWidgetItem
from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter
from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPoint


WIDE = 761
HEIGHT = 651
UI_WIDE = 461
UI_HEIGHT = 11

global pen_color
global bg_color


class GUI(QtWidgets.QMainWindow, ui.Ui_GUI):
    def __init__(self):
        global bg_color, pen_color
        super().__init__()
        self.setupUi(self)
        self.setFixedSize(self.size())
        self.graphicsView.scale(1, 1)
        self.scene = QtWidgets.QGraphicsScene()
        self.graphicsView.setScene(self.scene)
        h = self.graphicsView.height()
        w = self.graphicsView.width()
        self.scene.setSceneRect(0, 0, w-2, h-2)

        bg_color = Qt.white
        pen_color = Qt.black
        self.pen = QPen(pen_color)
        self.pen.setWidth(1)

        self.image = QImage(WIDE, HEIGHT, QImage.Format_ARGB32_Premultiplied)
        self.image.fill(bg_color)

        self.black_back.clicked.connect(self.set_black_bg)
        self.white_back.clicked.connect(self.set_white_bg)
        
        self.white_fg.clicked.connect(self.set_white_pen)
        self.black_fg.clicked.connect(self.set_black_pen)

        self.clearScreenButton.clicked.connect(self.clean_screen)
        self.addPointButton.clicked.connect(self.add_point_btn)
        self.closeButton.clicked.connect(self.lock)
        self.drawButton.clicked.connect(self.fill_polygon)

        self.edges = []
        self.point_now = None
        self.point_start = None
 

    def set_black_bg(self):
        global bg_color
        bg_color = Qt.black
        self.graphicsView.setStyleSheet("background-color: black")

    def set_white_bg(self):
        global bg_color
        bg_color = Qt.white
        self.graphicsView.setStyleSheet("background-color: white")


    def set_black_pen(self):
        global pen_color
        pen_color = Qt.black
        self.pen.setColor(Qt.black)

    def set_white_pen(self):
        global pen_color
        pen_color = Qt.white
        self.pen.setColor(Qt.white)
    


    def draw_point(self, x, y):
        self.scene.addLine(x, y, x, y, self.pen)


    def clean_screen(self):
        l = self.table.rowCount()
        for i in range(l, -1, -1):
            self.table.removeRow(i)
        

        self.edges = []
        self.table.clearContents()
        self.point_now = None
        self.point_start = None
        self.scene.clear()
        self.image.fill(bg_color)


    
    def add_point(self, x, y):
        if not self.point_now:
            self.point_start = [x, y]
            self.draw_point(x, y)
        else:
            self.edges.append([self.point_now[0], self.point_now[1], x, y])
            self.scene.addLine(self.point_now[0], self.point_now[1], x, y, self.pen)

        self.point_now = [x, y]
        i = self.table.rowCount()
        self.add_row()
        x = QTableWidgetItem("{0}".format(x))
        y = QTableWidgetItem("{0}".format(y))
        self.table.setItem(i, 0, x)
        self.table.setItem(i, 1, y)
        


    def add_point_btn(self):
        try:
            x = int(self.X.text())
            y = int(self.Y.text())

        except ValueError:
            QtWidgets.QMessageBox.critical(self, "Ошибка!", "Неверные координаты точки!")
            return

        self.add_point(x, y)



    def lock(self):
        x1, y1 = self.point_now[0], self.point_now[1]
        x2, y2 = self.point_start[0], self.point_start[1]

        self.edges.append([x1, y1, x2, y2])
        self.scene.addLine(x1, y1, x2, y2, self.pen)

        self.point_now = None



    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            x = event.x() - UI_WIDE
            y = event.y() - UI_HEIGHT
            self.add_point(x, y)
        else:
            return self.lock()



    def draw_edges(self, image, edges):
        p = QPainter()
        p.begin(image)
        p.setPen(QPen(pen_color))
        for e in edges:
            p.drawLine(e[0], e[1], e[2], e[3])
        p.end()




    def delay(self, pix):
        QtWidgets.QApplication.processEvents(QEventLoop.AllEvents, 1)
        pix.convertFromImage(self.image)
        self.scene.addPixmap(pix)


    def find_max_x(self, edges):
        xm = None
        
        for i in range(len(edges)):
            if not xm or edges[i][0] > xm:
                xm = edges[i][0]

            if not xm or edges[i][2] > xm:
                xm = edges[i][2]

        return xm


    def displaytime(self, time):
        self.timeLabel.setText("Время: {0:.0f} msc".format(time))
        return


    def activate_pixel(self, p, x, cur_y):
        if QColor(self.image.pixel(x, cur_y)) == bg_color:
            p.setPen(QPen(pen_color))
        else:
            p.setPen(QPen(bg_color))
        


    def fill_polygon(self):
        t = QTime()
        pix = QPixmap()
        p = QPainter()

        t.start()
        xm = int(self.find_max_x(self.edges)) # находим крайнюю правую точку
        p.begin(self.image)

        for ed in self.edges:
            x1, y1 = ed[0], ed[1]
            x2, y2 = ed[2], ed[3]

            if y1 == y2:
                continue

            if y1 > y2:
                y1, y2 = y2, y1
                x1, x2 = x2, x1

            cur_y = y1
            end_y = y2
            dx = (x2 - x1) / (y2 - y1)
            start_x = x1

            while cur_y < end_y:
                x = start_x
                while x < xm:
                    self.activate_pixel(p, x, cur_y)
                    p.drawPoint(x, cur_y)
                    x += 1

                start_x += dx
                cur_y += 1
                if self.delayBox.isChecked():
                    self.delay(pix)

            pix.convertFromImage(self.image)
            self.scene.addPixmap(pix)
        p.end()
        self.displaytime(t.elapsed())
        self.draw_edges(self.image, self.edges)



    def add_row(self):
        self.table.insertRow(self.table.rowCount())



if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()