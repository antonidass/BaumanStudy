#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include "structures.h"
#include "point.h"


typedef struct {
    int left_vertex;
    int right_vertex;
} edgeT;


typedef struct {
    pointT *coords;
    edgeT *edges;
    int vertices_count;
    int edges_count;
    pointT center;
} modelT;


modelT& initModel();

void destroyModel(modelT &model);

int allocateModel(modelT &model);

void freeModel(modelT &model);

#endif // MODEL_H
