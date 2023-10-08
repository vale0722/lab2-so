#include <stdio.h>
#include "../include/shell.h"

/**
 * Función principal del programa.
 * @param argc: Número de argumentos.
 * @param argv: Array de argumentos.
 * @return: Estado de salida.
 */
int main(int argc, char** argv) {
    int state = 0;
    shell_initialization();
    state = loop(argc, argv);
    return state;
}
