#ifndef DIJSKTRA_H
#define DIJSKTRA_H

#include <limits.h>

#include "filaPrioridade.c"
#include "Grafo.c"

int* dijkstra(GRAFO g, int s);
void inicializaDijsktra(GRAFO g, int* d, int s);

#endif