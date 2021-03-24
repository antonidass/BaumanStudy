#include "draw.h"
#include "constants.h"
#include "check.h"


pointT getPoint(const pointT coords[], const int &index) {
    return coords[index];
}


void drawEdge(const edgeT &edge, const pointT coords[], const canvasT &canvas) {
    pointT point1 = getPoint(coords, edge.left_vertex);
    pointT point2 = getPoint(coords, edge.right_vertex);

    drawLine(point1, point2, canvas);
}


void drawEdges(const edgesDataT &edgesData, const pointsDataT &pointsData, const canvasT &canvas) {
    for (int i = 0; i < edgesData.edges_count; i++) {
        drawEdge(edgesData.edges[i], pointsData.coords, canvas);
    }
}
