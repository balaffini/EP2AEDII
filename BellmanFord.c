#ifndef BELLMANFORD_C
#define BELLMANFORD_C

#include "BellmanFord.h"

void inicializaBellmanFord(GRAFO g, int* b, int s){
    for (int v = 0; v < g->vertices; v++){
        b[v] = INT_MAX/2;
    }
    b[s] = 0;
}

int* bellmanFord(GRAFO g, int s){
    int* b = (int*) malloc(sizeof(int)*g->vertices);
    inicializaBellmanFord(g, b, s);

    ADJACENCIA a;
    for(int j = 0; j < g->vertices-1; j++){
        for(int i = 0; i < g->vertices-1; i++){
            a = g->adj[i].cab;
            while(a){
                if(b[a->vertice] > b[i] + a->peso){
                    b[a->vertice] = b[i] + a->peso;
                }
                a = a->prox;
            }
        }
    }

    for(int i = 0; i < g->vertices-1; i++){
        a = g->adj[i].cab;
        while(a){
            if(b[a->vertice] > b[i] + a->peso){
                return false;
            }
            a = a->prox;
        }
    }
    
    return b;
}

#endif