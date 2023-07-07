#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "Grafo.c"
#include <limits.h>

void inicializaBellmanFord(GRAFO g, int* b, int s);
int* bellmanFord(GRAFO g, int s);

#endif