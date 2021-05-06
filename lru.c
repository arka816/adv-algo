#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_CACHE 10
#define MAX_SIZE_HASH 20

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    unsigned int pageNumber;
    void *val;
} Node;

typedef struct Hash{
    int capacity;
    Node **table;
} Hash;

typedef struct LRUCache{
    Node *head;
    Node *tail;
    Hash *hashTable;
    int capacity;
    int size;
} LRUCache;

LRUCache* createCache(){
    LRUCache* cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->head = NULL;
    cache->tail = NULL;
    cache->capacity = MAX_SIZE_CACHE;

    Hash *hash = (Hash *)malloc(sizeof(Hash));
    hash->capacity = MAX_SIZE_HASH;
    hash->table = (Node **)malloc(sizeof(Node *));
    for(int i = 0; i < hash->capacity; i++) hash->table[i] = NULL;
    cache->hashTable = hash;

    return cache;
}

void * get(LRUCache *cache, int pageNum){
    Node *curr = cache->hashTable->table[pageNum];
    if(curr == NULL) return -1;
    Node *prev = curr->prev;
    Node *next = curr->next;
    if(next != NULL){
        prev->next = next;
        next->prev = prev;
        cache->tail->next = curr;
        curr->prev = cache->tail;
        cache->tail = curr;
    }
    return curr->val;
}

void put(LRUCache *cache, int pageNum, void *val){
    Node *curr = cache->hashTable->table[pageNum];
    if(curr == NULL){
        
    }
}

int main(){
    LRUCache *cache = createCache();

}
