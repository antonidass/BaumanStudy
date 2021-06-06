import sys

import ui

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


from structs import *



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
        self.cutOffButton.clicked.connect(self.solution_wrapper)

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



    def eventFilter(self, source, event):
        if event.type() == QEvent.MouseMove and source is self.graphicsView.viewport():
            x = event.x()
            y = event.y()

            self.following_line(x, y)
            self.following_cutter(x, y)

        return QWidget.eventFilter(self, source, event)

    def keyPressEvent(self, event):
        key = event.key()
        if key == Qt.Key_Control:
            self.ctrl_pressed = True

    def keyReleaseEvent(self, event):
        key = event.key()
        if key == Qt.Key_Control:
            self.ctrl_pressed = False

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
            self.line_on_screen(x, y)
            self.cutter_on_screen(x, y)



    def get_line(self):
        try:
            x1 = int(self.X_1.text())
            y1 = int(self.Y_1.text())
            x2 = int(self.X_2.text())
            y2 = int(self.Y_2.text())
        except ValueError:
            QMessageBox.critical(self, "Ошибка", "Введены некорректные данные отрезка!")
            return -1

        self.add_line(x1, y1, x2, y2, self.line_color)

    def get_cutter(self):
        try:
            x_left = int(self.X_left.text())
            y_up = int(self.Y_up.text())
            x_right = int(self.X_right.text())
            y_down = int(self.Y_down.text())
        except ValueError:
            QMessageBox.critical(self, "Ошибка", "Введены некорректные данные отсекателя!")
            return -1

        if x_left == x_right or y_up == y_down:
            QMessageBox.critical(self, "Ошибка", "Введен некорректный отсекатель!")
            return -1

        self.del_cutter()
        self.add_cutter(x_left, y_up, x_right, y_down, self.cutter_color)

    def choose_cutter(self):
        self.del_cutter()
        self.drawing_cutter = True

    def add_line(self, x1, y1, x2, y2, color):
        self.pen.setColor(color)

        line = Line()

        line.x1 = x1
        line.y1 = y1
        line.x2 = x2
        line.y2 = y2
        line.scene_item = self.scene.addLine(x1, y1, x2, y2, self.pen)

        self.lines.append(line)

    def drawPoly(self):
        rect = QRect(self.cutter.x_left, self.cutter.y_down, self.cutter.x_right - self.cutter.x_left, self.cutter.y_up - self.cutter.y_down)
        pix = QPixmap()
        painter = QPainter()

        image = QImage(WIDE, HEIGHT, QImage.Format_RGB32)
        image.fill(Qt.white)
        painter.begin(image)

        pen = QPen(self.line_color)
        pen.setWidth(1)
        painter.setPen(pen)
           
        for line in self.lines:
            painter.drawLine(line.x1, line.y1, line.x2, line.y2)

        painter.fillRect(rect, QBrush(Qt.white))
        pen = QPen(self.cutter_color)
        painter.setPen(pen)
        painter.drawRect(rect)

        painter.end()
        pix.convertFromImage(image)
        self.scene.clear()
        self.scene.addPixmap(pix)
        

    def add_cutter(self, x_l, y_u, x_r, y_d, color):
        self.pen.setColor(color)

        if x_l > x_r:
            x_l, x_r = x_r, x_l
        if y_u > y_d:
            y_u, y_d = y_d, y_u

        cutter = Cutter()

        cutter.x_left = x_l
        cutter.y_up = y_u
        cutter.x_right = x_r
        cutter.y_down = y_d
        cutter.scene_item = self.scene.addRect(x_l, y_u, x_r - x_l, y_d - y_u, self.pen)

        self.cutter = cutter

    def del_cutter(self):
        if self.cutter:
            self.scene.removeItem(self.cutter.scene_item)
        self.cutter = None


    def line_on_screen(self, x, y):
        if not self.drawing_cutter:
            if self.ctrl_pressed == 0 or len(self.cur_line) == 0:
                self.cur_line.append((x, y))

            else:
                prev = self.cur_line[0]

                dx = x - prev[0]
                dy = y - prev[1]

                if abs(dy) >= abs(dx):
                    self.cur_line.append((prev[0], y))
                else:
                    self.cur_line.append((x, prev[1]))

            if len(self.cur_line) == 2:
                c1, c2 = self.cur_line
                self.add_line(c1[0], c1[1], c2[0], c2[1], self.line_color)
                self.cur_line.clear()
                self.scene.removeItem(self.follow_line)


    def cutter_on_screen(self, x, y):
        if self.drawing_cutter:
            if len(self.cur_cutter) < 2:
                self.cur_cutter.append((x, y))

            if len(self.cur_cutter) == 2:
                c1, c2 = self.cur_cutter
                self.add_cutter(c1[0], c1[1], c2[0], c2[1], self.cutter_color)
                self.cur_cutter.clear()
                self.scene.removeItem(self.follow_cutter)
                self.drawing_cutter = False


    def following_line(self, x, y):
        if len(self.cur_line) == 1:
            prev = self.cur_line[0]
            self.pen.setColor(self.line_color)

            if self.follow_line:
                self.scene.removeItem(self.follow_line)

            if self.ctrl_pressed:
                dx = x - prev[0]
                dy = y - prev[1]

                if abs(dy) >= abs(dx):
                    cur = (prev[0], y)
                else:
                    cur = (x, prev[1])

                self.follow_line = self.scene.addLine(prev[0], prev[1], cur[0], cur[1], self.pen)
            else:
                self.follow_line = self.scene.addLine(prev[0], prev[1], x, y, self.pen)


    def following_cutter(self, x, y):
        if len(self.cur_cutter) == 1:
            x_l, y_u = self.cur_cutter[0]
            x_r, y_d = x, y
            self.pen.setColor(self.cutter_color)

            if self.follow_cutter:
                self.scene.removeItem(self.follow_cutter)

            if x_l > x_r:
                x_l, x_r = x_r, x_l
            if y_u > y_d:
                y_u, y_d = y_d, y_u

            self.follow_cutter = self.scene.addRect(x_l, y_u, x_r - x_l, y_d - y_u, self.pen)


    def draw_line(self, dot1, dot2, color):
        self.pen.setColor(color)
        self.scene.addLine(dot1[0], dot1[1], dot2[0], dot2[1], self.pen)



    def multiplication_code(self, code1, code2):  
        result = 0
        for i in range(len(code1)):
            result += code1[i] & code2[i]
        return result


    def sum_code(self, code):
        result_sum = 0
        for c in code:
            result_sum += c
        return result_sum


    def create_code(self, point, rectangle):
        result_list = [0, 0, 0, 0]

        result_list[0] = 1 if point[X] < rectangle.x_left else 0
        result_list[1] = 1 if point[X] > rectangle.x_right else 0
        result_list[2] = 1 if point[Y] > rectangle.y_down else 0
        result_list[3] = 1 if point[Y] < rectangle.y_up else 0

        return result_list


    def is_visible(self, code_1, code_2, rectangle):
        if not self.sum_code(code_1) and not self.sum_code(code_2):
            return VISIBLE_LINE

        if self.multiplication_code(code_1, code_2) != 0:
            return INVISIBLE_LINE

        return PARTLY_VISIBLE_LINE


    def cohen_sutherland(self, line, rectangle):
        flag, m = NORMAL_LINE, 1

        if line.x1 - line.x2 == 0:
            flag = VERTICAL_LINE
        else:
            m = (line.y2 - line.y1) / (line.x2 - line.x1)

            if m == 0:
                flag = HORIZONTAL_LINE

        for i in range(4):
            code_1 = self.create_code([line.x1, line.y1], rectangle)
            code_2 = self.create_code([line.x2, line.y2], rectangle)

            vis = self.is_visible(code_1, code_2, rectangle)

            if vis == VISIBLE_LINE:
                return line
            elif vis == INVISIBLE_LINE: 
                return INVISIBLE_LINE

            if code_1[i] == code_2[i]:
                continue

            if not code_1[i]:
                line.x1, line.y1, line.x2, line.y2 = line.x2, line.y2, line.x1, line.y1

            if flag != VERTICAL_LINE:
                if i < 2:
                    if i == 0:
                        line.y1 = m * (rectangle.x_left - line.x1) + line.y1
                        line.x1 = rectangle.x_left
                    elif i == 1:
                        line.y1 = m * (rectangle.x_right - line.x1) + line.y1
                        line.x1 = rectangle.x_right
                    continue
                else:
                    if i == 2:
                        line.x1 = (1 / m) * (rectangle.y_down - line.y1) + line.x1
                    elif i == 3:
                        line.x1 = (1 / m) * (rectangle.y_up - line.y1) + line.x1
                        
            if i == 2:
                line.y1 = rectangle.y_down
            elif i == 3:    
                line.y1 = rectangle.y_up

        return line


    def find_solution(self):
        result_list = list()

        for i in range(len(self.lines)):
            res = self.cohen_sutherland(self.lines[i], self.cutter)
            if res != INVISIBLE_LINE:
                result_list.append(res)

        return result_list


    def solution_wrapper(self):
        if not self.cutter:
            QMessageBox.critical(self, "Ошибка", "Для начала выберите отсекатель!")
            return

        self.drawPoly()
        result_list = self.find_solution()

        for i in range(len(result_list)):
            self.add_line(result_list[i].x1, result_list[i].y1, result_list[i].x2, result_list[i].y2, self.cut_line_color)

        self.scene.addRect(self.cutter.x_left, self.cutter.y_down, self.cutter.x_right - self.cutter.x_left, self.cutter.y_up - self.cutter.y_down, self.cutter_color)




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




