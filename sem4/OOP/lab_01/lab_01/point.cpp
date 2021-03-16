#include "math.h"

#include "point.h"
#include "constants.h"


pointT initPoint(const double &x, const double &y, const double &z) {
    pointT point;
    point.x = x;
    point.y = y;
    point.z = z;

    return point;
}


void scalePoint(pointT &point, const scaleT &scale, const pointT &center) {
    point.x = ((point.x - center.x) * scale.kx) + center.x;
    point.y = ((point.y - center.y) * scale.ky) + center.y;
    point.z = ((point.z - center.z) * scale.kz) + center.z;
}


void rotatePoint(pointT &point, const rotateT &rotate, const pointT &center) {
    pointT tempPoint = initPoint(0.0, 0.0, 0.0);

    if (fabs(rotate.angle_x) > EPS) {
        rotateCoordX(tempPoint, point, rotate.angle_x, center);
    }

    else if (fabs(rotate.angle_y) > EPS) {
        rotateCoordY(tempPoint, point, rotate.angle_y, center);
    }

    else if (fabs(rotate.angle_z) > EPS) {
        rotateCoordZ(tempPoint, point, rotate.angle_z, center);
    }
    else {
        return;
    }

    point = tempPoint;
}


double getCosRadians(const double &angle) {
    return cos(angle * PI / 180);
}


double getSinRadians(const double &angle) {
    return sin(angle * PI / 180);
}


void rotateCoordX(pointT &tempPoint, const pointT &point, const double &angle, const pointT &center) {
    double cosRad = getCosRadians(angle);
    double sinRad = getSinRadians(angle);

    tempPoint.x = point.x;
    tempPoint.y = center.y + (point.y - center.y) * cosRad - (point.z - center.z) * sinRad;
    tempPoint.z = center.z + (point.y - center.y) * sinRad + (point.z - center.z) * cosRad;
}


void rotateCoordY(pointT &tempPoint, const pointT &point, const double &angle, const pointT &center) {
    double cosRad = getCosRadians(angle);
    double sinRad = getSinRadians(angle);

    tempPoint.y = point.y;
    tempPoint.x = center.x + (point.x - center.x) * cosRad + (point.z - center.z) * sinRad;
    tempPoint.z = center.z + (-(point.x - center.x)) * sinRad + (point.z - center.z) * cosRad;
}


void rotateCoordZ(pointT &tempPoint, const pointT &point, const double &angle, const pointT &center) {
    double cosRad = getCosRadians(angle);
    double sinRad = getSinRadians(angle);

    tempPoint.z = point.z;
    tempPoint.x = center.x + (point.x - center.x) * cosRad - (point.y - center.y) * sinRad;
    tempPoint.y = center.y + (point.x - center.x) * sinRad + (point.y - center.y) * cosRad;
}


void movePoint(pointT &point, const moveT &move) {
    point.x += move.dx;
    point.y += move.dy;
    point.z += move.dz;
}
