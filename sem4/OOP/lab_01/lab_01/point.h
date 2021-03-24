#ifndef POINT_H
#define POINT_H

#include "structures.h"


typedef struct {
    double x;
    double y;
    double z;
} pointT;


typedef struct {
    pointT *coords;
    int vertices_count;
} pointsDataT;


void scalePoint(pointT &point, const scaleT &scale_coeff,  const pointT &center);

void scalePoints(pointsDataT &pointsData, const scaleT &scale, const pointT &center);

void rotatePoint(pointT &point, const rotateT &angle, const pointT &center);

void subtractCenter(pointT &point, const pointT &center);

void addCenter(pointT &point, const pointT &center);

void rotatePointX(pointT &point, const double &angle);

void rotatePointZ(pointT &point, const double &angle);

void rotatePointY(pointT &point, const double &angle);

void movePoint(pointT &point, const moveT &move);

void movePoints(pointsDataT &pointsData, const moveT &move);

void rotatePoints(pointsDataT &pointsData, const rotateT &rotate, const pointT &center);

void freePoints(pointsDataT &pointsData);

int allocatePoints(pointsDataT &pointsData);

int loadPoints(pointsDataT &pointsData, FILE *file);

int readPoint(pointT &point, FILE *file);


#endif // POINT_H
