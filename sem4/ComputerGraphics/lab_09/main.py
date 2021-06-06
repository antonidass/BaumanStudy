import sys

import ui
from math import *

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

import sys

import copy


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

        self.cutter = list()
        self.lines = list()
        self.polygons = list()

        self.full_polygon = False
        self.isConvex = False
        self.direction = -1

        self.ctrl_pressed = False

        self.cutOff_colorButton.clicked.connect(self.get_cutter_color)
        self.result_colorButton.clicked.connect(self.get_result_color)
        self.segment_olorButton.clicked.connect(self.get_line_color)

        self.cutterRadio.toggled.connect(self.onClickCutter)
        self.segmentRadio.toggled.connect(self.onClickSegment)

        self.clearScreenButton.clicked.connect(self.clean_screen)
        self.addSegmentButton.clicked.connect(self.get_line)
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
                QMessageBox.critical(
                    self, "Ошибка", "Цвет отсекателя и цвет отрезков совпадают!")
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
                QMessageBox.critical(
                    self, "Ошибка", "Цвет результата и цвет отрезка совпадают. ")
                return

            self.cut_line_color = color
            self.result_colorButton.setStyleSheet("background-color:rgb"
                                                  + self.color_in_str(self.cut_line_color.getRgb()))

    def onClickSegment(self):
        self.label_4.setText("Ввод точки многоугольника")
        self.addSegmentButton.setText("Добавить точку многоугольника")
        self.delCutterButton.setEnabled(False)

    def onClickCutter(self):
        self.label_4.setText("Ввод точки отсекателя")
        self.addSegmentButton.setText("Добавить точку отсекателя")
        self.delCutterButton.setEnabled(True)

    def get_line(self):
        try:
            x = int(self.X_box.text())
            y = int(self.Y_box.text())
        except ValueError:
            QMessageBox.critical(
                self, "Ошибка", "Введены некорректные данные!")
            return -1

        if x < 0 or y < 0 or x > WIDE or y > HEIGHT:
            QMessageBox.critical(
                self, "Ошибка", "Введенная точка находится за пределами экрана!")
            return -1

        if self.segmentRadio.isChecked():
            self.add_line_event(QPointF(x, y))
        else:
            self.add_cutter(QPointF(x, y))

    def mousePressEvent(self, event):
        if event.buttons() == Qt.LeftButton and self.cutterRadio.isChecked():
            x = event.x() - UI_WIDE
            y = event.y() - UI_HEIGHT
            if (x < 0 or y < 0 or x > WIDE or y > HEIGHT):
                return

            if self.ctrl_pressed and len(self.cutter) > 0:
                dx = x - self.cutter[-1].x()
                dy = y - self.cutter[-1].y()

                if abs(dy) >= abs(dx):
                    cur = QPoint(self.cutter[-1].x(), y)
                else:
                    cur = QPoint(x, self.cutter[-1].y())
                self.add_cutter_event(cur)
            else:
                self.add_cutter_event(QPoint(x, y))

        elif event.buttons() == Qt.LeftButton and self.segmentRadio.isChecked():
            x = event.x() - UI_WIDE
            y = event.y() - UI_HEIGHT
            if (x < 0 or y < 0 or x > WIDE or y > HEIGHT):
                return

            if self.ctrl_pressed and len(self.lines) > 0:
                dx = x - self.lines[-1].x()
                dy = y - self.lines[-1].y()

                if abs(dy) >= abs(dx):
                    cur = QPointF(self.lines[-1].x(), y)
                else:
                    cur = QPointF(x, self.lines[-1].y())
                self.add_line_event(cur)
            else:
                self.add_line_event(QPoint(x, y))

        elif event.buttons() == Qt.RightButton and self.cutterRadio.isChecked():
            self.close_cutter()
        elif event.buttons() == Qt.RightButton and self.segmentRadio.isChecked():
            self.close_polygon()

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

        for i in range(len(self.cutter)):
            pol.append(self.cutter[i])

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

        for pol in self.polygons:
            for i in range(-1, len(pol) - 1):
                painter.drawLine(QLineF(pol[i], pol[i + 1]))

        painter.fillPath(polygon_path, QBrush(Qt.white))
        pen = QPen(self.cutter_color)
        painter.setPen(pen)

        painter.end()
        pix.convertFromImage(image)
        self.scene.clear()
        self.scene.addPixmap(pix)

    def change_position(self, point):
        self.curPointLabel.setText(
            "x: " + str(round(point.x())) + " y: " + str(round(point.y())))

    def add_line_event(self, point):
        if point in self.lines:
            QMessageBox().warning(self, "Ошибка", "Данная точка уже была введена ранее!")
            return

        self.lines.append(point)

        if len(self.lines) >= 2:
            self.add_line(QLineF(self.lines[-2], self.lines[-1]))

    def add_line(self, line):
        self.scene.addLine(line, self.pen)

    def add_cutter_event(self, point):
        self.add_cutter(point)

    def add_cutter(self, point):
        if self.full_polygon:
            QMessageBox.warning(self, "Ошибка", "Отсекатель уже введен")
            return

        self.cutter.append(point)
        size = len(self.cutter)

        if size > 1:
            self.scene.addLine(
                QLineF(self.cutter[size - 2], self.cutter[size - 1]), QPen(self.cutter_color))

    def del_cutter(self):
        if self.cutterRadio.isChecked():
            self.cutter = list()
            self.full_polygon = False
            self.scene.clear()
            self.draw_all_lines()

    def draw_all_lines(self):
        for pol in self.polygons:
            for i in range(-1, len(pol) - 1):
                self.scene.addLine(
                    QLineF(pol[i], pol[i + 1]), QPen(self.line_color))

    def close_cutter(self):
        if self.cutterRadio.isChecked():
            size = len(self.cutter)
            if size > 2:
                self.add_cutter(self.cutter[0])
                self.full_polygon = True
                isConvex, _sign = self.is_convex(self.cutter)

                if isConvex:
                    self.isConvex = True
                    self.direction = _sign
                else:
                    self.isConvex = False
                    QMessageBox().warning(self, "Ошибка", "Отсекатель невыпуклый")
        else:
            self.close_polygon()

    def close_polygon(self):
        size = len(self.lines)

        if (size > 2):
            self.scene.addLine(
                QLineF(self.lines[-1], self.lines[0]), QPen(self.line_color))
            self.polygons.append(self.lines)
            self.lines = list()

    def clean_screen(self):
        self.scene.clear()
        self.lines = list()
        self.polygons = list()
        self.cutter = list()
        self.full_polygon = False
        self.isConvex = False
        self.direction = -1

    def color_in_str(self, color):
        return str("(" + str(color[0]) + "," + str(color[1]) + "," + str(color[2]) + ")")




























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
                ab = QPointF(polygon[i].x() - polygon[i - 1].x(),



                             polygon[i].y() - polygon[i - 1].y())
                bc = QPointF(polygon[i + 1].x() - polygon[i].x(),



                             polygon[i + 1].y() - polygon[i].y())
            else:
                ab = QPointF(polygon[i].x() - polygon[i - 1].x(),



                             polygon[i].y() - polygon[i - 1].y())
                bc = QPointF(polygon[1].x() - polygon[0].x(),



                             polygon[1].y() - polygon[0].y())

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

    def cut_all(self):
        if not self.isConvex:
            QMessageBox().warning(self, "Ошибка", "Отсекатель невыпуклый")
            return

        self.drawPoly()

        if self.full_polygon:
            for pol in self.polygons:
                new_pol = self.sazerland_hod(pol, self.cutter)
                for i in range(len(new_pol) - 1):
                    self.scene.addLine(
                        QLineF(new_pol[i], new_pol[i+1]), QPen(self.cut_line_color))

        for i in range(len(self.cutter) - 1):
            self.scene.addLine(
                QLineF(self.cutter[i], self.cutter[i + 1]), QPen(self.cutter_color))

    def visible(self, p0, p1, p2):
        Pab1 = (p0.x() - p1.x()) * (p2.y() - p1.y())
        Pab2 = (p0.y() - p1.y()) * (p2.x() - p1.x())

        return self.sign(Pab1 - Pab2)

    def fact_sech(self, p0, pk, w1, w2):
        vis_1 = self.visible(p0, w1, w2)
        vis_2 = self.visible(pk, w1, w2)

        if (vis_1 < 0 and vis_2 > 0) or (vis_1 > 0 and vis_2 < 0):
            return True

        return False

    def intersection(self, p1, p2, w1, w2):
        d_1 = (p2.x() - p1.x()) * (w1.y() - w2.y()) - \
            (w1.x() - w2.x()) * (p2.y() - p1.y())
        d_2 = (w1.x() - p1.x()) * (w1.y() - w2.y()) - \
            (w1.x() - w2.x()) * (w1.y() - p1.y())
        t = d_2 / d_1

        return QPointF(p1.x() + (p2.x() - p1.x()) * t,
                       p1.y() + (p2.y() - p1.y()) * t)

    def sazerland_hod(self, polygon_0, cutter):
        polygon = polygon_0.copy()
        Np = len(polygon)
        Nw = len(cutter)

        S = QPointF()
        F = QPointF()
        for i in range(Nw - 1):
            Nq = 0
            Q = list()

            for j in range(Np):
                if j != 0:
                    if self.fact_sech(S, polygon[j], cutter[i], cutter[i + 1]):
                        I = self.intersection(
                            S, polygon[j], cutter[i], cutter[i + 1])
                        Q.append(I)
                        Nq += 1
                else:
                    F = polygon[j]

                S = polygon[j]
                is_visible = self.visible(S, cutter[i], cutter[i + 1])

                if (is_visible >= 0 and self.direction == -1) or (is_visible <= 0 and self.direction == 1):
                    Q.append(S)
                    Nq += 1
            if Nq != 0:
                if self.fact_sech(S, F, cutter[i], cutter[i + 1]):
                    I = self.intersection(S, F, cutter[i], cutter[i + 1])
                    Q.append(I)
                    Nq += 1

            Np = Nq
            polygon = Q.copy()

        if len(polygon) > 0:
            polygon.append(polygon[0])
        return polygon


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()
