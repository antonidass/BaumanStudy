#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
    int left_vertex;
    int right_vertex;
} edgeT;


typedef struct {
    edgeT *edges;
    int edges_count;
} edgesDataT;


void freeEdges(edgesDataT &edgesData);

int allocateEdges(edgesDataT &edgesData);

int loadEdges(edgesDataT &edgesData, FILE *file);

int readEdges(edgesDataT &edgesData, FILE *file);

int readEdge(edgeT &edge, FILE *file);

int readAmount(edgesDataT &edgesData, FILE *file);


#endif // EDGE_H
