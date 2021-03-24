#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include "structures.h"
#include "point.h"
#include "edge.h"


typedef struct {
    pointsDataT pointsData;
    edgesDataT edgesData;
    pointT center;
} modelT;


modelT &initModel();

void freeModel(modelT &model);

int loadModel(modelT &model, const char fileName[]);

int scaleModel(modelT &model, const scaleT &scale);

int moveModel(modelT &model, const moveT &move);

int rotateModel(modelT &model, const rotateT &rotate);

int drawModel(const modelT& model, const canvasT &canvas);

#endif // MODEL_H
