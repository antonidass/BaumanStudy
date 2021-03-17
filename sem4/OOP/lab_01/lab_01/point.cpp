#include "math.h"

#include "point.h"
#include "constants.h"
#include "utils.h"


void scalePoint(pointT &point, const scaleT &scale, const pointT &center) {
    point.x = ((point.x - center.x) * scale.kx) + center.x;
    point.y = ((point.y - center.y) * scale.ky) + center.y;
    point.z = ((point.z - center.z) * scale.kz) + center.z;
}


void movePoint(pointT &point, const moveT &move) {
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}


void rotatePoint(pointT &point, const rotateT &rotate, const pointT &center) {
    if (fabs(rotate.angle_x) > EPS) {
        rotatePointX(point, rotate.angle_x, center);
    }
    else if (fabs(rotate.angle_y) > EPS) {
        rotatePointY(point, rotate.angle_y, center);
    }
    else if (fabs(rotate.angle_z) > EPS) {
        rotatePointZ(point, rotate.angle_z, center);
    }
}


void rotatePointX(pointT &point, const double &angle, const pointT &center) {
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempY = point.y;

    point.y = center.y + (point.y - center.y) * cosA - (point.z - center.z) * sinA;
    point.z = center.z + (tempY - center.y) * sinA + (point.z - center.z) * cosA;
}


void rotatePointY(pointT &point, const double &angle, const pointT &center) {
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempX = point.x;

    point.x = center.x + (point.x - center.x) * cosA + (point.z - center.z) * sinA;
    point.z = center.z + (-(tempX - center.x)) * sinA + (point.z - center.z) * cosA;
}


void rotatePointZ(pointT &point, const double &angle, const pointT &center) {
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempX = point.x;

    point.x = center.x + (point.x - center.x) * cosA - (point.y - center.y) * sinA;
    point.y = center.y + (tempX - center.x) * sinA + (point.y - center.y) * cosA;
}
