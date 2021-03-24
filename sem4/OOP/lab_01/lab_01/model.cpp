#include <stdlib.h>

#include "model.h"
#include "constants.h"
#include "check.h"
#include "draw.h"


modelT &initModel() {
    static modelT model;

    model.pointsData.coords = nullptr;
    model.edgesData.edges = nullptr;

    return model;
}


void freeModel(modelT &model) {
    freeEdges(model.edgesData);
    freePoints(model.pointsData);
}


int loadTempModel(modelT &tempModel, FILE *file) {
    int check = OK;

    if ((check = readPoint(tempModel.center, file))) {
        return check;
    }

    if ((check = loadPoints(tempModel.pointsData, file))) {
        return check;
    }

    if ((check = loadEdges(tempModel.edgesData, file))) {
        freePoints(tempModel.pointsData);
    }

    return check;
}



int loadModel(modelT &model, const char fileName[]) {
    FILE *file = fopen(fileName, "r");

    if (!file) {
        return ERR_OPEN_FILE;
    }

    modelT tempModel = initModel();

    int check = loadTempModel(tempModel, file);
    fclose(file);

    if (check != OK) {
        return check;
    }

    freeModel(model);
    model = tempModel;

    return check;
}


int scaleModel(modelT &model, const scaleT &scale) {
    int check = OK;

    if ((check = checkModelEmpty(model))) {
        return check;
    }

    scalePoints(model.pointsData, scale, model.center);

    return check;
}


int moveModel(modelT &model, const moveT &move) {
    int check = OK;

    if ((check = checkModelEmpty(model))) {
        return check;
    }

    movePoints(model.pointsData, move);

    movePoint(model.center, move);

    return OK;
}


int rotateModel(modelT &model, const rotateT &rotate) {
    int check = OK;

    if ((check = checkModelEmpty(model))) {
        return check;
    }

    rotatePoints(model.pointsData, rotate, model.center);

    return OK;
}


int drawModel(const modelT &model, const canvasT &canvas) {
    int check = OK;

    if ((check = checkModelEmpty(model))) {
        return check;
    }

    if ((check = checkCanvasEmpty(canvas))) {
        return check;
    }

    prepareCanvas(canvas);

    drawEdges(model.edgesData, model.pointsData, canvas);

    return OK;
}
