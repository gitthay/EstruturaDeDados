#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura para um nó na lista de adjacência
typedef struct vertice{
    int valor;
    int peso;
    struct vertice* prox;
} vert;

// Estrutura para representar uma lista de adjacência
typedef struct ADJ{
    vert *cab;
} adj;

// Estrutura para representar o grafo
typedef struct Grafo{
    int quant;
    adj* vetor;
} grafo;


//funcoes de lista
typedef struct NoLista {
    vert* v;
    struct NoLista* prox;
} nolista;

nolista* desenfilera(nolista **fila) {
    nolista *elem = NULL;
    if (*fila) {
        elem = *fila;
        *fila = (*fila)->prox;
        elem->prox = NULL;
    }
    return elem;
}

void inserefinal(nolista **fila, vert *v) {
    nolista *novo = malloc(sizeof(nolista));
    novo->prox = NULL;
    novo->v = v;

    if (*fila == NULL) {
        *fila = novo;
    } else {
        nolista *aux = *fila;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

nolista* desempilha(nolista **lista) {
    if (*lista == NULL)
        return NULL;

    nolista *atual = *lista;
    nolista *anterior = NULL;

    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        // Só tem um elemento
        *lista = NULL;
    } else {
        anterior->prox = NULL;
    }

    return atual; // Retorna o nó removido (último)
}

int vazio(nolista *fila) {
    return fila == NULL;
}

// Função para criar um novo nó
vert* criarno(int v){
    vert *novo = (vert*) malloc(sizeof(vert));
    novo->valor = v;
    novo->prox = NULL;
    novo->peso = 0;
    return novo;
}

// Função para criar um grafo com V vértices
grafo* criarGrafo(int v){
    grafo *novografo = malloc(sizeof(grafo));
    novografo->quant = v;
    novografo->vetor = malloc(v*sizeof(adj));

    for(int i = 0; i < v; i++)
        novografo->vetor[i].cab = NULL;

    return novografo;
}

// Imprime o grafo
void imprime(grafo* g){
    if(g){
        for(int i = 0; i<g->quant; i++){
            printf("\nGrafo %d:\n", i);
            vert* a = g->vetor[i].cab;
            while(a){
                printf("->%d", a->valor);
                a = a->prox;
            }
        }
    }
    printf("\n\n");
}


// Adiciona uma aresta ao grafo
void addaresta(grafo* g, int vert0, int vertdest, int peso){
    vert* new = criarno(vertdest);
    new->prox = g->vetor[vert0].cab;
    g->vetor[vert0].cab = new;
    new->peso = peso;

    vert *new1 = criarno(vert0);
    new1->prox = g->vetor[vertdest].cab;
    new1->peso = peso;
    g->vetor[vertdest].cab = new1;

}


// Busca em profundidade sem pilha
void auxpronfundidade(grafo* g, int i, int visita[]){
    visita[i] = 1; //grafo, inicial, vetor
    printf("%d", i);
    vert *adjacentes = g->vetor[i].cab;
    while(adjacentes){
        if(!visita[adjacentes->valor]){
            auxpronfundidade(g, adjacentes->valor, visita);
        }
        adjacentes = adjacentes->prox;
    }

}

void buscaprofunda(grafo *g, int v){
    int visita[g->quant];

    for(int i = 0; i<g->quant; i++)
        visita[i] = 0; //indicando nao visita

    for(int i = 0; i < g->quant; i++){
        if(!visita[i]){ // se ainda não foi visitado
            auxpronfundidade(g, i, visita); // inicia DFS a partir dele
        }
    
}
}

// Busca em largura
void buscaLargura(grafo *g, int inicio) {
    int visita[g->quant];
    for (int i = 0; i < g->quant; i++)
        visita[i] = 0;

    nolista *fila = NULL;

    // Marca o vértice inicial como visitado e enfileira
    visita[inicio] = 1;

    vert *vInicio = criarno(inicio);
    inserefinal(&fila, vInicio);

    while (!vazio(fila)) {
        // Desenfileira
        nolista *removido = desenfilera(&fila);
        int v = removido->v->valor;
        free(removido->v);
        free(removido);

        printf("%d ", v);

        // Para todos os adjacentes
        vert *adj = g->vetor[v].cab;
        while (adj) {
            if (!visita[adj->valor]) {
                visita[adj->valor] = 1;

                vert *novo = malloc(sizeof(vert));
                novo->valor = adj->valor;
                novo->prox = NULL;
                inserefinal(&fila, novo);
            }
            adj = adj->prox;
        }
    }
}

// Menor caminho por aresta
void buscaLarguraMenorCaminho(grafo *g, int inicio, int destino) {
    int visita[g->quant];
    int dist[g->quant];
    int pai[g->quant];

    for (int i = 0; i < g->quant; i++) {
        visita[i] = 0;
        dist[i] = -1;   // -1 indica não visitado
        pai[i] = -1;    // sem pai definido
    }

    nolista *fila = NULL;

    visita[inicio] = 1;
    dist[inicio] = 0;

    vert *vInicio = criarno(inicio);
    inserefinal(&fila, vInicio);

    while (!vazio(fila)) {
        nolista *removido = desenfilera(&fila);
        int v = removido->v->valor;
        free(removido->v);
        free(removido);

        if (v == destino)
            break; // já achou o destino, pode parar

        vert *adj = g->vetor[v].cab;
        while (adj) {
            int w = adj->valor;
            if (!visita[w]) {
                visita[w] = 1;
                dist[w] = dist[v] + 1;
                pai[w] = v;

                vert *novo = malloc(sizeof(vert));
                novo->valor = w;
                novo->prox = NULL;
                inserefinal(&fila, novo);
            }
            adj = adj->prox;
        }
    }

    // Reconstruir caminho mínimo do destino até início
    if (dist[destino] == -1) {
        printf("Não existe caminho de %d até %d\n", inicio, destino);
        return;
    }

    int caminho[g->quant];
    int tam = 0;
    int atual = destino;
    while (atual != -1) {
        caminho[tam++] = atual;
        atual = pai[atual];
    }

    printf("Menor caminho de %d até %d (distância %d): ", inicio, destino, dist[destino]);
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0)
            printf(" -> ");
    }
    printf("\n");
}

void dijkstra(grafo* g, int origem) {
    int dist[g->quant];
    int visitado[g->quant];

    for (int i = 0; i < g->quant; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
    }

    dist[origem] = 0;

    for (int i = 0; i < g->quant - 1; i++) {
        int u = -1;
        int menor = INT_MAX;

        for (int j = 0; j < g->quant; j++) {
            if (!visitado[j] && dist[j] < menor) {
                menor = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // Todos os alcançáveis já foram visitados

        visitado[u] = 1;

        vert* adj = g->vetor[u].cab;
        while (adj) {
            int v = adj->valor;
            int peso = adj->peso;
            if (!visitado[v] && dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
            adj = adj->prox;
        }
    }

    printf("Distâncias a partir do vértice %d:\n", origem);
    for (int i = 0; i < g->quant; i++) {
        if (dist[i] == INT_MAX)
            printf("%d -> INF\n", i);
        else
            printf("%d -> %d\n", i, dist[i]);
    }
}


// Função principal
int main() {
    grafo* g = criarGrafo(5);
    int cont=0;
    addaresta(g, 0, 1, 20);
    addaresta(g, 2, 1, 5);
    addaresta(g, 2, 3, 5);
    addaresta(g, 1, 4, 3);
    addaresta(g, 3, 1, 3);
    addaresta(g, 0, 2, 4);
    dijkstra(g, 0);
    return 0;
}