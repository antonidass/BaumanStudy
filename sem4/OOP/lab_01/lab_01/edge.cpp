#include "edge.h"
#include "structures.h"
#include "constants.h"


void freeEdges(edgesDataT &edgesData) {
    if (edgesData.edges != nullptr) {
        delete[] edgesData.edges;
    }
}


int allocateEdges(edgesDataT &edgesData) {
    edgesData.edges = new edgeT[edgesData.edges_count];

    if (edgesData.edges == nullptr) {
        return ERR_ALLOC_EDGES;
    }

    return OK;
}


int readAmount(edgesDataT &edgesData, FILE *file) {
    if (fscanf(file, "%d", &edgesData.edges_count) != 1) {
        return ERR_FILE_READ_EDGE_COUNT;
    }

    return OK;
}


int readEdge(edgeT &edge, FILE *file) {
    if (fscanf(file, "%d%d", &edge.left_vertex, &edge.right_vertex) != 2) {
        return ERR_FILE_READ_EDGE_CONNECTION;
    }

    return OK;
}


int readEdges(edgesDataT &edgesData, FILE *file) {
    int check = OK;

    for (int i = 0; i < edgesData.edges_count && !check; i++) {
        check = readEdge(edgesData.edges[i], file);
    }

    return check;
}


int loadEdges(edgesDataT &edgesData, FILE *file) {
    int check = OK;

    if ((check = readAmount(edgesData, file))) {
        return check;
    }

    if ((check = allocateEdges(edgesData))) {
        return check;
    }

    if ((check = readEdges(edgesData, file))) {
        freeEdges(edgesData);
        return check;
    }

    return OK;
}
