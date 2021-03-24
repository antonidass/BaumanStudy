#ifndef DRAW_H
#define DRAW_H

#include "draw_qt.h"
#include "model.h"
#include "mainwindow.h"

void drawLine(const pointT &point1, const pointT &point2, const canvasT &canvas);

void drawEdges(const edgesDataT &edgesData, const pointsDataT &pointsData, const canvasT &canvas);


#endif // DRAW_H
