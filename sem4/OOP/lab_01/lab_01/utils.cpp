#include "utils.h"
#include "constants.h"
#include "math.h"


int checkScaleCoeffs(const scaleT &scale) {
    if (fabs(scale.kx) < EPS || fabs(scale.ky) < EPS || fabs(scale.kz) < EPS) {
        return ERR_SCALE_COEFF;
    }

    return OK;
}


double getCosAngle(const double &angle) {
    return cos(angle * PI / 180);
}


double getSinAngle(const double &angle) {
    return sin(angle * PI / 180);
}
