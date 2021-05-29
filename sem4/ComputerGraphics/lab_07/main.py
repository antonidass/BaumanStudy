import sys

import ui
# from PyQt5 import QtWidgets, QtCore, QtGui
# from PyQt5.QtWidgets import QGraphicsScene, QTableWidgetItem
# from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter
# from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPoint

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


from funcs import *


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
        self.image = QImage(WIDE, HEIGHT, QImage.Format_RGB32)
        self.image.fill(Qt.white)


        # self.bg_color = QColor(Qt.white)
        # self.line_color = QColor(Qt.black)
        # self.cutter_color = QColor(Qt.red)
        # self.cut_line_color = QColor(Qt.blue)

        self.cutter_color = QColor(100, 200, 100)
        self.line_color = QColor(Qt.black)
        self.cut_line_color = QColor(229, 204, 255)

        self.ctrl_pressed = False
        self.lines = []
        self.cur_line = []
        self.follow_line = None

        self.cutter = None
        self.drawing_cutter = False
        self.cur_cutter = []
        self.follow_cutter = None


        self.cutOff_colorButton.clicked.connect(self.get_cutter_color)    
        self.result_colorButton.clicked.connect(self.get_result_color)    
        self.segment_olorButton.clicked.connect(self.get_line_color)    

        self.clearScreenButton.clicked.connect(self.clean_screen)
        self.addSegmentButton.clicked.connect(self.get_line)
        self.addCutOffButton.clicked.connect(self.get_cutter)
        self.chooseCutOffButton.clicked.connect(self.choose_cutter)
        self.cutOffButton.clicked.connect(self.cut)

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



    # Отслеживание передвижения мыши
    def eventFilter(self, source, event):
        if event.type() == QEvent.MouseMove and source is self.graphicsView.viewport():
            x = event.x()
            y = event.y()

            following_line(self, x, y)
            following_cutter(self, x, y)

        return QWidget.eventFilter(self, source, event)

    # Нажатие клавиши
    def keyPressEvent(self, event):
        key = event.key()
        if key == Qt.Key_Control:
            self.ctrl_pressed = True

    # Отжатие клавиши
    def keyReleaseEvent(self, event):
        key = event.key()
        if key == Qt.Key_Control:
            self.ctrl_pressed = False

    # Нажатие кнопки мыши
    def mousePressEvent(self, event):
        but = event.button()
        x = event.x()
        y = event.y()
        borders = self.graphicsView.geometry().getCoords()
        if borders[0] <= x < borders[2] and borders[1] <= y < borders[3]:
            x -= borders[0]
            y -= borders[1]
        else:
            return

        if but == 1:
            line_on_screen(self, x, y)
            cutter_on_screen(self, x, y)




    def get_line(self):
        try:
            x1 = int(self.X_1.text())
            y1 = int(self.Y_1.text())
            x2 = int(self.X_2.text())
            y2 = int(self.Y_2.text())
        except ValueError:
            mes("Неверные данные отрезка")
            return -1

        add_line(self, x1, y1, x2, y2, self.line_color)


    def get_cutter(self):
        try:
            x_left = int(self.X_left.text())
            y_up = int(self.Y_up.text())
            x_right = int(self.X_right.text())
            y_down = int(self.Y_down.text())
        except ValueError:
            mes("Неверные данные отрезка")
            return -1

        del_cutter(self)
        add_cutter(self, x_left, y_up, x_right, y_down, self.cutter_color)


    def choose_cutter(self):
        del_cutter(self)
        self.drawing_cutter = True






































    def cut(self):    # Возвращает концы видимого отрезка.
        # Если отрезок невидим, то возвращает INVISIBLE_LINE
        """
        flag - Положение отрезка:
        1 = общего положения
        0 = горизонтальный
        -1 = вертикальный
        """
        # Изначально считаем, что отрезок общего положения.
        flag, m = NORMAL_LINE, 1
        # Проверка на то, что отрезок вертикальный.
        if line[X1] - line[X2] == 0:
            flag = VERTICAL_LINE
        else:
            # Если отрезок не вертикальный, то вычисляем тангенс.
            m = (line[Y2] - line[Y1]) / (line[X2] - line[X1])
            # Проверка на то, что отрезок горизонтальный.
            if m == 0:
                flag = HORIZONTAL_LINE

        # Итерируемся по 4 сторонам отсекателя
        # В порядке: (x_левое, x_правое, y_нижнее, y_верхнее)
        for i in range(4):
            # Формируем четырехразрядный код начала отрезка.
            code_1 = create_code([line[X1], line[Y1]], rectangle)
            # Формируем четырехразрядный код конца отрезка.
            code_2 = create_code([line[X2], line[Y2]], rectangle)
            # Определяем видимость отрезка.
            vis = is_visible(code_1, code_2, rectangle)
            # Если отрезок видимый, возвращаем его координаты (начало и конец).
            if vis == VISIBLE_LINE:
                return line
            # Если отрезок невидимый возвращаем признак невидимости.
            elif vis == INVISIBLE_LINE:
                return INVISIBLE_LINE

            # Проверяем пересечение отрезка и стороны отсекателя.
            # До этого момента не дойдет отрезок, у которого две
            # координаты по одну сторону, потому что выше мы это обработали.
            # Т.е. в данном случае может могут быть только
            # Такие значения code_1[i] и code_2[i]: 0 и 1, 1 и 0, 0 и 0
            # 1 и 0, 0 и 1 - означает, что данный отрезок пересекает
            # Данную сторону отсекателя (Т.е. одна его сторона находится
            # По невидимую сторону, а вторая по видимую => есть
            # Пересечение с данной стороной) - это то, что нам нужно.
            # 0 и 0 - означает обратное => отрезок ее не пересекает.
            if code_1[i] == code_2[i]:
                continue

            # Т.к. мы собираемся искать пересечение
            # Прямой и стороны отсекателя мы должны будем после
            # Того, как найдем данное пересечение
            # Присвоить одной вершине отрезка найденное пересечение.
            # Чтобы корректной вершине присвоить пересечение
            # Мы должны проверить, что данная вершина находится по
            # Невидимую сторону стороны отсекателя. Если это не так
            # То поменять местами. Если данную проверку не произвести (И обмен),
            # То получится, что после того, как мы найдем пересечение
            # Мы можем присвоить вершине, которая и так является видимой, а та
            # Вершина, которая находилась вне отсекателя так там и останется.
            # Т.е. вместо того, чтобы отбросить невидимую часть отрезка
            # Мы можем (Если не произведем данный обмен) отбросить видимую часть.
            if not code_1[i]:
                line[X1], line[Y1], line[X2], line[Y2] = line[X2], line[Y2], line[X1], line[Y1]

            # Если не вертикальная линия.
            if flag != VERTICAL_LINE:
                # Т.к. rectangle представлен данном виде:
                # (x_левое, x_правое, y_нижнее, y_верхнее)
                # Это значит, что при i<2 мы ищем пересечение
                # Либо с x_левой либо с x_правой.
                if i < 2:
                    # Находим пересечение.
                    line[Y1] = m * (rectangle[i] - line[X1]) + line[Y1]
                    # Мы точно знаем, что раз есть пересечение,
                    # То координата x будет соответствовать x_левому или x_правому
                    # В зависимости от того, с какой стороной
                    # Мы на данный момент работаем.
                    line[X1] = rectangle[i]
                    continue
                else:
                    line[X1] = (1 / m) * (rectangle[i] - line[Y1]) + line[X1]
            line[Y1] = rectangle[i]

        return line



    def create_code(self, point, rectangle):
        result_list = [0, 0, 0, 0]
        # print("point, rectangle = ", point, rectangle)

        result_list[0] = 1 if point[X] < rectangle[LEFT] else 0
        result_list[1] = 1 if point[X] > rectangle[RIGHT] else 0
        # Чуть иначе для Y (Не так, как в конспекте, потому что у нас ось Y направлена вниз).
        result_list[2] = 1 if point[Y] > rectangle[DOWN] else 0
        result_list[3] = 1 if point[Y] < rectangle[UP] else 0

        # print("result_list = ", result_list, "sum_code = ", sum_code(result_list))
        return result_list






    def multiplication_code(self, code1, code2):  # scalar_product
        result = 0
        for i in range(len(code1)):
            result += code1[i] * code2[i]
        return result


    def sum_code(self, code):
        result_sum = 0
        for c in code:
            result_sum += c
        return result_sum


    def create_code(self, point, rectangle):
        result_list = [0, 0, 0, 0]
        # print("point, rectangle = ", point, rectangle)

        result_list[0] = 1 if point[X] < rectangle[LEFT] else 0
        result_list[1] = 1 if point[X] > rectangle[RIGHT] else 0
        # Чуть иначе для Y (Не так, как в конспекте, потому что у нас ось Y направлена вниз).
        result_list[2] = 1 if point[Y] > rectangle[DOWN] else 0
        result_list[3] = 1 if point[Y] < rectangle[UP] else 0

        # print("result_list = ", result_list, "sum_code = ", sum_code(result_list))
        return result_list



    def is_visible(self, code_1, code_2, rectangle):
        """Видимость:
                1 = видимый
                0 = частично видимый
                -1 = невидимый"""
        # code_1 = create_code([start[X], start[Y]], rectangle)
        # code_2 = create_code([end[X], end[Y]], rectangle)

        if not self.sum_code(code_1) and not self.sum_code(code_2):
            return VISIBLE_LINE

        if self.multiplication_code(code_1, code_2) != 0:
            return INVISIBLE_LINE

        return PARTLY_VISIBLE_LINE




    def clean_screen(self):        
        self.scene.clear()

        self.lines.clear()
        self.cur_line.clear()
        self.follow_line = None

        self.cutter = None
        self.cur_cutter.clear()
        self.follow_cutter = None
        self.drawing_cutter = False


    def color_in_str(self, color):
        return str("(" + str(color[0]) + "," + str(color[1]) + "," + str(color[2]) + ")")
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = GUI()
    win.show()
    app.exec_()







