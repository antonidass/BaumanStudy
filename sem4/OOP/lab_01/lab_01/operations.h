#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "model.h"
#include "point.h"
#include "structures.h"

int scaleModel(modelT &model, const scaleT &scale);

int moveModel(modelT &model, const moveT &move);

int rotateModel(modelT &model, const rotateT &rotate);

#endif // OPERATIONS_H
