#ifndef POINT_H
#define POINT_H

#include "structures.h"

typedef struct {
    double x;
    double y;
    double z;
} pointT;

void scalePoint(pointT &point, const scaleT &scale_coeff,  const pointT &center);

void rotatePoint(pointT &point, const rotateT &angle, const pointT &center);

void rotatePointX(pointT &point, const double &angle, const pointT &centerPoint);

void rotatePointZ(pointT &point, const double &angle, const pointT &centerPoint);

void rotatePointY(pointT &point, const double &angle, const pointT &centerPoint);

void movePoint(pointT &point, const moveT &move);


#endif // POINT_H
