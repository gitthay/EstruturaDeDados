#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//basico
typedef struct No{
    int valor;
    struct No *esq, *dir, *pai; 
} no;

typedef struct NO{
    no* No;
    struct NO *prox; 
} nolista;

no* criarNo (int valor, no* pai);

//pilha e fila
nolista* desempilha(nolista **lista);
nolista* desenfilera(nolista **lista);
void inserefinal(nolista **lista, no *v);
int vazio(nolista *lista);

//vistas
void preordemrecursiva(no *raiz);
void inordemrecursiva(no *raiz);
void posordemrecursiva(no *raiz);
void preordem(no *raiz);
void inordem(no *raiz);
void posordem(no *raiz);

void imprimirlargura(no *raiz);

void inserirrecursiva(no **arv, int valor);
void inserir(no **raiz, int v); 

no* buscarecursiva(no *raiz, int v);
no* busca(no *raiz, int v);

int quantosnosparesrecursiva(no *arvore);
int quantosnos(no *arvore); 

int quantasfolhasrecursiva(no *NO);
int quantasfolhas(no *NO);

int alturarecursiva(no *arvore);
int altura(no *arvore);

int compararecursiva(no *a1, no *a2);
int compara(no *a1, no *a2);

no* buscaremoverecursiva(no *arv, int v);
void buscaremove(no **arv, int v);
bool balanceada(no* r);

int main(){
    no *arv = NULL;

    inserir(&arv, 30);
    inserir(&arv, 40);
    inserir(&arv, 50);
    inserir(&arv, 60);
    inserir(&arv, 70);
    inserir(&arv, 80);
    inserir(&arv, 90);

    printf("%d", imprimirlargura(arv));
    
}

bool balanceada(no* r){
    if (r == NULL)
        return true;
    else{
        int fb = alturarecursiva(r->esq) - alturarecursiva(r->dir);
        if (fb < -1 || fb > 1)
            return false;
        else
            return balanceada(r->esq) && balanceada(r->dir);
    }

}  

no* buscaremoverecursiva(no *arv, int v){
    if (arv==NULL){
        printf("Nao ta aqui brother! (broder?)");
        return NULL;
    }
    else{
        if(arv->valor == v){
            if(arv->dir == NULL && arv->esq == NULL){//no folha
                free(arv);
                return NULL;
            }
            if(arv->dir != NULL && arv->esq != NULL){//dois filhos
                no* aux = arv->esq;
                while(aux->dir != NULL)
                    aux = aux->dir;

                arv->valor = aux->valor;
                aux->valor = v;

                arv->esq = buscaremoverecursiva(arv->esq, v);
                return arv;       
            }
            else{//1 filho
                no *aux;
                if(arv->dir!=NULL)
                    aux = arv->dir;
                else
                    aux = arv->esq;
                free(arv);
                return aux;
            }
        }
        else{
            if(v > arv->valor)
                arv->dir = buscaremoverecursiva(arv->dir, v);
            else
                arv->esq = buscaremoverecursiva(arv->esq, v);
        }
    }
}



void buscaremove(no **arv, int v){
    no *aux = *arv, *aux2;
    while(aux != NULL && aux->valor != v){
        if(v < aux->valor){
            aux = aux->esq;
        }
        else if(v > aux->valor){
            aux = aux->dir;
        }
    }
    
    if(aux){
        if(aux->dir == NULL && aux->esq == NULL){ //no folha
            aux2 = aux;
            if(aux->pai == NULL) 
                *arv = NULL;
            else if(aux->pai->dir == aux) 
                aux->pai->dir = NULL;
            else 
                aux->pai->esq = NULL;
            free(aux2);
        }
        else if(aux->dir != NULL && aux->esq == NULL){//no com 1 filho, a dir
            aux2 = aux; 
            if(aux->pai == NULL){
                *arv = aux->dir;
             }    
            else if(aux->pai->dir == aux){
                aux->dir->pai = aux->pai;
                aux->pai->dir = aux->dir;
            }
            else {
                aux->esq->pai = aux->pai;
                aux->pai->esq = aux->dir;
            }
            free(aux2);
        }
        else if(aux->dir == NULL && aux->esq != NULL){//no com 1 filho, a esq
            aux2 = aux; 
            if(aux->pai == NULL){
                *arv = aux->esq;
             }    
            else if(aux->pai->dir == aux) 
                aux->pai->dir = aux->esq;
            else 
                aux->pai->esq = aux->esq;
            free(aux2);
        }

        else{//dois filhos
            no *aux3 = aux->esq;
            aux2 = aux;

            while(aux3->dir!=NULL){ 
                aux3 = aux3->dir;
            }

            aux3->dir = aux->dir; 
            aux->dir->pai = aux3;

            if(aux3->pai->valor < aux3->valor)
                aux3->pai->dir = aux3->esq;
            else if(aux3->pai->valor > aux3->valor)
                aux3->pai->esq = aux3->esq;


            if(aux->pai == NULL){
                aux3->pai = NULL;
                *arv = aux3;
            }
            else if (aux->pai->esq == aux)
                aux->pai->esq = aux3;
            
            else
                 aux->pai->dir = aux3;
            
            aux3->pai = aux->pai;
           
            free(aux2);
        }
    }
}


int compararecursiva(no *a1, no *a2) {
    if (a1 == NULL && a2 == NULL) {
        return 1;  
    }
    if (a1 == NULL || a2 == NULL) {
        return 0;  
    }
    if (a1->valor != a2->valor) { 
        return 0;  
    }
    return compararecursiva(a1->esq, a2->esq) && compararecursiva(a1->dir, a2->dir);
}


int compara(no *a1, no *a2){
    nolista *pilha1 = NULL, *pilha2 = NULL;
    inserefinal(&pilha1, a1);
    inserefinal(&pilha2, a2);
    
    while(!vazio(pilha1) && !vazio(pilha2)){
        nolista *elem1 = desempilha(&pilha1);
        nolista *elem2 = desempilha(&pilha2);
   
        no *n1 = elem1->No;
        no *n2 = elem2->No;
        
        free(elem1);
        free(elem2);
        
        if(n1 == NULL && n2 == NULL)
            continue;
        
        if(n1 == NULL || n2 == NULL)
            return 0;
        
        if(n1->valor != n2->valor)
            return 0;
        
        inserefinal(&pilha1, n1->esq);
        inserefinal(&pilha2, n2->esq);
        inserefinal(&pilha1, n1->dir);
        inserefinal(&pilha2, n2->dir);
    }
    
    if(!vazio(pilha1) || !vazio(pilha2))
        return 0;
    return 1;
}

int alturarecursiva(no *NO){
    if(NO==NULL)
        return 0;
    else{
        int esq = alturarecursiva(NO->esq);
        int dir = alturarecursiva(NO->dir);
        if (esq < dir)
            return dir + 1;
        else
            return esq + 1;
    }
}


int altura(no *arvore) {
    int cont = 0;
    nolista *fila = NULL;
    inserefinal(&fila, arvore);

    while(!vazio(fila)) {
        nolista *aux = fila;
        int quantfilhos = 0;

        while(aux!=NULL){
            quantfilhos++;
            aux = aux->prox;        
        }

        while(quantfilhos>0){
            nolista *elem  = desenfilera(&fila);
            if (elem->No->dir != NULL)
                inserefinal(&fila, elem->No->dir);
            if (elem->No->esq != NULL)
                inserefinal(&fila, elem->No->esq);
            quantfilhos--;

        }
        cont++;
    }
    return cont;
}

int quantasfolhasrecursiva(no *NO){
    if (NO==NULL) 
        return 0;
    else if(NO->dir == NULL && NO->esq == NULL)
        return 1;
    else{
        return quantasfolhasrecursiva(NO->dir) + quantasfolhasrecursiva(NO->esq);
    }
}

int quantasfolhas(no *NO){
    nolista* fila = NULL;
    int cont = 0; 
    
    inserefinal(&fila, NO);

    while(!vazio(fila)){
        nolista *elem = desempilha(&fila);

        if(elem->No->dir == NULL && elem->No->esq == NULL)
            cont++;
        else{
            if (elem->No->dir != NULL)
                inserefinal(&fila, elem->No->dir);
            if (elem->No->esq != NULL)
                inserefinal(&fila, elem->No->esq);
        }
        free(elem);

    }

    return cont;
}


void preordem(no *raiz){
    if(raiz){
        nolista *pilha = NULL;
        inserefinal(&pilha, raiz);

        while(!vazio(pilha)){
            nolista *noav = desempilha(&pilha);
            printf("%d ", noav->No->valor);
            if(noav->No->dir!=NULL)
                inserefinal(&pilha, noav->No->dir);
            if(noav->No->esq!=NULL)
                inserefinal(&pilha, noav->No->esq);
            free(noav);
        }
        printf("\n");
    }
}


void inordem(no* raiz) {
    nolista *pilha = NULL;
    
    no* atual = raiz;
    while(atual!= NULL || !vazio(pilha)){
        while(atual != NULL){
            inserefinal(&pilha, atual);
            atual = atual->esq;////anda esquerda
        }
        
        nolista *n = desempilha(&pilha);///processa ultimo
        printf("%d ", n->No->valor);  
        atual = n->No->dir; ///anda direita

    }
}

void posordem(no* raiz) {
    nolista *pilhafilhos = NULL, *pilhapais = NULL;

    inserefinal(&pilhafilhos, raiz);
    while(!vazio(pilhafilhos)){
        nolista* elem = desempilha(&pilhafilhos);
        inserefinal(&pilhapais, elem->No);

        if(elem->No->esq!= NULL)
            inserefinal(&pilhafilhos, elem->No->esq);
        if(elem->No->dir!= NULL)
            inserefinal(&pilhafilhos, elem->No->dir);
    }
    while(!vazio(pilhapais)){
        nolista* elem = desempilha(&pilhapais);
        printf("%d ", elem->No->valor);
        free(elem);
    }
}

void inordemrecursiva(no *raiz){
    if(raiz!=NULL){
        inordemrecursiva(raiz->esq);
        printf("%d ", raiz->valor);
        inordemrecursiva(raiz->dir);
    }
}

void posordemrecursiva(no *raiz){
    if(raiz!=NULL){
        posordemrecursiva(raiz->esq);
        posordemrecursiva(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

void preordemrecursiva(no *raiz){
    if(raiz!=NULL){
        printf("%d ", raiz->valor);
        preordemrecursiva(raiz->esq);
        preordemrecursiva(raiz->dir);
    }
}

void imprimirlargura (no* arv) {  
    if (arv != NULL) {
        nolista *fila = NULL;
        inserefinal(&fila, arv);

        nolista *n = fila;
        while (n!=NULL) {
            no *atual = n->No;
            if (atual->esq != NULL)
                inserefinal (&fila, atual->esq);

            if (atual->dir!= NULL)
                inserefinal(&fila, atual->dir);
            n = n->prox;
        }
        while(!vazio(fila)){
            nolista *aux2 = desenfilera(&fila);
                printf("%d ", aux2->No->valor);
                free(aux2);
        }
    }
}

int quantosnosparesrecursiva(no *arvore){
    if(arvore==NULL)
            return 0;
    else if (arvore->valor % 2 == 0)
        return quantosnosparesrecursiva(arvore->dir) + quantosnosparesrecursiva(arvore->esq) + 1;
    else{
        return quantosnosparesrecursiva(arvore->dir) + quantosnosparesrecursiva(arvore->esq);
    }
}

int quantosnos(no *arvore){
    int cont = 0;
    if(arvore){
        nolista *fila = NULL;
        inserefinal(&fila, arvore);
        while(!vazio(fila)){
        nolista * NO = desenfilera(&fila);
            if(NO->No->dir!=NULL)
                inserefinal(&fila, NO->No->dir);
            if(NO->No->esq!=NULL)
                inserefinal(&fila, NO->No->esq);
            cont++;
        }
    }
    return cont;
}

void inserir(no **raiz, int v){
    no *aux = *raiz, *pai = NULL, *novo;
    while(aux!=NULL){   ///verifico onde vou colocar, como eu sei o pai, sei o anterior de null
        pai = aux;
        if(v < aux->valor)
            aux = aux->esq;
            
        else
            aux = aux->dir;
    }
    novo = criarNo(v, pai);

    if(*raiz == NULL) //atribuo a arvore
        *raiz = novo;
    
    else if(v < pai->valor)
        pai->esq = novo;

    else
        pai->dir = novo;
}

void inserirrecursiva(no **raiz, int v){
    if(*raiz==NULL)
        *raiz = criarNo(v, NULL);
    else{
        if(v < (*raiz)->valor){
            if((*raiz)->esq==NULL)
                (*raiz)->esq = criarNo(v, *raiz);
            else{
                inserirrecursiva(&((*raiz)->esq), v);
            }
        }
        else {
            if((*raiz)->dir==NULL)
                (*raiz)->dir = criarNo(v, *raiz);
            else
                inserirrecursiva(&((*raiz)->dir), v);

        }
    }
}

no* busca(no *raiz, int v){
    no *p_raiz = raiz;
    while(p_raiz){
        if(p_raiz->valor == v)
            return p_raiz;
        else if(v < p_raiz->valor){
            p_raiz = p_raiz->esq;
        }
        else{
            p_raiz = p_raiz->dir;
        }
    }
    return NULL;
}


no* buscarecursiva(no *raiz, int v){
    while(raiz!=NULL){
        if(v == raiz->valor)
            return raiz;
        else if (v < raiz->esq->valor)
            return buscarecursiva(raiz->esq, v);
        else 
            return buscarecursiva(raiz->dir, v);
    }
    return NULL;

}


no* criarNo (int v, no *pai){
    no *novo;
    novo = (no*)malloc(sizeof(no));
    novo->valor = v;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = pai;

    return novo;
}

void liberamemoria(no *n){
    if(n!=NULL){
        liberamemoria (n->dir);
        liberamemoria (n->esq);
        free(n);    
    }
}

///pilhas e filas
nolista* desempilha(nolista **lista){
    nolista *aux=*lista, *elem=NULL;
    if(aux){
        if (aux->prox == NULL){
            elem = *lista;
            *lista =  NULL;
        }
        else{
            while(aux->prox->prox!=NULL)
                aux = aux->prox;
            elem = aux->prox;
            aux->prox = NULL;
        }
    }
    return elem;
}

nolista* desenfilera(nolista **lista){
    nolista *elem = NULL;
    if(*lista){
        elem = *lista;
        *lista = (*lista)->prox;
    }
    return elem;
}

void inserefinal(nolista **lista, no *v){
    nolista *novo;
    novo = malloc(sizeof(nolista));
    novo->prox = NULL;
    novo->No = v;
    
    if(*lista == NULL)
        *lista = novo;
    else{
        nolista *aux=*lista;
        while(aux->prox!=NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

int vazio(nolista *lista){
    return lista == NULL;
}