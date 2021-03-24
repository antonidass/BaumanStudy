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


void subtractCenter(pointT &point, const pointT &center) {
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;
}


void addCenter(pointT &point, const pointT &center) {
    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}


void rotatePoint(pointT &point, const rotateT &rotate, const pointT &center) {
    subtractCenter(point, center);

    if (fabs(rotate.angle_x) > EPS) {
        rotatePointX(point, rotate.angle_x);
    }
    else if (fabs(rotate.angle_y) > EPS) {
        rotatePointY(point, rotate.angle_y);
    }
    else if (fabs(rotate.angle_z) > EPS) {
        rotatePointZ(point, rotate.angle_z);
    }

    addCenter(point, center);
}


void rotatePointX(pointT &point, const double &angle) {
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempY = point.y;

    point.y = point.y * cosA - point.z * sinA;
    point.z = tempY * sinA + point.z * cosA;
}


void rotatePointY(pointT &point, const double &angle) {
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempX = point.x;

    point.x = point.x * cosA + point.z * sinA;
    point.z = -tempX * sinA + point.z * cosA;
}


void rotatePointZ(pointT &point, const double &angle) {
    double cosA = getCosAngle(angle);
    double sinA = getSinAngle(angle);
    double tempX = point.x;

    point.x = point.x * cosA - point.y * sinA;
    point.y = tempX * sinA + point.y * cosA;
}


void movePoints(pointsDataT &pointsData, const moveT &move) {
    for (int i = 0; i < pointsData.vertices_count; i++) {
        movePoint(pointsData.coords[i], move);
    }
}


void rotatePoints(pointsDataT &pointsData, const rotateT &rotate, const pointT &center) {
    for (int i = 0; i < pointsData.vertices_count; i++) {
        rotatePoint(pointsData.coords[i], rotate, center);
    }
}


void scalePoints(pointsDataT &pointsData, const scaleT &scale, const pointT &center) {
    for (int i = 0; i < pointsData.vertices_count; i++) {
        scalePoint(pointsData.coords[i], scale, center);
    }
}


int readAmount(pointsDataT &pointsData, FILE *file) {
    if (fscanf(file, "%d", &pointsData.vertices_count) != 1) {
        return ERR_FILE_READ_VERTICES_COUNT;
    }

    return OK;
}


int readPoint(pointT &point, FILE *file) {
    if (fscanf(file, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3) {
        return ERR_FILE_READ_POINT;
    }

    return OK;
}


int readPoints(pointsDataT &pointsData, FILE *file) {
    int check = OK;

    for (int i = 0; i < pointsData.vertices_count && !check; i++) {
       check = readPoint(pointsData.coords[i], file);
    }

    return check;
}


int loadPoints(pointsDataT &pointsData, FILE *file) {
    int check = OK;

    if ((check = readAmount(pointsData, file))) {
        return check;
    }

    if ((check = allocatePoints(pointsData))) {
        return check;
    }

    if ((check = readPoints(pointsData, file))) {
        freePoints(pointsData);
    }

    return check;
}


void freePoints(pointsDataT &pointsData) {
    if (pointsData.coords != nullptr) {
        delete[] pointsData.coords;
    }
}


int allocatePoints(pointsDataT &pointsData) {
    pointsData.coords = new pointT[pointsData.vertices_count];

    if (pointsData.coords == nullptr) {
        return ERR_ALLOC_COORDS;
    }

    return OK;
}
