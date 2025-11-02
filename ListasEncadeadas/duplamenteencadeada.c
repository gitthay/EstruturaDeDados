#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *prox;
    struct No *ant;
}no;

void inserefinal(no **lista, int v);
void insereinicio(no **lista, int v);
void insereordenado(no **lista, int n);
void imprime(no *lista);
void imprimeidaevolta(no *lista);
void removeinicio(no **lista);
void removefinal(no **lista);
int comprimento (no *l);
no* concatena (no *l1, no *l2);
no* inverte(no*l);
no* separa (no * l, int n); 
no* retira_n (no *l, int n);



int main(){
    no *lista = NULL;
    inserefinal(&lista, 10);
    inserefinal(&lista, 10);
    inserefinal(&lista, 30);
    inserefinal(&lista, 10);
    inserefinal(&lista, 40);
    inserefinal(&lista, 10);
    
    imprimeidaevolta(retira_n(lista, 10));
}


/*Implemente uma função que receba como parâmetro uma lista encadeada e inverta o encadeamento de
seus nós, retornando a lista resultante. Após a execução dessa função, cada nó da lista apontará para o
nó que originalmente era seu antecessor, e o último nó da lista passará a ser o primeiro nó da lista
invertida, conforme ilustrado a seguir*/
no* inverte(no* l) {
    no* atual = l;
    no* guarda = NULL;

    while (atual != NULL) {
        guarda = atual->ant;
        atual->ant = atual->prox;
        atual->prox = guarda;
    
        atual = atual->ant;

    }
    if (guarda!=NULL)
        l = guarda->ant;

    return l;
    
}





/*Implemente uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, e divida
a lista em duas, de tal forma que a segunda lista comece no primeiro nó logo após a primeira ocorrência
de n na lista original.*/
no* separa (no * l, int n){
    no *aux, *l2=NULL;
    
    aux = l;
    while(aux != NULL && aux->valor != n)
        aux = aux->prox;
    if(aux == NULL)
        printf("tem nao");
    else{
        l2 = aux->prox;
        l2->ant = NULL;

        aux->prox = NULL;
    }
    return l2;
}



/*Implemente uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, retire da
lista todas as ocorrências de n, e retorne a lista resultante.*/
no* retira_n (no *l, int n){
    no *aux1, *aux2;
    
    if(l == NULL || (l->prox == NULL && l->valor == n))
        return NULL; //retira se for so um elemneto

    aux1 = l;
    if(aux1->valor == n){
        aux1 = l;//retira no inicio
        l = aux1->prox;
        l->ant = NULL;
        free(aux1);
        return retira_n(l,n);
    }
    else{
        aux1 = l->prox;
        while(aux1->prox != NULL && aux1->valor != n){
            aux1 = aux1->prox;
        }
        if(aux1->valor == n && aux1->prox == NULL){
            aux2 = aux1;
            aux1->ant->prox = NULL;
            free(aux2);
        }
        else if(aux1->valor == n && aux1->prox != NULL){
            aux2 = aux1;
            aux1->ant->prox = aux2->prox;
            aux1->prox->ant = aux1->ant;
            free(aux2);
            return retira_n(l, n);
        }
    }
    return l;
}


/*Implemente uma função que receba duas listas encadeadas e retorne a lista resultante da concatenação
das duas listas recebidas como parâmetro, isto é, após a concatenação, o último elemento da primeira
lista deve apontar para o primeiro elemento da segunda lista.*/
no* concatena (no *l1, no *l2){
    no  *aux;
    aux = l1;

    if (l1==NULL)
        return l2;
    else if(l2==NULL)
        return l1;

    else {
        while(aux->prox!=NULL){
            aux = aux->prox;
        }
    aux->prox = l2;
    l2->ant = aux;
    }
    return l1;
}


/*Implemente uma função que tenha como valor de retorno o comprimento de uma lista encadeada, isto
é, calcule o número de nós de uma lista.*/

int comprimento (no *l) {
    int cont=0;

    while(l!=NULL){
        cont++;
        l = l->prox;
    }
    printf("%d", cont);
    return cont;

}


void removefinal(no **lista){
    no *aux1, *aux2;
    if (*lista == NULL) 
        printf("Lista Vazia Thay!");
    else if((*lista)->ant ==NULL && (*lista)->prox == NULL)
        *lista = NULL;
    else{
        aux1 = *lista;
        while(aux1->prox!= NULL){
            aux1 = aux1->prox;
        }
        aux2 = aux1;
        aux1->ant->prox = NULL;
        free(aux2);
    }
}
void removeinicio(no **lista){
    no *aux;
    if (*lista == NULL) 
        printf("Lista Vazia, num tem como remover!");
    else if((*lista)->ant == NULL && (*lista)->prox == NULL)
        *lista = NULL;
    else{
        aux = *lista;
        *lista = aux->prox;
        (*lista)->ant = NULL;
        free(aux);

    }
}


void insereinicio(no **lista, int v){
    no *novo;
    int valor;

    novo = (no*)malloc(sizeof(no));
    novo->prox = NULL;
    novo->valor = v;
    novo->ant = NULL;

    if(*lista==NULL)
        *lista = novo;
    else{
        novo->prox = *lista;
        (*lista)->ant = novo;
        *lista = novo;
    }
}


void inserefinal(no **lista, int v){
    no *aux, *novo;
    int valor;

    novo = (no*)malloc(sizeof(no));
    novo->prox = NULL;
    novo->valor = v;
    novo->ant = NULL;

    if(*lista==NULL)
        *lista = novo;

    else{
    aux = *lista;
    while(aux->prox != NULL)
        aux = aux->prox;
    
    aux->prox = novo;
    novo->ant = aux;
    }
}


void insereordenado(no **lista, int n){
    no *novo, *aux;
    novo = malloc(sizeof(no));
    novo->valor = n;
    novo->ant = NULL;
    novo->prox = NULL;
   
    if(*lista==NULL){
        *lista = novo;
        return;
    }

    aux = *lista;
    if(aux->valor >= n){
        novo->prox = *lista;
        (*lista)->ant = novo;
        *lista = novo;
        return;
    }

    while(aux->prox!=NULL && aux->prox->valor <= n){
        aux=aux->prox;
    }

    novo->ant = aux;
    novo->prox = aux->prox;
    aux->prox->ant = novo;
    aux->prox = novo;
}

void imprime(no *lista){
    no *aux;
    aux = lista;
    if(lista==NULL) printf("TA VAZIA!");
    else{
    while(aux!=NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}
}

void imprimeidaevolta(no *lista){
    if(lista==NULL) printf("TA VAZIAAAAAA!");
    else{
    imprime(lista);
    no *aux;
    aux = lista;
    while(aux->prox!=NULL){
        aux = aux->prox;
    }
    printf("\n", aux->valor);
    while(aux!=NULL){
        printf("%d ", aux->valor);
        aux = aux->ant;
    }
}
}


