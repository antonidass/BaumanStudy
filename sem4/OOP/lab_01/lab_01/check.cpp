#include "check.h"
#include "constants.h"
#include <string.h>

int checkCoordsEmpty(const pointsDataT &pointsData) {
    if (pointsData.coords == nullptr) {
        return ERR_EMPTY_MODEL;
    }

    return OK;
}


int checkEdgesEmpty(const edgesDataT &edgesData) {
    if (edgesData.edges == nullptr) {
        return ERR_EMPTY_MODEL;
    }

    return OK;
}


int checkModelEmpty(const modelT &model) {
    int check = OK;

    if ((check = checkCoordsEmpty(model.pointsData))) {
        return check;
    }

    return checkEdgesEmpty(model.edgesData);
}


int checkCanvasEmpty(const canvasT &canvas) {
    if (!canvas.scene) {
        return ERR_EMPTY_SCENE;
    }

    return OK;
}


void handleError(const int &check, char error[]) {
    if (check == ERR_ALLOC_EDGES) {
        strncpy(error, ERR_ALLOC_MSG, WORD_LEN);
    }
    else if (check == ERR_ALLOC_COORDS) {
        strncpy(error, ERR_ALLOC_VERT_MSG, WORD_LEN);
    }
    else if (check == ERR_EMPTY_MODEL) {
        strncpy(error, ERR_EMPTY_MODEL_MSG, WORD_LEN);
    }
    else if (check == ERR_FILE_READ_INT) {
        strncpy(error, ERR_FILE_READ_INT_MSG, WORD_LEN);
    }
    else if (check == ERR_FILE_READ_POINT) {
        strncpy(error, ERR_FILE_READ_POINT_MSG, WORD_LEN);
    }
    else if (check == ERR_FILE_READ_EDGE_CONNECTION) {
        strncpy(error, ERR_FILE_READ_EDGE_MSG, WORD_LEN);
    }
    else if (check == ERR_SCALE_COEFF) {
        strncpy(error, ERR_SCALE_COEFF_MSG, WORD_LEN);
    }
    else if (check == ERR_EMPTY_SCENE) {
        strncpy(error, ERR_EMPTY_SCENE_MSG, WORD_LEN);
    }    
}
