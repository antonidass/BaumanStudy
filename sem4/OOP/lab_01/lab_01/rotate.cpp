#include "rotate.h"

#include "constants.h"
#include "math.h"


//double getCosRadians(const double &angle) {
//    return cos(angle * PI / 180);
//}


//double getSinRadians(const double &angle) {
//    return sin(angle * PI / 180);
//}


//pointT findMinPoint(const modelT &model) {
//    pointT point = *model.coords;

//    for (int i = 0; i < model.vertices_count; i++) {
//        if ((model.coords + i)->x < point.x) {
//            point.x = (model.coords + i)->x;
//        }
//        if ((model.coords + i)->y < point.y) {
//            point.y = (model.coords + i)->y;
//        }
//        if ((model.coords + i)->z < point.z) {
//            point.z = (model.coords + i)->z;
//        }
//    }

//    return point;
//}


//pointT findMaxPoint(const modelT &model) {
//    pointT point = *model.coords;

//    for (int i = 0; i < model.vertices_count; i++) {
//        if ((model.coords + i)->x > point.x) {
//            point.x = (model.coords + i)->x;
//        }
//        if ((model.coords + i)->y > point.y) {
//            point.y = (model.coords + i)->y;
//        }
//        if ((model.coords + i)->z > point.z) {
//            point.z = (model.coords + i)->z;
//        }
//    }

//    return point;
//}


//void modelCenterUpdate(modelT &model) {
//     pointT pointMax = findMaxPoint(model);
//     pointT pointMin = findMinPoint(model);

//    model.center.x = pointMin.x + (pointMax.x - pointMin.x) / 2;
//    model.center.y = pointMin.y + (pointMax.y - pointMin.y) / 2;
//    model.center.z = pointMin.z + (pointMax.z - pointMin.z) / 2;


//    printf("MODEL_CENTeR LOLLL = %lf   %lf   %lf\n", model.center.x, model.center.y, model.center.z);

//}



//void rotateCoordX(pointT &tempPoint, pointT &point, const double &angle, const pointT &centerPoint) {
//    double cosRadians = getCosRadians(angle);
//    double sinRadians = getSinRadians(angle);

//    tempPoint.x = point.x;
//    tempPoint.y = centerPoint.y + (point.y - centerPoint.y) * cosRadians - (point.z - centerPoint.z) * sinRadians;
//    tempPoint.z = centerPoint.z + (point.y - centerPoint.y) * sinRadians + (point.z - centerPoint.z) * cosRadians;
//}

//void rotateCoordY(pointT &tempPoint, pointT &point, const double &angle, const pointT &centerPoint) {
//    double cosRadians = getCosRadians(angle);
//    double sinRadians = getSinRadians(angle);

//    tempPoint.y = point.y;
//    tempPoint.x = centerPoint.x + (point.x - centerPoint.x) * cosRadians + (point.z - centerPoint.z) * sinRadians;
//    tempPoint.z = centerPoint.z + (-(point.x - centerPoint.x)) * sinRadians + (point.z - centerPoint.z) * cosRadians;

//}


//void rotateCoordZ(pointT &tempPoint, pointT &point, const double &angle, const pointT &centerPoint) {
//    double cosRadians = getCosRadians(angle);
//    double sinRadians = getSinRadians(angle);

//    tempPoint.z = point.z;
//    tempPoint.x = centerPoint.x + (point.x - centerPoint.x) * cosRadians - (point.y - centerPoint.y) * sinRadians;
//    tempPoint.y = centerPoint.y + (point.x - centerPoint.x) * sinRadians + (point.y - centerPoint.y) * cosRadians;
//}



//void rotatePoint(pointT &point, const pointT &angle, const pointT &centr) {
//    pointT tempPoint;
//    tempPoint.x = 0.0;
//    tempPoint.y = 0.0;
//    tempPoint.z = 0.0;


//    if (fabs(angle.x) > __DBL_EPSILON__) {
//        rotateCoordX(tempPoint, point, angle.x, centr);
//    }

//    if (fabs(angle.y) > __DBL_EPSILON__) {
//        rotateCoordY(tempPoint, point, angle.y, centr);
//    }

//    if (fabs(angle.z) > __DBL_EPSILON__) {
//        rotateCoordZ(tempPoint, point, angle.z, centr);
//    }

//    point = tempPoint;
//}


//int rotateModel(modelT &model, const pointT &point) {
//    if (!model.coords || !model.edges) {
//        return ERR_EMPTY_MODEL;
//    }
//    modelCenterUpdate(model);
//     printf("MODEL_CENTeR = %lf   %lf   %lf\n", model.center.x, model.center.y, model.center.z);
//    for (int i = 0; i < model.vertices_count; i++) {
//        rotatePoint(*(model.coords + i), point, model.center);
//    }

//    return OK;
//}
