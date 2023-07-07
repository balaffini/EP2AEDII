#ifndef DAGMIN_C
#define DAGMIN_C

#include "DAGmin.h"

void inicializaDAGmin(GRAFO g, int* m, int s){
    for (int v = 0; v < g->vertices; v++){
        m[v] = INT_MAX/2;
    }
    m[s] = 0;
}

void ordenacaoTopologica(GRAFO g, int* ot){
    int vis[g->vertices];
    int e = g->vertices -1;
    for(int i = 0; i < g->vertices; i++){
        ot[i] = -1;
        vis[i] = 0;
    }
    for(int i = 0; i < g->vertices; i++){
        if(vis[i] != 2)
            ordenacaoProfundidade(g, vis, i, ot, &e);
    }
}

void ordenacaoProfundidade(GRAFO g, int* vis, int i, int* ot, int* e){
    vis[i] = 1;
    ADJACENCIA a = g->adj[i].cab;
    while(a){
        if(!vis[a->vertice])
            ordenacaoProfundidade(g, vis, a->vertice, ot, e);
        a = a->prox;
    }
    vis[i] = 2;
    ot[*e] = i;
    e[0]--;
}

bool DAGmin(GRAFO g, int s, int* m){
    inicializaDAGmin(g, m, s);

    int* ot = (int*) malloc(sizeof(int)*g->vertices);
    ordenacaoTopologica(g, ot);

    /*for(int i = 0; i < g->vertices; i++){
        printf("%i ", ot[i]);
    }
    printf("\n");*/

    ADJACENCIA adj = g->adj[0].cab;
    int i;
    for(int o = ot[i = 0]; i < g->vertices; o = ot[i++]){
        if(m[o] == INT_MAX/2)
            continue;
        adj = g->adj[o].cab;
        while(adj){
            if(m[adj->vertice] > m[o] + adj->peso){
                m[adj->vertice] = m[o] + adj->peso;
            }
            adj = adj->prox;
        }
    }
    bool res = true;
    return res;
}

#endif