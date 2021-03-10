#include "math.h"

#include "operations.h"
#include "constants.h"


int scaleModel(modelT &model, const scaleT &scale) {
    if (!model.coords || !model.edges) {
        return ERR_EMPTY_MODEL;
    }

    if (fabs(scale.kx) < EPS || fabs(scale.ky) < EPS || fabs(scale.kz) < EPS) {
        return ERR_SCALE_COEFF;
    }

    for (int i = 0; i < model.vertices_count; i++) {
        scalePoint(*(model.coords + i), scale, model.center);
    }

    return OK;
}


int moveModel(modelT &model, const moveT &move) {
    if (!model.coords || !model.edges) {
        return ERR_EMPTY_MODEL;
    }

    for (int i = 0; i < model.vertices_count; i++) {
        movePoint(*(model.coords + i), move);
    }

    movePoint(model.center, move);

    return OK;
}


int rotateModel(modelT &model, const rotateT &rotate) {
    if (!model.coords || !model.edges) {
        return ERR_EMPTY_MODEL;
    }

    for (int i = 0; i < model.vertices_count; i++) {
        rotatePoint(*(model.coords + i), rotate, model.center);
    }

    return OK;
}
