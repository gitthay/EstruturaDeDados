#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//auxiliares
typedef struct No{
    int valor, altura;
    struct No *esq, *dir; 
} no;

no* criarNo (int valor);
int maior (int a, int b);
int altura(no *NO);
int fb(no* No);

no* inserir(no *r, int x);
no* remover(no* arv, int v);
no* balancear(no* r);
void imprime(no* r, int nivel);

//rotacoes
no* rotesq(no* r);
no* rotdir(no* r);
no* rotduplaesq(no* r);
no* rotdupladir(no* r);
bool balanceada(no* r);

int main(){
    no *arv = NULL;

    arv = inserir(arv, 30);
    arv = inserir(arv, 40);
    arv = inserir(arv, 50);
    arv = inserir(arv, 60);
    arv = inserir(arv, 70);
    arv = inserir(arv, 80);
    arv = inserir(arv, 90);
    imprime(arv, 1);
    printf("%d", balanceada(arv));
    
}

bool balanceada(no* r){
    if (r == NULL)
        return true;
    else{
        int fb = altura(r->esq) - altura(r->dir);
        if (fb < -1 || fb > 1)
            return false;
        else
            return balanceada(r->esq) && balanceada(r->dir);
    }

}  


no* balancear(no* r){
    int Fb = fb(r);

    if(Fb < - 1 && fb(r->dir) <= 0){
        r = rotesq(r);
    }
    else if(Fb >  1 && fb(r->esq) >= 0)
        r = rotdir(r);

    else if(Fb > 1 && fb(r->esq) < 0)
        r = rotdupladir(r);

    else if(Fb < - 1 && fb(r->dir) > 0)
        r = rotduplaesq(r);
    return r;
}

no* remover(no *arv, int v){
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

                arv->esq = remover(arv->esq, v);
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
                arv->dir = remover(arv->dir, v);
            else
                arv->esq = remover(arv->esq, v);
        }

        arv->altura = maior(altura(arv->esq), altura(arv->dir)) + 1;
        arv = balancear(arv);

        return arv;
    }
}

no* inserir(no* r, int x){
    if(r == NULL){
        return criarNo(x);
    }else{
        if(x < r->valor){
            r->esq = inserir(r->esq, x);
        }else if(x > r->valor){
            r->dir = inserir(r->dir, x);
        }else{
            printf("Elemento já existe\n");
        }
    }

    return r;
}


void imprime(no* r, int nivel){
    if(r == NULL) 
        return;

    imprime(r->dir, nivel + 1);

    for(int i = 0; i < nivel; i++) printf("   ");
    printf("%d\n", r->valor);

    imprime(r->esq, nivel + 1);
}

no* rotesq(no* r){
    no *y, *f;

    y = r->dir;
    f = y->esq;

    y->esq = r;
    r->dir = f;

    r->altura = maior(altura(r->esq), altura(r->dir)) + 1;
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
    
    return y;

}

no* rotdir(no *r){
    no *y, *f;

    y = r->esq;
    f = y->dir;

    y->dir= r;
    r->esq = f;

    r->altura = maior(altura(r->esq), altura(r->dir)) + 1;
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

no* rotduplaesq(no* r){
    r->esq = rotesq(r->esq);
    return rotdir(r);
}
no* rotdupladir(no* r){
    r->dir = rotdir(r->dir);
    return rotesq(r);
}

int fb(no *No){
    if(No)
        return (altura(No->esq)-altura(No->dir));
    else 
        return 0;
}

int maior (int a, int b){
    return (a>b)? a:b;
}

int altura(no *NO){
    if(NO==NULL)
        return -1;
    else{
        return NO->altura;
    }
}


no* criarNo (int v){
    no *novo;
    novo = (no*)malloc(sizeof(no));
    novo->valor = v;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->altura = 0;

    return novo;
}