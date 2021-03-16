#include "draw.h"

void drawModel(const modelT& model, QGraphicsScene *scene) {
    scene->clear();

    for (int i = 0; i < model.edges_count; i++) {
        scene->addLine((model.coords + (model.edges + i)->left_vertex)->x,
                       (model.coords + (model.edges + i)->left_vertex)->y,
                       (model.coords + (model.edges + i)->right_vertex)->x,
                       (model.coords + (model.edges + i)->right_vertex)->y);
    }
}
