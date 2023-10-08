#include "../include/command.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Inicializa una estructura de comando.
 * @return: Puntero a la estructura de comando inicializada.
 */
Command* init_command_struct() {
    Command* command = (Command *) malloc(sizeof(Command));
    command->subcommands = (char***)malloc(sizeof(char**) * CMD_NUM);
    for(int i = 0; i < CMD_NUM; i++) {
        command->argcs[i] = 0;
        command->is_redirected[i] = 0;
    }
    command->num_cmd = 0;
    return command;
}

/**
 * Libera la memoria ocupada por una estructura de comando.
 * @param command: Puntero a la estructura de comando.
 */
void free_command_struct(Command* command) {
    for(int i = 0; i < command->num_cmd; i++) {
        for(int j = 0; j < command->argcs[i]; j++) {
            free(command->subcommands[i][j]);
        }
        free(command->subcommands[i]);
    }
    free(command);
}

/**
 * Imprime la estructura de comando.
 * @param command: Puntero a la estructura de comando.
 */
void print_command(Command* command) {
    printf("Command:\n");
    for(int i = 0; i < command->num_cmd; i++) {
        printf("\tsub command: ");
        for(int j = 0; j < command->argcs[i]; j++) {
            printf("%s ", command->subcommands[i][j]);
        }
        printf("argc: %i, is redirected = %i",
               command->argcs[i],
               command->is_redirected[i]);
        printf("\n");
    }
    printf("\n");
}
