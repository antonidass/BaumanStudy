#include <stdlib.h>

#include "model.h"
#include "constants.h"


modelT& initModel() {
    static modelT model;

    model.edges = nullptr;
    model.coords = nullptr;

    return model;
}


int allocateModel(modelT &model) {
    model.edges = (edgeT *) malloc(sizeof(edgeT) * model.edges_count);

    if (!model.edges) {
        return ERR_ALLOC_MODEL;
    }

    model.coords = (pointT *) malloc(sizeof(pointT) * model.vertices_count);

    if (!model.coords) {
        return ERR_ALLOC_MODEL;
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

