#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "mainwindow.h"
#include "structures.h"

typedef struct {
    int type;
    union {
        FILE *file;
        QGraphicsScene *scene;
        scaleT scale;
        rotateT rotate;
        moveT move;
    };
} eventT;

int eventHandler(const eventT &event);


#endif // EVENT_HANDLER_H
