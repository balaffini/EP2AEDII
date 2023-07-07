#include "BellmanFord.c"
#include "Dijsktra.c"
#include "DAGmin.c"
#include "time.h"

GRAFO geraGrafo(int n, int p, int k){
    GRAFO g = criaGrafo(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j){
                if(!(rand() % p)) //chance de 1 em p
                    criaAresta(g, i, j, (rand() % k));
            }
        }
    }
    return g;
}

GRAFO geraDAG(int n, int p, int k){
    GRAFO dag = criaGrafo(n);
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(!(rand() % p)) //chance de 1 em p
                criaAresta(dag, i, j, (rand() % k));
        }
    }
    return dag;
}

int main(){
    /*GRAFO gr = criaGrafo(5);
    criaAresta(gr, 0, 1, 2);
    criaAresta(gr, 1, 2, 4);
    criaAresta(gr, 2, 0, 12);
    criaAresta(gr, 2, 4, 40);
    criaAresta(gr, 3, 1, 3);
    criaAresta(gr, 4, 3, 8);
    GRAFO gr = criaGrafo(6);
    criaAresta(gr, 0, 1, 10);
    criaAresta(gr, 0, 2, 5);
    criaAresta(gr, 2, 1, 3);
    criaAresta(gr, 1, 3, 1);
    criaAresta(gr, 2, 3, 8);
    criaAresta(gr, 2, 4, 2);
    criaAresta(gr, 4, 5, 6);
    criaAresta(gr, 3, 5, 4);
    criaAresta(gr, 3, 4, 4);

    int *d = dijkstra(gr, 0);
    printf("Dijkstra:\n");
    for(int i = 0; i < gr->vertices; i++){
        printf("D(v0->v%i) = %i\n", i, d[i]);
    }

    printf("\n");

    int *b = (int*) malloc(sizeof(int)*gr->vertices);
    printf("BellmanFord:\n");
    b = bellmanFord(gr, 0);
    for(int i = 0; i < gr->vertices; i++){
        printf("D(v0->v%i) = %i\n", i, b[i]);
    }

    printf("\n");
    GRAFO dag = criaGrafo(6);
    criaAresta(dag, 0, 2, 2);
    criaAresta(dag, 0, 3, 4);
    criaAresta(dag, 0, 4, 3);
    criaAresta(dag, 2, 1, 1);
    criaAresta(dag, 2, 4, -1);
    criaAresta(dag, 3, 4, -2);
    criaAresta(dag, 3, 5, 1);
    criaAresta(dag, 4, 1, 0);
    criaAresta(dag, 4, 5, 1);
    criaAresta(dag, 5, 1, 2);

    int *m = (int*) malloc(sizeof(int)*dag->vertices);
    printf("DAGmin:\n");
    DAGmin(dag, 0, m);
    for(int i = 0; i < dag->vertices; i++){
        printf("D(v0->v%i) = %i\n", i, m[i]);
    }

    printf("\n");

    imprime(gr);

    printf("\n");

    imprime(dag);

    */
    
    //int n = vertices
    //int p = probabilidade de entrar
    //int k = peso

    int ns[] = {100, 1000, 1500, 2000, 3000, 5000, 10000};
    double ps[] = {0.1, 0.2, 0.4, 0.5, 0.6, 0.8, 0.9};
    int ks[] = {10, 100, 150, 200, 300, 500, 1000};
    int testes = 7;

    srand(time(NULL));

    int cnt = 1;
    GRAFO g;
    clock_t t0, tf;
    double t;
    for(int i = 0; i < testes; i++){
        for(int j = 0; j < testes; j++, cnt++){
            printf("Grafo teste %i:\nn = %i, p = %.1lf, k = %i\n", cnt, ns[i], ps[j], ks[i]);
            g = geraGrafo(ns[i], (int)(1.0/ps[j]), ks[i]);
            printf("Arestas: %i\n", g->arestas);
            t0 = clock();
            bellmanFord(g, 0);
            tf = clock();
            t = (double) (tf - t0) / (CLOCKS_PER_SEC);
            printf("Algoritmo de BellmanFord - %lfs\n", t);

            t0 = clock();
            dijkstra(g, 0);
            tf = clock();
            t = (double) (tf - t0) / (CLOCKS_PER_SEC);
            printf("Algoritmo de Djisktra - %lfs\n\n", t);
        }
    }

    printf("DAGs\n\n");

    cnt = 1;
    GRAFO dag; 
    for(int i = 0; i < testes; i++){
        for(int j = 0; j < testes; j++, cnt++){
            printf("DAG teste %i:\nn = %i, p = %.1lf, k = %i\n", cnt, ns[i], ps[j], ks[i]);
            dag = geraDAG(ns[i], (int)(1.0/ps[j]), ks[i]);
            
            t0 = clock();
            bellmanFord(dag, 0);
            tf = clock();
            t = (double) (tf - t0) / (CLOCKS_PER_SEC);
            printf("Algoritmo BellmanFord - %lfs\n", t);

            t0 = clock();
            dijkstra(dag, 0);
            tf = clock();
            t = (double) (tf - t0) / (CLOCKS_PER_SEC);
            printf("Algoritmo Djisktra - %lfs\n", t);

            int* m = (int*) malloc(sizeof(int)*dag->vertices);
            t0 = clock();
            DAGmin(dag, 0, m);
            tf = clock();
            t = (double) (tf - t0) / (CLOCKS_PER_SEC);
            printf("Algoritmo DAGmin - %lfs\n\n", t);
            free(m);
        }
    }
}
