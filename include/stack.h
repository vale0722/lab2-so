#ifndef STACK_H
#define STACK_H

typedef struct __Stack {
    int top;
    char** base;
} Stack;

Stack* init_stack(int size);
void push(Stack* stack, char* str);
char* pop(Stack* stack);
void printstack(Stack* s);
void free_stack(Stack* stack);

#endif//STACK_H
