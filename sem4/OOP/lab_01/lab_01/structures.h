#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QGraphicsScene>

typedef struct {
    double kx;
    double ky;
    double kz;
} scaleT;


typedef struct {
    double dx;
    double dy;
    double dz;
} moveT;


typedef struct {
    double angle_x;
    double angle_y;
    double angle_z;
} rotateT;


typedef struct {
    QGraphicsScene *scene;
} canvasT;

#endif // STRUCTURES_H
