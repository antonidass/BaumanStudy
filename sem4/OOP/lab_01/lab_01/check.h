#ifndef CHECK_H
#define CHECK_H

#include "point.h"
#include "edge.h"
#include "model.h"


int checkModelEmpty(const modelT &model);

int checkCanvasEmpty(const canvasT &canvas);

void handleError(const int &check, char error[]);

#endif // CHECK_H
