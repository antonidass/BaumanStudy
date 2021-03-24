#ifndef DRAW_QT_H
#define DRAW_QT_H

#include "structures.h"
#include "point.h"


void prepareCanvas(const canvasT &canvas);

void drawLine(const pointT &point1, const pointT &point2, const canvasT &canvas);


#endif // DRAW_QT_H
