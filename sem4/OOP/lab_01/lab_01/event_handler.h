#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <QGraphicsScene>
#include "structures.h"
#include "constants.h"

typedef struct {
    int type;
    union {
        char fileName[FILE_NAME_LEN];
        QGraphicsScene *scene;
        scaleT scale;
        rotateT rotate;
        moveT move;
    };
} eventT;

int eventHandler(const eventT &event);


#endif // EVENT_HANDLER_H
