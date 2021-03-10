#include <stdlib.h>

#include "event_handler.h"
#include "constants.h"
#include "model.h"
#include "file_handler.h"
#include "draw.h"
#include "operations.h"


int eventHandler(const eventT &event) {
    int check = OK;
    static modelT model = initModel();

    if (event.type == LOAD_MODEL) {
        check = readModelFromFile(model, event.file);
    }
    else if (event.type == DRAW_MODEL) {
        drawModel(model, event.scene);
    }
    else if (event.type == MOVE_MODEL) {
        check = moveModel(model, event.move);
    }
    else if (event.type == ROTATE_MODEL) {
        check = rotateModel(model, event.rotate);
    }
    else if (event.type == SCALE_MODEL) {
        check = scaleModel(model, event.scale);
    }
    else if (event.type == FREE_MODEL) {
        freeModel(model);
    }

    return check;
}
