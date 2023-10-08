#ifndef EXEC_H
#define EXEC_H
#include "../include/command.h"
#include "../include/global.h"

void execute_command(Command* command);
int execute_subcommand(char** subcommand);
int execute_and_redirect_subcommand(char** subcommand, int argc);

#endif//EXEC_H
