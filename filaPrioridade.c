#ifndef FILAPRIORIDADE_C
#define FILAPRIORIDADE_C

#include "filaPrioridade.h"

PFILA criarFila(int max) {
    PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
    res->maxElementos = max;
    res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
    int i;
    for (i=0;i<max;i++) {
        res->arranjo[i] = NULL;
    }
    PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->fila = cabeca;
    cabeca->ant = cabeca;
    cabeca->prox = cabeca;
    cabeca->id = -1;
    cabeca->prioridade = 1000000;
    return res;
}

int tamanho(PFILA f) {
    int tam = 0;
    PONT ende = f->fila->prox;
    while (ende != f->fila) {
        ende = ende->prox;
        tam++;
    }
    return tam;
}

PONT buscaAnt(PFILA f, float prio, PONT* np) {
    *np = f->fila;
    PONT atual = f->fila->prox;  

    while(atual->prioridade < prio) {           
        *np = atual;                      
        atual = atual->prox;               
    }
             
    return atual;
}

PONT buscaid(PFILA f, int id, PONT* ante) {         
    
    *ante = f->fila;                        
    PONT atual = f->fila->prox;                     
    f->fila->id = id;               

    while(atual->id != id) {    
        *ante = atual;                               
        atual = atual->prox;                    
    }

    if ((atual != f->fila) && (atual->id == id)) {  
        f->fila->id = -1;
        return atual;
    }

    f->fila->id = -1;
    return NULL;
}

bool inserirElemento(PFILA f, int id, float prioridade) {
    bool resposta = false;

    if(id >= 0 && id < f->maxElementos) {                
        PONT anterior, np;   
        PONT i = buscaid(f, id, &anterior);             
        
        if(i == NULL) {                                  
            PONT a = buscaAnt(f, prioridade, &np);     
            i = (PONT) malloc(sizeof(ELEMENTO));
            i->id = id;
            i->prioridade = prioridade;
            i->prox = np->prox;
            np->prox = i;
            f->arranjo[id] = i;
            resposta = true;                       
        }
    }
    return resposta;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade) {

    bool resposta = false;

    if(id >= 0 && id < f->maxElementos) {  
        PONT anterior, np;
        PONT i = buscaid(f, id, &anterior);

        if(i != NULL && i->prioridade>novaPrioridade) {  
            PONT a = buscaAnt(f, novaPrioridade, &np);  
            i->prioridade = novaPrioridade; 
            anterior->prox = i->prox;
            i->prox = np->prox;
            np->prox = i;   
        }
    }
    return resposta;
}

PONT removerElemento (PFILA f) {
    PONT resposta = NULL;
    if (f->fila->prox != NULL && f->fila->prox != f->fila) {         
        PONT aux = f->fila->prox;    
        f->arranjo[aux->id] = NULL;                                   
        resposta = aux;                                             
        f->fila->prox = aux->prox;   
        f->fila->prox->ant = aux->ant;                               
    }
    return resposta;
}

bool consultarPrioridade(PFILA f, int id, float* resposta) {
    bool resp = false;

    if(id >= 0 && id < f->maxElementos) {
        PONT anterior;
        PONT i = buscaid(f, id, &anterior);
        if(i != NULL) {
            float qual = i->prioridade;
            resposta = &qual;
            resp  = true;
        }
    }
    return resp;
}

#endif