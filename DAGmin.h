#ifndef DAGMIN_H
#define DAGMIN_H

#include "Grafo.c"
#include <limits.h>

void inicializaDAGmin(GRAFO g, int* m, int s);

void ordenacaoTopologica(GRAFO g, int* ot);

void ordenacaoProfundidade(GRAFO g, int* vis, int i, int* ot, int* e);

bool DAGmin(GRAFO g, int s, int* m);

#endif