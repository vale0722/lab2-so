#ifndef IO_PROMPT_H
#define IO_PROMPT_H

#include "../include/global.h"
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

#define DEFAULT_PROMPT "\033[1mwish"
#define PROMPT_SYMBOL ">\033[0m"
#define KEY_ENTER 0x000A
#define KEY_ESCAPE 0x001B

#define cursorNext(x) printf("\033[%dC", (x))
#define cursorPrev(x) printf("\033[%dD", (x))

static size_t buffer_size;
static struct termios term, old_term;

typedef struct line_buffer{
    char* line;
    int len;
    int size;
    int cursor;

}line_buffer;

enum shellkeys{
    ARROW_UP = 0x0105,
    ARROW_DOWN = 0x0106,
    ARROW_RIGHT = 0x0107,
    ARROW_LEFT = 0x0108,
    BACKSPACE = 0x0007F,
};

void prompt();
int getch(char *c, int vmin, int vtime);
int readKey();
int render_buf(line_buffer* lbuf);
void insert_char(line_buffer* lbuf, char c);
char* readline();

void output(char** data);

#endif//IO_PROMPT_H
