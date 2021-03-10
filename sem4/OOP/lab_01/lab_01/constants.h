#ifndef CONSTANTS_H
#define CONSTANTS_H

#define OK                             0
#define ERR_FILE_READ_INT             -1
#define ERR_FILE_READ_POINT           -2
#define ERR_FILE_READ_EDGE_CONNECTION -3
#define ERR_OPEN_FILE                 -4
#define ERR_CLOSE_FILE                -5
#define ERR_EMPTY_MODEL               -6
#define ERR_ALLOC_MODEL               -7
#define ERR_SCALE_COEFF               -8

#define LOAD_MODEL                    10
#define DRAW_MODEL                    11
#define MOVE_MODEL                    12
#define ROTATE_MODEL                  13
#define SCALE_MODEL                   14
#define FREE_MODEL                    15

#define ERR_TITLE               "Ошибка!"
#define ERR_OPEN_MSG            "Невозможно открыть указанный файл!"
#define ERR_ALLOC_MSG           "Невозможно выделить память под модель!"
#define ERR_EMPTY_MODEL_MSG     "Для начала работы введите модель из файла"
#define ERR_CLOSE_FILE_MSG      "Невозможно закрыть файл"
#define ERR_FILE_READ_INT_MSG   "Ошибка в вводимых данных (описание файла)"
#define ERR_FILE_READ_POINT_MSG "Ошибка в вводимых данных (неверно указаны координаты точки)"
#define ERR_FILE_READ_EDGE_MSG  "Ошибка в вводимых данных (неверно указаны соединения ребер)"
#define ERR_SCALE_COEFF_MSG     "Ошибка в коэффициенте масштабирования!"

#define PI 3.1415
#define EPS 1e-6

#define SCENE_WIDHT 600
#define SCENE_HEIGHT 500

#endif // CONSTANTS_H
