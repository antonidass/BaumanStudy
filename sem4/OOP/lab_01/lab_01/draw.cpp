#include "draw.h"
#include "constants.h"


void drawEdge(const edgeT &edge, const pointT *const coords , QGraphicsScene *const scene) {
    const pointT point1 = *(coords + edge.left_vertex);
    const pointT point2 = *(coords + edge.right_vertex);

    scene->addLine(point1.x, point1.y, point2.x, point2.y);
}


int drawModel(const modelT &model, QGraphicsScene *const scene) {
    if (model.edges_count <= 0 || model.vertices_count <= 0 || !model.coords || !model.edges) {
        return ERR_EMPTY_DATA;
    }

    scene->clear();

    for (int i = 0; i < model.edges_count; i++) {
        drawEdge(*(model.edges + i), model.coords, scene);
    }

    return OK;
}
