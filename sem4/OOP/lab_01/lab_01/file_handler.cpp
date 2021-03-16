#include <stdlib.h>

#include "file_handler.h"
#include "constants.h"


int readModelDescription(modelT &model, FILE *file) {
    int rc = fscanf(file, "%d%d", &model.vertices_count, &model.edges_count);

    if (rc != 2) {
        return ERR_FILE_READ_INT;
    }

    return OK;
}


int readModelCenter(modelT &model, FILE *file) {
   int rc = fscanf(file, "%lf%lf%lf", &model.center.x, &model.center.y, &model.center.z);

   if (rc != 3) {
       return ERR_FILE_READ_POINT;
   }

   return OK;
}


int readPoints(modelT &model, FILE *file) {
    int rc;

    for (int i = 0; i < model.vertices_count; i++) {
        rc = fscanf(file, "%lf%lf%lf", &((model.coords + i)->x), &((model.coords + i)->y), &((model.coords + i)->z) );

        if (rc != 3) {
            return ERR_FILE_READ_POINT;
        }
    }

    return OK;
}


int readEdgeConnections(modelT &model, FILE *file) {
    int rc;

    for (int i = 0; i < model.edges_count; i++) {
        rc = fscanf(file, "%d%d", &(model.edges + i)->left_vertex, &(model.edges + i)->right_vertex);

        if (rc != 2) {
            return ERR_FILE_READ_EDGE_CONNECTION;
        }
    }

    return OK;
}


int readModelFromFile(modelT &model, FILE *file) {
    int check = readModelDescription(model, file);

    if (check != OK) {
        return check;
    }

    check = readModelCenter(model, file);

    if (check != OK) {
        return check;
    }

    freeModel(model);
    check = allocateModel(model);

    if (check != OK) {
        return check;
    }

    check = readPoints(model, file);

    if (check != OK) {
        return check;
    }

    check = readEdgeConnections(model, file);

    if (check != OK) {
        return check;
    }

    return check;
}
