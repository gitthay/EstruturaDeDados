#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *prox;
}no;

void imprime(no *lista);
void inserefinal(no **lista, int v);
void insereinicio(no **lista, int v);
void insereordenado(no **lista, int n);
void removeinicio(no **lista);
void removefinal(no **lista);
void buscaremove(no **lista, int n);

int main(){
    no *lista = NULL;

    inserefinal(&lista, 10);
    inserefinal(&lista, 10);
    inserefinal(&lista, 30);
    inserefinal(&lista, 10);
    inserefinal(&lista, 50);
    inserefinal(&lista, 60);
    buscaremove(&lista, 10);
    imprime(lista);
}


void buscaremove(no **lista, int n){
    no *aux = (*lista)->prox, *aux2;
    if(*lista==NULL)
        return;
    if(aux->prox == aux && aux->valor == n){
        *lista = NULL;
        return;
    }

    if(aux->valor == n){
        removeinicio(lista);
        buscaremove(lista, n);
    }
    else{
        while(aux -> prox != *lista && aux->prox->valor != n){
            aux = aux->prox;
        }
        if (aux->prox == *lista && aux->prox->valor==n)
            removefinal(lista);
        
        else if(aux->prox->valor == n){
            aux2 = aux->prox;
            aux->prox = aux2->prox;
            free(aux2);
            buscaremove(lista, n);
        }
        else
            return;
    }
}

void removefinal(no **lista){
    no *aux = (*lista)->prox, *aux2;

    if(*lista==NULL)
        return;
    if( aux->prox == aux){
        *lista = NULL;
        return;
    }
    
    while(aux->prox != *lista){
        aux = aux->prox;    
    }
    aux2 = *lista;
    aux->prox = (*lista)->prox;
    *lista = aux;
    free(aux2);
}


void removeinicio(no **lista){
    no *aux = (*lista)->prox;

    if(*lista==NULL)
        return;
    if( aux->prox == aux){
        *lista = NULL;
        return;
    }
    
    (*lista)->prox = aux->prox;
    free(aux);

}

void insereordenado(no **lista, int n){
    no *aux = (*lista)->prox, *novo;
    
    novo = (no*)malloc(sizeof(no));
    novo->valor = n;

    if(*lista == NULL){
        novo->prox = novo;
        *lista = novo;
    }
    else if(aux->valor >= n){
        novo->prox = (*lista)->prox;
        (*lista)->prox = novo;
    }
    else{
        while(aux != *lista && aux->prox->valor <= n){
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
        if(aux == *lista)
            *lista = novo;
    }


}


void insereinicio(no **lista, int v){
    no *novo;
    novo = malloc(sizeof(no));
    novo->valor = v;

    if(*lista == NULL){
        novo->prox = novo;
        *lista = novo;
    }
    else{
        novo->prox = (*lista)->prox;
        (*lista)->prox = novo;
    }
}

void inserefinal(no **lista, int v){
    no *novo;
    novo = malloc(sizeof(no));
    novo->valor = v;

    if(*lista == NULL){
        novo->prox = novo;
        *lista = novo;
    }
    else{
        novo->prox = (*lista)->prox;
        (*lista)->prox = novo;
        (*lista) = novo;
    }
}

void imprime(no *lista){
    if(lista == NULL){
        printf("ta vazia vei");
    }
    else{
        no *aux = lista->prox;
        while(aux!= lista){
            printf("%d -> ", aux->valor);
            aux = aux->prox;
        }
        printf("%d", aux->valor);
    }
}