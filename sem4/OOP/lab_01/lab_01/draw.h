#ifndef DRAW_H
#define DRAW_H

#include "model.h"
#include "mainwindow.h"


int drawModel(const modelT& model, QGraphicsScene *scene);

void drawEdge(const edgeT &edge, const pointT *const coords , QGraphicsScene *const scene);

#endif // DRAW_H
