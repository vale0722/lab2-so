#include "../include/stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Inicializa una nueva pila.
 * @param size: Tamaño de la pila.
 * @return: Puntero a la pila inicializada.
 */
Stack* init_stack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->base = (char**)malloc(sizeof(char*) * size);
    return stack;
}

/**
 * Añade un nuevo elemento a la pila.
 * @param stack: Pila a la que se añadirá el elemento.
 * @param str: Cadena a añadir.
 * @param size: Tamaño de la cadena.
 */
void __add_new_item(Stack* stack, char* str, int size) {
    char* aux = (char*) malloc(size);
    strlcpy(aux, str, size);
    stack->base[++stack->top] = aux;
}

/**
 * Empuja una nueva cadena a la pila.
 * @param stack: Pila a la que se añadirá la cadena.
 * @param str: Cadena a añadir.
 */
void push(Stack *stack, char *str) {
    size_t size = strlen(str) + 1;
    if(stack->top == -1) {
        __add_new_item(stack, str, size);
    } else if(stack->top >= 0) {
        if(strcmp(str, stack->base[stack->top]) != 0) {
            __add_new_item(stack, str, size);
        }
    }
}

/**
 * Extrae el elemento superior de la pila.
 * @param stack: Pila de la que se extraerá el elemento.
 * @return: Cadena extraída.
 */
char* pop(Stack *stack) {
    if(stack->top >= 0) {
        return stack->base[stack->top--];
    } else {
        return NULL;
    }
}

/**
 * Imprime el contenido de la pila.
 * @param s: Pila a imprimir.
 */
void printstack(Stack* s) {
    char* sep = "";
    for (int i = 0; i <= s->top; i++) {
        printf("%sitem %i: %s", sep, i, s->base[i]);
        sep = ", ";
    } 
    printf("\n");
}

/**
 * Libera la memoria ocupada por la pila.
 * @param stack: Pila a liberar.
 */
void free_stack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        free(stack->base[i]);
    }
    free(stack);
}
