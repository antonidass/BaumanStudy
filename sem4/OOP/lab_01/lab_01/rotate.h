#ifndef ROTATE_H
#define ROTATE_H

#include "model.h"
#include "point.h"

int rotateModel(modelT &model, const pointT &point);

void turnPoint(pointT &point, const pointT &angle);

void modelCenterUpdate(modelT &model);

#endif // ROTATE_H
