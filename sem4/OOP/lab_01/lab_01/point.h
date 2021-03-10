#ifndef POINT_H
#define POINT_H

#include "structures.h"

typedef struct {
    double x;
    double y;
    double z;
} pointT;


pointT initPoint(const double &x, const double &y, const double &z);

void scalePoint(pointT &point, const scaleT &scale_coeff,  const pointT &center);


void rotatePoint(pointT &point, const rotateT &angle, const pointT &center);

void rotateCoordX(pointT &tempPoint, const pointT &point, const double &angle, const pointT &centerPoint);

void rotateCoordZ(pointT &tempPoint, const pointT &point, const double &angle, const pointT &centerPoint);

void rotateCoordY(pointT &tempPoint, const pointT &point, const double &angle, const pointT &centerPoint);


void movePoint(pointT &point, const moveT &move);


#endif // POINT_H
