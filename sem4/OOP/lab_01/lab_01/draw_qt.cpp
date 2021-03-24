#include "draw_qt.h"


void prepareCanvas(const canvasT &canvas) {
    canvas.scene->clear();
}


void drawLine(const pointT &point1, const pointT &point2, const canvasT &canvas) {
    canvas.scene->addLine(point1.x, point1.y, point2.x, point2.y);
}
