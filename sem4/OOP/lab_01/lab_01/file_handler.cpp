#include <stdlib.h>

#include "file_handler.h"
#include "constants.h"


int readModelDescription(int &verticesCount, int &edgesCount, FILE *file) {
    int rc = fscanf(file, "%d%d", &verticesCount, &edgesCount);

    if (rc != 2) {
        return ERR_FILE_READ_INT;
    }

    return OK;
}


int readModelCenter(pointT &centerPoint, FILE *file) {
   int rc = fscanf(file, "%lf%lf%lf", &centerPoint.x, &centerPoint.y, &centerPoint.z);

   if (rc != 3) {
       return ERR_FILE_READ_POINT;
   }

   return OK;
}


int readModelCoords(pointT *const coords, const int &n, FILE *file) {
    int rc;

    for (int i = 0; i < n; i++) {
        rc = fscanf(file, "%lf%lf%lf", &((coords + i)->x), &((coords + i)->y), &((coords + i)->z));

        if (rc != 3) {
            return ERR_FILE_READ_POINT;
        }
    }

    return OK;
}


int readModelEdgeConnections(edgeT *const edges, const int &n, FILE *file) {
    int rc;

    for (int i = 0; i < n; i++) {
        rc = fscanf(file, "%d%d", &(edges + i)->left_vertex, &(edges + i)->right_vertex);

        if (rc != 2) {
            return ERR_FILE_READ_EDGE_CONNECTION;
        }
    }

    return OK;
}


int readModelFromFile(modelT &model, FILE *file) {
    int check = readModelDescription(model.vertices_count, model.edges_count, file);

    if (check != OK) {
        return check;
    }

    check = readModelCenter(model.center, file);

    if (check != OK) {
        return check;
    }

    check = allocateModel(model);

    if (check != OK) {
        return check;
    }

    check = readModelCoords(model.coords, model.vertices_count, file);

    if (check != OK) {
        return check;
    }

    check = readModelEdgeConnections(model.edges, model.edges_count, file);

    if (check != OK) {
        return check;
    }

    return check;
}
