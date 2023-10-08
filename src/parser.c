#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Convierte una cadena en una estructura de comando.
 * @param command: Puntero a la estructura de comando.
 * @param cmd_str: Cadena de entrada a analizar.
 */
void string_to_command(Command *command, char *cmd_str) {
    char** sub_command;
    int argc;
    int is_redirected;
    char** command_list = string_splitter(cmd_str, &command->num_cmd, NULL, "&", CMD_NUM);

    for(int i = 0; i < command->num_cmd; i++) {
        argc = 0;
        is_redirected = 0;
        sub_command = string_splitter(command_list[i], &argc, &is_redirected, " ", ARGV_NUM);
        command->subcommands[i] = sub_command;
        command->is_redirected[i] = is_redirected;
        command->argcs[i] = argc;
    }
    free(command_list);
}

/**
 * Divide una cadena en subcadenas basadas en un delimitador.
 * @param input: Cadena de entrada a dividir.
 * @param argc: Puntero al número de subcadenas resultantes.
 * @param is_redirected: Puntero a la bandera de redirección.
 * @param sep: Delimitador para dividir la cadena.
 * @param max_splits: Número máximo de divisiones.
 * @return: Array de subcadenas.
 */
char** string_splitter(char* input, int* argc, int* is_redirected, char* sep, int max_splits) {
    if(!input || !argc || !sep) return NULL;

    char** splitted_str = (char**) malloc(sizeof(char*) * max_splits);
    char* token;
    char* input_copy;
    int size = 0;
    int amount = 0;

    size = strlen(input) + 1;
    input_copy = (char*) malloc(sizeof(char) * size);
    strlcpy(input_copy, input, size);

    token = strtok(input_copy, sep);
    while(token) {
        size = strlen(token) + 1;
        if(amount < CMD_NUM) {
            splitted_str[amount] = (char*) malloc(sizeof(char) * size);
            strlcpy(splitted_str[amount], token, size);
            if(is_redirected && strcmp(splitted_str[amount], ">") == 0) {
                *is_redirected = 1;
            }
        } else {
            break;
        }
        token = strtok(NULL, sep);
        amount++;
    }
    *argc = amount;

    if(amount < max_splits) {
        splitted_str[amount] = NULL;
    }

    free(input_copy);
    return splitted_str;
}
