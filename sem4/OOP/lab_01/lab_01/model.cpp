#include <stdlib.h>

#include "model.h"
#include "constants.h"
#include "file_handler.h"


modelT &initModel() {
    static modelT model;

    model.edges = nullptr;
    model.coords = nullptr;

    return model;
}


int allocateModel(modelT &model) {
    model.edges = (edgeT *) malloc(sizeof(edgeT) * model.edges_count);

    if (!model.edges) {
        return ERR_ALLOC_EDGES;
    }

    model.coords = (pointT *) malloc(sizeof(pointT) * model.vertices_count);

    if (!model.coords) {
        return ERR_ALLOC_COORDS;
    }

    return OK;
}


void freeModel(modelT &model) {
    if (model.edges) {
        free(model.edges);
    }

    if (model.coords) {
        free(model.coords);
    }
}


int loadModel(modelT &model, const char fileName[]) {
    FILE *file = fopen(fileName, "r");

    if (!file) {
        return ERR_OPEN_FILE;
    }

    modelT tempModel = initModel();

    int check = readModelFromFile(tempModel, file);
    fclose(file);

    if (check != OK) {
        freeModel(tempModel);
        return check;
    }

    freeModel(model);
    model = tempModel;

    return check;
}

