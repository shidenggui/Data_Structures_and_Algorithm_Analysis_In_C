#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct Node {
    int value;
    struct Node *next;
} Node, *List;

List create_list() {
    List list = malloc(sizeof(Node));
    if (list == NULL)
        fatal_error("out of space");
    list->next = NULL;
    return list;
}

void free_list(List l) {
    if (l == NULL)
        fatal_error("out of space");
    while (l != NULL) {
        Node *temp = l;
        l = l->next;
        free(temp);
    }
}

void list_insert(int value, Node *prev) {
    Node *inserted = malloc(sizeof(Node));
    if (inserted == NULL)
        fatal_error("out of space");
    inserted->value = value;
    inserted->next = prev->next;
    prev->next = inserted;
}

Node *list_find(int value, List l) {
    l = l->next;
    while (l != NULL && l->value != value)
        l = l->next;
    return l;
}

void print_list(List l) {
    l = l->next;
    printf("H->");
    while (l != NULL) {
        printf("%d->", l->value);
        l = l->next;
    }
    printf("NULL");
}


typedef struct HashTableRecord {
    List *lists;
    int capacity;
} HashTableRecord, *HashTable;

HashTable create_hashtable(int size) {
    HashTable hashtable = malloc(sizeof(HashTableRecord));
    if (hashtable == NULL)
        fatal_error("out of space");
    hashtable->lists = malloc(sizeof(List) * size);
    if (hashtable->lists == NULL)
        fatal_error("out of space");
    for (int i = 0; i < size; i++) 
        hashtable->lists[i] = create_list();
    hashtable->capacity = size;
    return hashtable;
}

void free_hashtable(HashTable hashtable) {
    if (hashtable == NULL)
        return;
    for (int i = 0; i < hashtable->capacity; i++)
        free_list(hashtable->lists[i]);
    free(hashtable->lists);
    free(hashtable);
}

int hash(int value, int capacity) {
    return value % capacity;
}

void insert(int value, HashTable hashtable) {
    int key = hash(value, hashtable->capacity);
    Node *exist = list_find(value, hashtable->lists[key]);
    if (exist == NULL)
        list_insert(value, hashtable->lists[key]);
}

Node *find(int value, HashTable hashtable) {
    int key = hash(value, hashtable->capacity);
    return list_find(value, hashtable->lists[key]);
}

void print_hashtable(HashTable hashtable) {
    printf("HashTable: \n");
    for (int i = 0; i < hashtable->capacity; i++) {
        printf("key: %d list: ", i);
        print_list(hashtable->lists[i]);
        printf("\n");
    }
}

void test_hashtable() {
    HashTable table = create_hashtable(10);
    insert(1, table);
    insert(1, table);
    insert(2, table);
    insert(11, table);
    print_hashtable(table);
    free_hashtable(table);
}


int main() {
    test_hashtable();
}


