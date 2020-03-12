#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  *h = (HashTable*) malloc(sizeof(HashTable));
    (*h)->size = size;
    (*h)->hashFunction = f;
    (*h)->elements = (Element**) malloc(sizeof(Element*)*size);
    for(int i = 0; i < size; i++) {
      (*h)->elements[i] = NULL;
    }
}

int exists(HashTable *hashTable, Key key) {
  int hash_index = hashTable->hashFunction(key, hashTable->size);
  if(hashTable->elements[hash_index] == NULL)
    return 0;
  else {
    Element* elem = hashTable->elements[hash_index];
    while(elem != NULL) {
      if(!strcmp(elem->key,key))
        return 1;
      elem = elem->next;
    }
  }
  return 0;
}

Value get(HashTable *hashTable, Key key) {
  int index = hashTable->hashFunction(key, hashTable->size);
  Element* elems = hashTable->elements[index];
  while (elems != NULL) {
    if (strcmp(elems->key, key) == 0)
      return elems->value;
    elems = elems->next;
    }
    return 0;
}

void put(HashTable *hashTable, Key key, Value value) {
  if(exists(hashTable,key)){
    int hash_index = hashTable->hashFunction(key, hashTable->size);
    Element* elem = hashTable->elements[hash_index];
    while(elem != NULL) {
      if(!strcmp(elem->key,key)){
         elem->value = value;
         break;
      }
      elem = elem->next;
    }
  } else {
    Element* new_elem;
    new_elem = (Element*) malloc(sizeof(Element));
    new_elem->key = strdup(key);
    new_elem->value = value;
    int hash_index = hashTable->hashFunction(key, hashTable->size);
    new_elem->next = hashTable->elements[hash_index];
    hashTable->elements[hash_index] = new_elem;
  }
}

void deleteKey(HashTable *hashTable, Key key) {
  int index = hashTable->hashFunction(key, hashTable->size);
  if (exists(hashTable, key)){
    Element *aux = hashTable->elements[index];
    if (strcmp(aux->key, key) == 0){
      Element *del = aux;
      aux = aux->next;
      free(del);
      return;
    }
    while (aux->next){
      if (strcmp(aux->next->key, key) == 0) 
        break;
      aux = aux->next;
    }
    if (aux) {
      Element *del = aux;
      aux->next = del->next;
      free(del);
    }
  }
}

void print(HashTable *hashTable) {
  int i;
  for(i = 0; i < hashTable->size; i++){
    if (hashTable->elements[i] != NULL)
      printf("%d:\n", i);
    Element *aux = hashTable->elements[i];
    while (aux){
      printf("   %s:%d\n", aux->key, aux->value);
      aux = aux->next;
    }
  }
}

void freeHashTable(HashTable *hashTable) {
  Element *elem, *prev;
  for(int i = 0; i < hashTable->size; i++) {
    elem = hashTable->elements[i];
    while(elem != NULL) {
      prev = elem;
      elem = elem->next;
      free(prev);
    }
  }
  free(hashTable->elements);
  free(hashTable);
}


long hash1(Key word, long size) {
  int  i;
  long h = 0;
  int w_length = strlen(word);
  for(i = 0; i < w_length - 1; i++) {
    h = h * 17 + word[i];
  }
  return h % size;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable, *hashTable2;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common;
  int i;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);
  initHashTable(&hashTable2, hashSize, &hash1);
  //Cerinta 3
  while (fscanf(f1, "%s", word) != EOF) {
    Value val = get(hashTable, word);
    put(hashTable, word, val + 1);
  }
  print(hashTable);

  while (fscanf(f2, "%s", word) != EOF) {
   Value val = get(hashTable2, word);
   put(hashTable2, word, val + 1);
  }

  common = 0;
  for (i = 0; i < hashTable->size; i++) {
    Element* aux = hashTable->elements[i];
    while (aux) {
      Value aux_val = get(hashTable2, aux->key);
      if (aux->value >= aux_val) {
        common += aux_val;
      } else {
        common += aux->value;
      }
      aux = aux->next;
    }  
  }
   // Cerinta 4
   printf("Common words: %ld\n", common);

   fclose(f1);
   fclose(f2);
   return 0;
 }