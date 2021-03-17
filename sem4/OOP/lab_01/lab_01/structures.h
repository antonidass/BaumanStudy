#ifndef STRUCTURES_H
#define STRUCTURES_H

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

#endif // STRUCTURES_H
