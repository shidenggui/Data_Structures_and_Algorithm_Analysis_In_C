#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 16
typedef int List;
typedef int Node;

struct Node {
    char value;
    int next;
};

struct Node arr[MAX_SIZE];

void init_arr() {
    for (int i = 0; i < MAX_SIZE - 1; i++)
        arr[i].next = i + 1;
    arr[MAX_SIZE - 1].next = 0;
}

void print_arr() {
    printf("arr:\n");
    printf("idx: value: next:\n") ;
    for (int i = 0; i < MAX_SIZE; i++) 
        printf("%-4d %-6c  %-5d\n", i, arr[i].value, arr[i].next);
}

Node list_malloc() {
    Node node = arr[0].next;
    arr[0].next = arr[node].next;
    return node;
}

void list_free(Node node) {
    arr[node].next = arr[0].next;
    arr[0].next = node;
}

List make_empty_list() {
    List l = list_malloc();
    arr[l].value = 'h';
    arr[l].next = 0;
    return l;
}

void insert(char value, Node node) {
    Node new_node = list_malloc();
    arr[new_node].value = value;
    arr[new_node].next = arr[node].next;
    arr[node].next = new_node;
}

Node find_previous(char value, List l) {
    while (arr[l].next != 0 && arr[arr[l].next].value != value)
        l++;
    return l;
}

void delete(char value, List l) {
    Node prev = find_previous(value, l);
    if (arr[prev].next == 0)
        return;
    Node target = arr[prev].next;
    arr[prev].next = arr[target].next;
    list_free(target);
}

int main () {
    init_arr();
    print_arr();
    printf("malloc node\n");
    Node node = list_malloc();
    print_arr();
    printf("free node\n");
    list_free(node);
    print_arr();
    printf("make empty list\n");
    List l = make_empty_list();
    print_arr();
    printf("insert a as first element\n");
    insert('a', l);
    print_arr();
    printf("insert b as second element\n");
    insert('b', arr[l].next);
    print_arr();
    printf("delete c from list\n");
    delete('c', l);
    print_arr();
    printf("delete a from list\n");
    delete('a', l);
    print_arr();
    printf("delete b from list\n");
    delete('b', l);
    print_arr();
    printf("make empty list l2\n");
    List l2 = make_empty_list();
    print_arr();
    insert('c', l2);
    insert('b', l2);
    insert('a', l2);
    print_arr();


}
