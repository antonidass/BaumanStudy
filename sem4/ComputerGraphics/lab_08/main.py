import sys

import ui
from math import *

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *





WIDE = 761
HEIGHT = 651
UI_WIDE = 461
UI_HEIGHT = 11



VISIBLE_LINE = 1
PARTLY_VISIBLE_LINE = 0
INVISIBLE_LINE = -1

HORIZONTAL_LINE = 0
NORMAL_LINE = 1
VERTICAL_LINE = -1

# FOR RECTANGLE #

LEFT = 0
RIGHT = 1
DOWN = 2
UP = 3

# FOR LINE #

X = 0
Y = 1

X1 = 0
Y1 = 1
X2 = 2
Y2 = 3



class GUI(QMainWindow, ui.Ui_GUI):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setFixedSize(self.size())
        self.graphicsView.scale(1, 1)

        self.scene = QGraphicsScene(0, 0, WIDE, HEIGHT)
        self.scene.setSceneRect(0, 0, WIDE - 2, HEIGHT - 2)
        self.graphicsView.setScene(self.scene)

        self.pen = QPen(Qt.black)
        self.pen.setWidth(1)

        self.cutter_color = QColor(100, 200, 100)
        self.line_color = QColor(Qt.black)
        self.cut_line_color = QColor(229, 204, 255)

        self.polygon = list()
        self.lines = list()
        self.cur_line = list()

        self.full_polygon = False
        self.isConvex = False
        self.direction = -1

        self.ctrl_pressed = False

        self.cutOff_colorButton.clicked.connect(self.get_cutter_color)    
        self.result_colorButton.clicked.connect(self.get_result_color)    
        self.segment_olorButton.clicked.connect(self.get_line_color)    

        self.clearScreenButton.clicked.connect(self.clean_screen)
        self.addSegmentButton.clicked.connect(self.get_line)
        self.addCutterPointButton.clicked.connect(self.get_cutter_point)
        self.lockCutterButton.clicked.connect(self.close_cutter)
        self.cutterButton.clicked.connect(self.cut_all)
        self.delCutterButton.clicked.connect(self.del_cutter)
        
        self.first_color_buttons()

        self.graphicsView.setMouseTracking(True)
        self.graphicsView.viewport().installEventFilter(self)


    def first_color_buttons(self):
        self.cutOff_colorButton.setStyleSheet("background-color:rgb"
                                    + self.color_in_str(self.cutter_color.getRgb()))
        self.segment_olorButton.setStyleSheet("background-color:rgb"
                                        + self.color_in_str(self.line_color.getRgb()))
        self.result_colorButton.setStyleSheet("background-color:rgb"
                                        + self.color_in_str(self.cut_line_color.getRgb()))

    def get_cutter_color(self):
        color = QColorDialog.getColor()
        if color.isValid():
            if color == self.line_color:
                QMessageBox.critical(self, "Ошибка", "Цвет отсекателя и цвет отрезков совпадают!")
                return

            self.cutter_color = color
            self.cutOff_colorButton.setStyleSheet("background-color:rgb"
                                            + self.color_in_str(self.cutter_color.getRgb()))
       
    def get_line_color(self):
        color = QColorDialog.getColor()
        if color.isValid():
            self.line_color = color
            self.segment_olorButton.setStyleSheet("background-color:rgb"
                                            + self.color_in_str(self.line_color.getRgb()))
            self.pen.setColor(color)
             
    def get_result_color(self):
        color = QColorDialog.getColor()
        if color.isValid():
            print(color, self.line_color)
            if color == self.line_color:
                QMessageBox.critical(self, "Ошибка", "Цвет результата и цвет отрезка совпадают. ")
                return

            self.cut_line_color = color
            self.result_colorButton.setStyleSheet("background-color:rgb"
                                                + self.color_in_str(self.cut_line_color.getRgb()))



    def get_line(self):
        try:
            x1 = int(self.X_1.text())
            y1 = int(self.Y_1.text())
            x2 = int(self.X_2.text())
            y2 = int(self.Y_2.text())
        except ValueError:
            QMessageBox.critical(self, "Ошибка", "Введены некорректные данные отрезка!")
            return -1

        if x1 < 0 or x2 < 0 or y1 < 0 or y2 < 0 or x1 > WIDE or x2 > WIDE or y1 > HEIGHT or y2 > HEIGHT:
            QMessageBox.critical(self, "Ошибка", "Отрезок находится за пределами экрана!")
            return -1
            

        self.add_line(QLineF(float(x1), float(y1), float(x2), float(y2)))

    def get_cutter_point(self):
        try:
            x = int(self.X_cutter.text())
            y = int(self.Y_cutter.text())
        except ValueError:
            QMessageBox.critical(self, "Ошибка", "Введены некорректные данные отсекателя!")
            return -1

        if x < 0 or y < 0 or x > WIDE or y > HEIGHT:
            QMessageBox.critical(self, "Ошибка", "Введнная точка находится за пределами экрана!")
            return -1

        self.add_cutter(QPoint(x, y))

    def mousePressEvent(self, event):
        if event.buttons() == Qt.LeftButton and self.cutterRadio.isChecked():
            x = event.x() - UI_WIDE
            y = event.y() - UI_HEIGHT
            if (x < 0 or y < 0 or x > WIDE or y > HEIGHT):
                return

            if self.ctrl_pressed and len(self.polygon) > 0:
                dx = x - self.polygon[-1].x()
                dy = y - self.polygon[-1].y()

                if abs(dy) >= abs(dx):
                    cur = QPoint(self.polygon[-1].x(), y)
                else:
                    cur = QPoint(x, self.polygon[-1].y())
                self.add_cutter_event(cur)
            else:    
                self.add_cutter_event(QPoint(x, y))

        elif event.buttons() == Qt.LeftButton and self.segmentRadio.isChecked():
            x = event.x() - UI_WIDE
            y = event.y() - UI_HEIGHT
            if (x < 0 or y < 0 or x > WIDE or y > HEIGHT):
                return

            if self.ctrl_pressed and len(self.cur_line) > 0:
                dx = x - self.cur_line[0].x()
                dy = y - self.cur_line[0].y()

                if abs(dy) >= abs(dx):
                    cur = QPointF(self.cur_line[0].x(), y)
                else:
                    cur = QPointF(x, self.cur_line[0].y())
                self.add_line_event(cur)
            else:    
                self.add_line_event(QPoint(x, y))

        elif event.buttons() == Qt.RightButton:
            self.close_cutter()

    def keyPressEvent(self, event):
        key = event.key()
        if key == Qt.Key_Control:
            self.ctrl_pressed = True

    def keyReleaseEvent(self, event):
        key = event.key()
        if key == Qt.Key_Control:
            self.ctrl_pressed = False


    def eventFilter(self, source, event):
        if event.type() == QEvent.MouseMove and source is self.graphicsView.viewport():
            self.change_position(QPoint(event.x(), event.y()))
        return QWidget.eventFilter(self, source, event)

    def drawPoly(self):
        pol = QPolygonF()

        for i in range(len(self.polygon)):
            pol.append(self.polygon[i])

        polygon_path = QPainterPath()
        polygon_path.addPolygon(pol) 

        pix = QPixmap()
        painter = QPainter()

        image = QImage(WIDE, HEIGHT, QImage.Format_RGB32)
        image.fill(Qt.white)
        painter.begin(image)

        pen = QPen(self.line_color)
        pen.setWidth(1)
        painter.setPen(pen)
           
        for line in self.lines:
            painter.drawLine(line)

        painter.fillPath(polygon_path, QBrush(Qt.white))
        pen = QPen(self.cutter_color)
        painter.setPen(pen)

        painter.end()
        pix.convertFromImage(image)
        self.scene.clear()
        self.scene.addPixmap(pix)
        
    def change_position(self, point):
        self.curPointLabel.setText("x: " + str(round(point.x())) + " y: " + str(round(point.y())))


    def add_line_event(self, point):
        self.cur_line.append(point)

        if len(self.cur_line) == 2:
            self.add_line(QLineF(self.cur_line[0], self.cur_line[1]))
            self.cur_line = list()


    def add_line(self, line):
        self.lines.append(line)
        self.scene.addLine(line, self.pen)


    def add_cutter_event(self, point):
        self.add_cutter(point)


    def add_cutter(self, point):
        if self.full_polygon:
            QMessageBox.warning(self, "Ошибка", "Отсекатель уже введен")
            return

        self.polygon.append(point)
        size = len(self.polygon)

        if size > 1:
            self.scene.addLine(QLineF(self.polygon[size - 2], self.polygon[size - 1]), QPen(self.cutter_color))


    def del_cutter(self):
        self.polygon = list()
        self.full_polygon = False
        self.scene.clear()
        self.draw_all_lines()


    def draw_all_lines(self):
        for line in self.lines:
            self.scene.addLine(line, QPen(self.line_color))





    def close_cutter(self):
        size = len(self.polygon)
        if size > 2:
            self.add_cutter(self.polygon[0])
            self.full_polygon = True
            isConvex, _sign = self.is_convex(self.polygon)

            if isConvex:
                self.isConvex = True
                self.direction = _sign
            else:
                self.isConvex = False
                QMessageBox().warning(self, "Ошибка", "Отсекатель невыпуклый")


    def sign(self, x):
        if x == 0:
            return 0

        return x / fabs(x)


    def is_convex(self, polygon):
        size = len(polygon)
        array_vector = list()
        _sign = 0

        if size < 3:
            return False, _sign

        for i in range(1, size):
            if i < size - 1:
                ab = QPointF(polygon[i].x() - polygon[i - 1].x(), polygon[i].y() - polygon[i - 1].y())
                bc = QPointF(polygon[i + 1].x() - polygon[i].x(), polygon[i + 1].y() - polygon[i].y())
            else:
                ab = QPointF(polygon[i].x() - polygon[i - 1].x(), polygon[i].y() - polygon[i - 1].y())
                bc = QPointF(polygon[1].x() - polygon[0].x(), polygon[1].y() - polygon[0].y())

            array_vector.append(ab.x() * bc.y() - ab.y() * bc.x())

        exist_sign = False
        for i in range(len(array_vector)):
            if array_vector[i] == 0:
                continue

            if exist_sign:
                if self.sign(array_vector[i]) != _sign:
                    return False, _sign
            else:
                _sign = self.sign(array_vector[i])
                exist_sign = True

        return True, _sign


    # def SignVectorProduct(self, line1, line2):
    #     V1 = [line1[2] - line1[0], line1[3] - line1[1]]
    #     V2 = [line2[2] - line2[0], line2[3] - line2[1]]
    #     temp = V1[0] * V2[1] - V2[0] * V1[1]
    #     if fabs(temp) <= 1e-3:
    #         return
    #     return 1 if temp > 0 else -1


    # def is_convex(self, polygon):
    #     for temp in polygon:
    #         if len(temp):
    #             sign = self.SignVectorProduct(temp[-1], temp[0])
    #         for i in range(len(temp) - 1):
    #             next_sign = self.SignVectorProduct(temp[i], temp[i + 1])
    #             if not next_sign:
    #                 continue
    #             if sign != next_sign:
    #                 return False
    #     return sign



    def cut_all(self):
        if not self.isConvex:
            QMessageBox().warning(self, "Ошибка", "Отсекатель невыпуклый")
            return


        self.scene.clear()
        self.drawPoly()

        if self.full_polygon:        
            i = 0
            for line in self.lines:
                code = self.kirus_bek(self.polygon, line, self.direction)
                # i += 1
                # if code == 0:
                #     print(i, ": SUCCESS")
                # elif code == 1:
                #     print(i, ": WSCALAR < 0")
                # elif code == 2:
                #     print(i, ": T > 0")
                # elif code == 3:
                #     print(i, ": T < 0")
                # elif code == 4:
                #     print(i, ": TB > TE")
        for i in range(len(self.polygon) - 1):
            self.scene.addLine(QLineF(self.polygon[i], self.polygon[i + 1]), QPen(self.cutter_color))


    def scalar(self, p1, p2):
        return p1.x() * p2.x() + p1.y() * p2.y()

    def kirus_bek(self, polygon, line, n):
        tb = 0
        te = 1
        x = line.p1().x()
        y = line.p1().y()
        D = QPointF(line.p2().x() - x, line.p2().y() - y)

        for i in range(len(polygon) - 1):
            W = QPointF(x - polygon[i].x(), y - polygon[i].y())
            N = QPointF(-n * (polygon[i + 1].y() - polygon[i].y()), n * (polygon[i + 1].x() - polygon[i].x()))

            Dscalar = self.scalar(D, N)
            Wscalar = self.scalar(W, N)

            if fabs(Dscalar) < 0.001:
                if Wscalar < 0:
                    return 1
            else:
                t = -Wscalar / Dscalar

                if Dscalar > 0:
                    if t > 1:
                        return 2
                    else:
                        tb = max(tb, t)
                elif Dscalar < 0:
                    if t < 0:
                        return 3
                    else:
                        te = min(te, t)
        if tb <= te:
            self.scene.addLine(x + (line.p2().x() - x) * te,
                                y + (line.p2().y() - y) * te,
                                x + (line.p2().x() - x) * tb,
                                y + (line.p2().y() - y) * tb,
                                QPen(self.cut_line_color))
        else:
            return 4
        return 0







    def clean_screen(self):        
        self.scene.clear()
        self.lines = list()
        self.cur_line = list()
        self.polygon = list()
        self.full_polygon = False
        self.isConvex = False
        self.direction = -1

    def color_in_str(self, color):
        return str("(" + str(color[0]) + "," + str(color[1]) + "," + str(color[2]) + ")")
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()
