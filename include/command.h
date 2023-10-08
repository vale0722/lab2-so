#ifndef COMMAND_H
#define COMMAND_H

#include "../include/global.h"

/*
 *Struct which represents the command struct with its argv and pipelines.
 */
typedef struct __Command_struct{
    int num_cmd; //num of commands
    int argcs[CMD_NUM]; //num of args of each command
    int is_redirected[CMD_NUM]; //num of args of each command
    char*** subcommands;//List of the argv of each command
} Command;

Command* init_command_struct();
void print_command(Command* command);
void free_command_struct(Command* command);


#endif//COMMAND_H
