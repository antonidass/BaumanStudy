#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include "model.h"

int readModelDescription(modelT &model, FILE *file);

int readPoints(modelT &model, FILE *file);

int readEdgeConnections(modelT &model, FILE *file);

int readModelFromFile(modelT &model, FILE *file);

#endif // FILE_HANDLER_H
