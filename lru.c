#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_CACHE 10
#define MAX_SIZE_HASH 20

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    unsigned int pageNumber;
    int val;
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

    int (*get)(struct LRUCache *, int);
    void (*put)(struct LRUCache *, int, int);
} LRUCache;


void enqueue(LRUCache *cache, Node *page){
    if(cache->size == 0){
        cache->head = page;
        cache->tail = page;
        cache->size ++;
        cache->hashTable->table[page->pageNumber] = page;
        return;
    }
    cache->tail->next = page;
    page->prev = cache->tail;
    cache->tail = page;
    cache->size ++;
    cache->hashTable->table[page->pageNumber] = page;
    return;
}

void dequeue(LRUCache *cache){
    if(cache->size == 0) return;
    if(cache->size == 1){
        cache->hashTable->table[cache->head->pageNumber] = NULL;
        free(cache->head);
        cache->head = NULL;
        cache->tail = NULL;
        cache->size --;
        return;
    }
    Node *curr = cache->head;
    cache->hashTable->table[curr->pageNumber] = NULL;
    cache->head = curr->next;
    free(curr);
    cache->size --;
    return;
}

int get(LRUCache *cache, int pageNum){
    Node *curr = cache->hashTable->table[pageNum];
    if(curr == NULL){
        return -1;
    }
    
    Node *prev = curr->prev;
    Node *next = curr->next;

    if(next != NULL && prev != NULL){
        prev->next = next;
        next->prev = prev;
        cache->tail->next = curr;
        curr->prev = cache->tail;
        cache->tail = curr;
    }
    return curr->val;
}

void put(LRUCache *cache, int pageNum, int val){
    Node *curr = cache->hashTable->table[pageNum];
    if(curr == NULL){
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->pageNumber = pageNum;
        newNode->val = val;
        newNode->prev = NULL;
        newNode->next = NULL;
        enqueue(cache, newNode);

        if(cache->size > cache->capacity){
            dequeue(cache);
        }
    }
    else{
        curr->val = val;
        Node *prev = curr->prev;
        Node *next = curr->next;
        prev->next = next;
        next->prev = prev;
        cache->tail->next = curr;
        curr->prev = cache->tail;
        cache->tail = curr;
    }
}

LRUCache* createCache(){
    LRUCache* cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->head = NULL;
    cache->tail = NULL;
    cache->capacity = MAX_SIZE_CACHE;
    cache->size = 0;

    Hash *hash = (Hash *)malloc(sizeof(Hash));
    hash->capacity = MAX_SIZE_HASH;
    hash->table = (Node **)malloc(sizeof(Node *));
    for(int i = 0; i < hash->capacity; i++) hash->table[i] = NULL;
    cache->hashTable = hash;

    cache->get = get;
    cache->put = put;

    return cache;
}

int main(){
    LRUCache *cache = createCache();
    cache->put(cache, 1, 2);
    printf("%d", cache->get(cache, 1));
}
