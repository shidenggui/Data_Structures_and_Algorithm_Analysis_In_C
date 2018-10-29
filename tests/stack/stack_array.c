#define ETOS -1
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct StackRecord {
    int capacity;
    int top;
    int *array;
} StackRecord, *Stack;

void fatal_error(char *message) {
    printf("fatal error: %s\n", message);
    exit(1);
}

void error(char *message) {
    printf("error: %s\n", message);
    exit(1);
}


Stack create_stack(int max_size) {
    Stack s = malloc(sizeof(StackRecord));
    if (s == NULL)
        fatal_error("out of space");

    s->array = malloc(sizeof(int) * max_size);
    if (s->array == NULL)
        fatal_error("out of space");
    s->capacity = max_size;
    s->top = ETOS;
    return s;
}

int is_full(Stack s) {
    return s->top >= s->capacity - 1;
}

int is_empty(Stack s) {
    return s->top == ETOS;
}

void push(int value, Stack s) {
    if (is_full(s))
        error("stack is full");
    s->top++;
    s->array[s->top] = value;
}

int top(Stack s) {
    if (is_empty(s))
        error("cant get top of stack, stack is empty");
    return s->array[s->top];
}

void pop(Stack s) {
    if (is_empty(s))
        error("stack is empty");
    s->top--;
}

void depose_stack(Stack s) {
    if (s == NULL)
        return;
    free(s->array);
    free(s);
}
void print_stack(Stack s) {
    printf("stack: \n");
    printf("stack->capacity: %d stack->top: %d\n", s->capacity, s->top);
    for (int i = 0; i <= s->top; i++) {
        printf("idx: %d value: %d\n", i, s->array[i]);
    }
}


int main() {
    Stack s = create_stack(5);
    print_stack(s);
    printf("* push 0, 1 to stack\n");
    push(0, s);
    push(1, s);
    print_stack(s);
    printf("* get top of stack\n");
    assert(top(s) == 1);
    printf("* pop 1, 0 from stack\n");
    pop(s);
    assert(top(s) == 0);
    pop(s);
    depose_stack(s);
}
