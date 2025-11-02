#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *prox;
} no;

void inserefinal(no **lista, int v);
void insereinicio(no **lista, int v);
void insereordenado(no **lista, int n);

void imprime(no *lista);
void removeinicio(no **lista);
void removefinal(no **lista);

int comprimento(no *l);
no *concatena(no *l1, no *l2);
no *retira_n(no *l, int n);
no *separa(no *l, int n);
no *inverte(no *l);
no* mesclarListas(no *l1, no *l2);

int main()
{
    no *lista = NULL, *lista2 = NULL;
    inserefinal(&lista, 1);
    inserefinal(&lista, 3);
    inserefinal(&lista, 5);
    inserefinal(&lista, 7);
    inserefinal(&lista, 8);

    imprime(lista);
    imprime(lista2);
    imprime(mesclarListas(lista, lista2));
}

no* mesclarListas(no *l1, no *l2) {
    no *lista3 = NULL;
    no *atual = NULL;
    no *aux1 = l1;
    no *aux2 = l2;

    while (aux1 != NULL || aux2 != NULL) {
        if (aux1 != NULL && (aux2 == NULL || (aux2!= NULL && aux1->valor < aux2->valor) )){
            if (atual == NULL) {
                inserefinal(&lista3, aux1->valor);
                atual = lista3;
            } else if (aux1->valor != atual->valor) {
                inserefinal(&lista3, aux1->valor);
                atual = atual->prox;
            }
            aux1 = aux1->prox;
        } else {
            if ( atual == NULL) {
                inserefinal(&lista3, aux2->valor);
                atual = lista3;
            } else if (aux2 != NULL && aux2->valor != atual->valor) {
                inserefinal(&lista3, aux2->valor);
                atual = atual->prox;
            }
            aux2 = aux2->prox;
        }
    }

    return lista3;
} 

/*Implemente uma função que receba como parâmetro uma lista encadeada e inverta o encadeamento de
seus nós, retornando a lista resultante. Após a execução dessa função, cada nó da lista apontará para o
nó que originalmente era seu antecessor, e o último nó da lista passará a ser o primeiro nó da lista
invertida, conforme ilustrado a seguir*/
no *inverte(no *l)
{
    no *aux, *lista2 = NULL;

    while (l != NULL)
    {
        // guarda valor atual e o proximo
        aux = l;
        l = aux->prox;

        // insere inicio
        aux->prox = lista2;
        lista2 = aux;
    }
    return lista2;
}

/*Implemente uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, e divida
a lista em duas, de tal forma que a segunda lista comece no primeiro nó logo após a primeira ocorrência
de n na lista original.*/
no *separa(no *l, int n)
{
    no *aux, *l2 = NULL;

    aux = l;
    while (aux != NULL && aux->valor != n)
        aux = aux->prox;
    if (aux == NULL)
        printf("por aqui nao ta nao");
    else
    {
        l2 = aux->prox;
        aux->prox = NULL;
    }
    return l2;
}

/*Implemente uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, retire da
lista todas as ocorrências de n, e retorne a lista resultante.*/
no *retira_n(no *l, int n)
{
    no *aux1, *aux2;
    int flag = 1;

    while (flag == 1)
    {
        flag = 0;
        if (l != NULL && l->valor == n)
        {
            aux1 = l;
            l = l->prox;
            free(aux1);
            flag = 1;
        }
        else
        {
            aux1 = l;
            while (aux1 != NULL && aux1->prox != NULL)
            {
                if (aux1->prox->valor == n)
                {
                    aux2 = aux1->prox;
                    aux1->prox = aux2->prox;
                    free(aux2);
                    flag = 1;
                }
                else
                    aux1 = aux1->prox;
            }
        }
    }
    return l;
}

/*Implemente uma função que receba duas listas encadeadas e retorne a lista resultante da concatenação
das duas listas recebidas como parâmetro, isto é, após a concatenação, o último elemento da primeira
lista deve apontar para o primeiro elemento da segunda lista.*/
no *concatena(no *l1, no *l2)
{
    no *aux;
    aux = l1;

    if (l1 == NULL)
    {
        return l2;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = l2;
    }
    return l1;
}

/*Implemente uma função que tenha como valor de retorno o comprimento de uma lista encadeada, isto
é, calcule o número de nós de uma lista.*/

int comprimento(no *l)
{
    int cont = 0;

    while (l != NULL)
    {
        cont++;
        l = l->prox;
    }
    printf("%d", cont);
    return cont;
}

void removefinal(no **lista)
{
    no *aux1, *aux2;
    if (*lista == NULL)
        printf("Lista vazia, tu quer remover como?!");

    else
    {
        aux1 = *lista;
        while (aux1->prox != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->prox;
        }
        aux2->prox = NULL;
        free(aux1);
    }
}

void removeinicio(no **lista)
{
    no *aux;
    if (*lista == NULL)
        printf("Vo nem dizer!");
    else
    {
        aux = *lista;
        *lista = aux->prox;
        free(aux);
    }
}

void insereinicio(no **lista, int v)
{
    no *novo;
    int valor;

    novo = (no *)malloc(sizeof(no));
    novo->prox = *lista;
    novo->valor = v;

    *lista = novo;
}

void inserefinal(no **lista, int v)
{
    no *aux, *novo;
    int valor;

    novo = (no *)malloc(sizeof(no));
    novo->prox = NULL;
    novo->valor = v;

    if (*lista == NULL)
        *lista = novo;

    else
    {
        aux = *lista;
        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void insereordenado(no **lista, int n)
{
    no *novo, *aux;
    novo = malloc(sizeof(no));
    novo->valor = n;

    novo->prox = NULL;

    if (*lista == NULL)
    {
        *lista = novo;
        return;
    }

    aux = *lista;
    if (aux->valor >= n)
    {
        novo->prox = *lista;
        *lista = novo;
        return;
    }

    while (aux->prox != NULL && aux->prox->valor <= n)
    {
        aux = aux->prox;
    }

    aux->prox = novo;
    novo->prox = aux->prox;
}

void imprime(no *lista)
{
    no *aux;
    aux = lista;
    while (aux != NULL)
    {
        printf("%d ", aux->valor);
        aux = aux->prox;
    }

    printf("\n");
}
