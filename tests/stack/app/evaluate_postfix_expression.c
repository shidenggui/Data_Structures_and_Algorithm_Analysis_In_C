#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define MAX_SIZE 16
#define ETOS -1

typedef struct StackRecord {
    int capacity;
    int top;
    int *array;
} *Stack, StackRecord;

void fatal_error(char * message) {
    printf("fatal error %s\n", message);
    exit(1);
}

void error(char * message) {
    printf("error %s\n", message);
    exit(1);
}

Stack create_stack(int size)  {
    Stack s = malloc(sizeof(StackRecord));
    if (s == NULL)
        fatal_error("out of space");
    s->array = malloc(sizeof(int) * size);
    if (s->array == NULL)
        fatal_error("out of space");
    s->capacity = size;
    s->top = ETOS;
    return s;
}

int is_full(Stack s) {
    return s->top == s->capacity - 1;
}

int is_empty(Stack s) {
    return s->top == ETOS;
}

void push(int value, Stack s) {
    if (is_full(s)) 
        error("stack is full");
    s->array[++s->top] = value;
}

void pop(Stack s) {
    if (is_empty(s))
        error("stack is empty, cant pop");
    s->top--;
}

int top(Stack s) {
    if (is_empty(s))
        error("stack is empty, cant top");
    return s->array[s->top];
}


void print_stack(Stack s) {
    printf("stack: \n");
    printf("stack->capacity: %d stack->top: %d\n", s->capacity, s->top);
    for (int i = 0; i <= s->top; i++) {
        printf("idx: %d value: %d\n", i, s->array[i]);
    }
}

int evaluate_postfix_expression(char *exp) {
    Stack s = create_stack(MAX_SIZE);
    for (;*exp != NULL; exp++) {
        if (*exp == '+' || *exp == '*') {
            int value1 = top(s);
            pop(s);
            int value2 = top(s);
            pop(s);
            int result = 0;
            if (*exp == '+')
                result = value1 + value2;
            else
                result = value1 * value2;
            push(result, s);
        }
        else
            push(*exp - '0', s);
    }
    return top(s);
}


void test_stack() {
    Stack s = create_stack(5);
    printf("* push 0, 1 to stack\n");
    push(0, s);
    push(1, s);
    printf("* get top of stack\n");
    assert(top(s) == 1);
    printf("* pop 1, 0 from stack\n");
    pop(s);
    assert(top(s) == 0);
    pop(s);
    printf("test stack success\n");
}

void test_evaluate_postfix_expression() {
    assert(evaluate_postfix_expression("34+") == 7);
    assert(evaluate_postfix_expression("78*") == 56);
    assert(evaluate_postfix_expression("10+7*") == 7);
    assert(evaluate_postfix_expression("6523+8*+3+*") == 288);
}

int main() {
    test_stack();
    test_evaluate_postfix_expression();
}
