#include "../include/shell.h"
#include "../include/stack.h"
#include "../include/io_prompt.h"
#include "../include/parser.h"
#include "../include/command.h"
#include "../include/execution.h"
#include "../include/builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int path_len;
char** path;
Stack* history;
int running;

/**
 * Inicializa el shell.
 */
void shell_initialization() {
    path = (char**) malloc(sizeof(char) * PATH_SIZE);
    path[0] = (char*)"/bin/";
    history = init_stack(STACK_SIZE);
    path_len = 1;
    running = -1;
}

/**
 * Bucle principal del shell.
 * @param argc: Número de argumentos.
 * @param argv: Array de argumentos.
 * @return: Estado de salida.
 */
int loop(int argc, char** argv) {
    Command* command;
    char* cmd_str = NULL;
    FILE *input = stdin;
    size_t len = 0;
    ssize_t read;

    if(argc > 2) {
        PRINT_ERROR();
        return 1;
    }
    if(argc == 2) {
        if(access(argv[1], F_OK | R_OK) == -1) {
            PRINT_ERROR();
            exit(1);
        }
        input = fopen(argv[1], "r");
        if(!input) {
            PRINT_ERROR();
        }
    }

    while(running) {
        command = init_command_struct();
        if(argc == 2) {
            read = getline(&cmd_str, &len, input);
            if(read == -1) break;
            if(cmd_str[read - 1] == '\n') cmd_str[read - 1] = '\0';
        } else {
            cmd_str = readline();
        }

        push(history, cmd_str);
        string_to_command(command, cmd_str);
        execute_command(command);

        free(cmd_str);
        cmd_str = NULL;
        free_command_struct(command);
    }

    free(path);
    free_stack(history);
    if(input != stdin) fclose(input);
    return 0;
}
