#ifndef GRAFO_C
#define GRAFO_C

#include "Grafo.h"

GRAFO criaGrafo(int v){
    GRAFO g = (GRAFO) malloc(sizeof(Grafo));
    g->vertices = v;
    g->arestas = 0;
    g->abertos = v;
    g->adj = (VERTICE) malloc(v*sizeof(Vertice));
    for(int i = 0; i < v; i++)
        g->adj[i].cab = NULL;
    return g;
}

ADJACENCIA criaAdj(int v, int peso){
    ADJACENCIA temp = (ADJACENCIA) malloc(sizeof(Adjacencia));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    temp->aberto = true;
    return temp;
}

bool criaAresta(GRAFO gr, int vi, int vf, int p){
    if(!gr)
        return false;
    if((vf < 0) || (vf >= gr->vertices))
        return false;
    if((vi < 0) || (vi >= gr->vertices))
        return false;
    ADJACENCIA novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
}

void imprime(GRAFO gr){
    printf("Vértices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
    for(int i = 0; i < gr->vertices; i++){
        printf("v%d: ", i);
        ADJACENCIA ad = gr->adj[i].cab;
        while(ad){
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

#endif