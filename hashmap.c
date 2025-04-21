#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    if (map == NULL || key == NULL) return;

    long hashs = hash(key, map->capacity);
    long disponible = -1;
    int keyEncontrado = 0;

    for (int i = 0; i < map->capacity; i++) {
        long pos = (hashs + i) % map->capacity;
        Pair *current = map->buckets[pos];
        if (current == NULL) 
        {
            if (disponible == -1)
            { 
                disponible = pos;
            }
            break;
        }
        else if (current->key == NULL) 
        {
            if (disponible == -1)
            { 
                disponible = pos;
            }
        } 
        else if (is_equal(current->key, key)) 
        {
            keyEncontrado = 1;
            break;
        }
    }
    if (keyEncontrado) return;
    if (disponible == -1) return;

    Pair *existing = map->buckets[disponible];
    if (existing != NULL) {
        free(existing);
    }
    Pair *newPair = createPair(key, value);
    map->buckets[disponible] = newPair;
    map->size++;
    map->current = disponible;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap* map = (HashMap *)malloc(sizeof(HashMap));
    if (map == NULL)
    {
        printf("Error en la asignacion de memoria");
        return NULL;
    }
    map->buckets = (Pair **) calloc (capacity,sizeof(Pair *));
    if(map->buckets == NULL)
    {
        printf("Error en la asignacion de memoria");
        return NULL;
    }
    map->capacity = capacity;
    map->current = -1;
    map->size = 0;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
