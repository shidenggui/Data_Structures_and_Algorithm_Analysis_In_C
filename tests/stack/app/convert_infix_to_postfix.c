#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ASCII_RANGE_SIZE 256
#define OPERAND 0
#define OPERATOR 1
#define LEFT_PARENTHESES 2
#define RIGHT_PARENTHESES 3

#define MAX_SIZE 16
#define ETOS -1

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


Stack create_stack(int size) {
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

int is_empty(Stack s) {
    return s->top == ETOS;
}

int is_full(Stack s) {
    return s->top == s->capacity - 1;
}

void push(int value, Stack s) {
    if (is_full(s))
        error("stack is full");
    s->array[++s->top] = value;
}

int top(Stack s) {
    if (is_empty(s))
        error("stack is empty cant top");
    return s->array[s->top];
}

void pop(Stack s) {
    if (is_empty(s))
        error("stack is empty, cant pop");
    s->top--;
}

void dispose_stack(Stack s) {
    if (s == NULL)
        return;
    free(s->array);
    free(s);
}


int symbol_type[ASCII_RANGE_SIZE];
int symbol_priority[ASCII_RANGE_SIZE];

void init_symbol() {
    for (int i = 0; i < ASCII_RANGE_SIZE; i++)
        symbol_type[i] = OPERAND;

    symbol_type['+'] = OPERATOR;
    symbol_type['*'] = OPERATOR;
    symbol_type['('] = OPERATOR;
    symbol_type[')'] = RIGHT_PARENTHESES;

    symbol_priority['+'] = 0;
    symbol_priority['*'] = 1;
    symbol_priority['('] = 2;

}


int strlength(char *s) {
    int length = 0;
    while (*s != NULL) {
        s++;
        length++;
    }
    return length;
}

void print_stack(Stack s) {
    printf("stack: \n");
    printf("stack->capacity: %d stack->top: %d\n", s->capacity, s->top);
    for (int i = 0; i <= s->top; i++) {
        printf("idx: %d value: %c\n", i, s->array[i]);
    }
}

char *convert_infix_to_postfix(char *expr) {
    Stack s = create_stack(MAX_SIZE);
    char *postfix = malloc((strlength(expr) + 1) * sizeof(char));
    char *out_pointer = postfix;
    for (;*expr != NULL; expr++) {
        if (symbol_type[*expr] == OPERAND) {
            *out_pointer = *expr;
            out_pointer++;
        } else if (*expr == ')') {
            while (top(s) != '(') {
                *out_pointer = top(s);
                out_pointer++;
                pop(s);
            }
            pop(s);
        } else if(symbol_type[*expr] == OPERATOR) {
            while (!is_empty(s) && top(s) != '(' && symbol_priority[top(s)] >= symbol_priority[*expr]) {
                *(out_pointer++) = top(s);
                pop(s);
            }
            push(*expr, s);
        }
        print_stack(s);
        printf("%s\n", postfix);
    }
    while (!is_empty(s)) {
        *(out_pointer++) = top(s);
        pop(s);
    }
    *out_pointer = NULL;
    dispose_stack(s);
    return postfix;
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

int is_same_str(char *s1, char *s2) {
    while (*s1 != NULL && *s2 != NULL) {
        if (*s1 != *s2)
            return 0;
        s1++;
        s2++;
    }
    if (*s1 == NULL && *s2 == NULL)
        return 1;
    return 0;
}

void test_convert_infix_to_postfix() {
    init_symbol();
    printf("convert a+b to  %s\n", convert_infix_to_postfix("a+b"));
    assert(is_same_str(convert_infix_to_postfix("a+b"), "ab+"));
    printf("convert a+b*c to  %s\n", convert_infix_to_postfix("a+b*c"));
    assert(is_same_str(convert_infix_to_postfix("a+b*c"), "abc*+"));
    printf("convert a*b+c to  %s\n", convert_infix_to_postfix("a*b+c"));
    assert(is_same_str(convert_infix_to_postfix("a*b+c"), "ab*c+"));

    printf("convert a*(b+c) to  %s\n", convert_infix_to_postfix("a*(b+c)"));
    assert(is_same_str(convert_infix_to_postfix("a*(b+c)"), "abc+*"));
}

int main() {
    test_stack();
    test_convert_infix_to_postfix();
}
