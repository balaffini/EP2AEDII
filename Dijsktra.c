#ifndef DIJSKTRA_C
#define DIJSKTRA_C

#include "Dijsktra.h"

void inicializaDijsktra(GRAFO g, int* d, int s){
    for (int v = 0; v < g->vertices; v++){
        d[v] = INT_MAX/2;
    }
    d[s] = 0;
}

int* dijkstra(GRAFO g, int s){
    int* d = (int*) malloc(sizeof(int)*g->vertices);
    inicializaDijsktra(g, d, s);

    PFILA f = criarFila(g->vertices);
    inserirElemento(f, s, g->vertices);
    
    ADJACENCIA ad;
    while(tamanho(f)){
        PONT u = removerElemento(f);

        ad = g->adj[u->id].cab;
        while(ad){
            if(d[ad->vertice] > d[u->id] + ad->peso){
                d[ad->vertice] = d[u->id] + ad->peso;
                if(!(inserirElemento(f, ad->vertice, (d[u->id] + ad->peso))))
                    reduzirPrioridade(f, ad->vertice, (d[u->id] + ad->peso));
            }
            ad = ad->prox;
        }
    }
    return d;
}

#endif