#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifndef _Stack_h

struct Node;
//typedef struct Node *ptr_to_node;
//typedef ptr_to_node Stack;

typedef struct Node {
    int value;
    struct Node *next;
} Node, *Stack;

int is_empty(Stack s);
Stack create_stack();
void dispose_stack(Stack s);
void make_empty(Stack s);
void push(int x, Stack s);
int top(Stack s);
int pop(Stack s);

#endif

int is_empty(Stack s) {
    return s->next == NULL;
}

Stack create_stack() {
    Stack s = malloc(sizeof(Node));
    s->next = NULL;
    return s;
}

void push(int value, Stack s) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = s->next;
    s->next = node;
}

void print_stack(Stack s) {
    printf("inverse print stack: \n");
    while (s != NULL) {
        printf("{.value=%d .next=%x}\n", s->value, s->next);
        s = s->next;
    }
}

int top(Stack s) {
    if (s->next == NULL)
        return 0;
    return s->next->value;
}

int pop(Stack s) {
    if (s->next == NULL)
        return 0;
    Node *target = s->next;
    s->next = target->next;
    int value = target->value;
    free(target);
    return value;
}

int main() {
    Stack s = create_stack();
    assert(is_empty(s) == 1);
    printf("print empty stack\n");
    print_stack(s);
    printf("push 1 to stack\n");
    push(1, s);
    print_stack(s);
    printf("get top of stack\n");
    printf("%d\n", top(s));
    assert(top(s) == 1);
    printf("pop 1 from stack and push 2, 3, then pop 3 from stack\n");
    int pop_value = pop(s);
    assert(pop_value == 1);
    push(2, s);
    push(3, s);
    pop_value = pop(s);
    assert(pop_value == 3);
    print_stack(s);
}
