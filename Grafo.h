#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

typedef struct adjacencia{
    int vertice;
    int peso;
    bool aberto;
    struct adjacencia *prox;
} Adjacencia, *ADJACENCIA;

typedef struct vertice{
    ADJACENCIA cab;
} Vertice, *VERTICE;

typedef struct grafo{
    int vertices;
    int arestas;
    int abertos;
    VERTICE adj;
} Grafo, *GRAFO;

GRAFO criaGrafo(int v);

ADJACENCIA criaAdj(int v, int peso);

bool criaAresta(GRAFO gr, int vi, int vf, int p);

void imprime(GRAFO gr);

#endif