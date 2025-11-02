#include <stdio.h>
#include <stdlib.h>
#define TAM 31

void inicializar(int t[]){
    for(int i = 0; i<TAM; i++)
        t[i] = 0;
}

int hash(int chave){
    return chave%TAM;
}
 
void inserir(int t[], int valor){
    int end = hash(valor);
    while(t[end] != 0)
        end = hash(end+1);
    t[end] = valor;
}

int buscar(int t[], int valor){
    int end = hash(valor), tentativas = 0;
    while(t[end] != 0 && tentativas < TAM){
        if(t[end]==valor)
            return end;
        else
          end = hash(end+1); 
        tentativas ++;
    }
    return -1;
}

void printaaberto(int t[]){
    for(int i = 0; i<TAM; i++)
        printf("%d = %d\n", i, t[i]);
}


int main() {
    int tabela[TAM];
    inicializar(tabela);

    inserir(tabela, 10);
    inserir(tabela, 41);  // colisão com 10
    inserir(tabela, 72);  // outra colisão com 10
    inserir(tabela, 1);
    inserir(tabela, 7);
    inserir(tabela, 31);

    printaaberto(tabela);

    int valor = 41;
    int pos = buscar(tabela, valor);
    if (pos != -1)
        printf("Valor %d encontrado na posição %d\n", valor, pos);
    else
        printf("Valor %d não encontrado.\n", valor);

    return 0;
}



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct hash_entry{
  char *key;
  void *value;
} HashEntry;

typedef struct hash_table{
  double LOAD_FACTOR;
  int capacity;
  int size;
  HashEntry **entries;
} HashTable;

HashEntry *EMPTY = NULL;

HashTable* new_hash_table();
void put(HashTable* table, char* key, void* value);
void* get(HashTable* table, char* key);
void remove_key(HashTable* table, char* key);

HashEntry* empty_entry(){
  if(EMPTY==NULL){
    EMPTY = malloc(sizeof(HashEntry)); 
    EMPTY->key = NULL; 
    EMPTY->value = NULL;
  }
  return EMPTY;
}

int str_hash(char* s, int n){
  int h=0;
  for(int i=0; i<strlen(s); i++){      
    h = 31*h + s[i];
  }    
  //função de redução
  return abs(h) % n;
}

int findPos(HashTable* table, char* key){
  int firstEmpty = -1;
  int pos = str_hash(key, table->capacity);
  
  while(table->entries[pos] != NULL && (table->entries[pos] == empty_entry() || strcmp(table->entries[pos]->key, key) != 0)){      
    if (firstEmpty == -1 && table->entries[pos]==empty_entry()) {
      firstEmpty = pos; 
    }
    // resto da divisão pela capacidade da tabela me garante que não estoura e começa do inicio a busca por um lugar vazio!
    pos = (pos + 1) % table->capacity;    
  }

  if (table->entries[pos] == NULL && firstEmpty != -1) {
    return firstEmpty;
  } 
  else {
    return pos;
  } 
}

void resize(HashTable* table) {
  HashEntry** temp = table->entries;
  int old_capacity = table->capacity;
  table->capacity = old_capacity*2;
  table->entries = calloc(table->capacity, sizeof(HashEntry*));  
  table->size = 0;
  for (int i=0; i<old_capacity; i++) {
    if (temp[i] != NULL &&  temp[i]!=empty_entry()) {
      put(table, temp[i]->key, temp[i]->value);
    }
    free(temp[i]);      
  }
  free(temp);
}

HashTable* new_hash_table(int initCapacity){
  HashTable *h = malloc(sizeof(HashTable));
  h->LOAD_FACTOR = 0.5;
  h->capacity = initCapacity;
  h->size = 0;
  h->entries = calloc(initCapacity, sizeof(HashEntry*));
  for(int i=0;i<initCapacity; i++){
    h->entries[i] = NULL;
  }
  return h;
}

void put(HashTable* table, char* key, void* value){
  int i = findPos(table, key);

  if(table->entries[i] && table->entries[i]->key){
    free(table->entries[i]);
  } 
  else {
    table->size++;
  }
  
  HashEntry *e = malloc(sizeof(HashEntry));
  e->key = key;
  e->value = value;
  table->entries[i] = e; 

  if((double)table->size/table->capacity > table->LOAD_FACTOR){
     resize(table);    
  }
}

void* get(HashTable* table, char* key){
  //to do
}

void remove_key(HashTable* table, char* key){
  //to do
}

int main(void){

  HashTable* ht = new_hash_table(10);
  
  put(ht, "dedo", "A");
  put(ht, "maria", "B");
  put(ht, "luisa", "C");
  
  assert(ht->size == 3);
  assert(ht->capacity == 10);  

  /*  
  remove_key(ht, "maria");

  assert(ht->size == 2);
  assert(ht->capacity == 10); 
  
  assert(strcmp(get(ht, "dedo"),"A")==0);
  assert(strcmp(get(ht, "luisa"),"C")==0);
  assert(get(ht, "maria")==NULL);
  
  put(ht, "maria","E");
  assert(ht->size == 3);
  assert(ht->capacity == 10);

  assert(strcmp(get(ht, "dedo"),"A")==0);
  assert(strcmp(get(ht, "luisa"),"C")==0);
  assert(strcmp(get(ht, "maria"),"E")==0);
  */

  return 0;  
}  