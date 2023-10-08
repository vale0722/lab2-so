#include "../include/io_prompt.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

/**
 * Muestra el prompt en la consola.
 */
void prompt() {
    printf("%s%s ", DEFAULT_PROMPT, PROMPT_SYMBOL);
}

/**
 * Lee un carácter desde la entrada estándar.
 * @param c: Puntero al carácter leído.
 * @param vmin: Valor mínimo de caracteres a leer.
 * @param vtime: Tiempo máximo de espera para leer.
 * @return: El carácter leído.
 */
int getch(char *c, int vmin, int vtime) {
    int ch = 0;
    tcgetattr(0, &old_term); // Obtener la configuración inicial
    memcpy(&term, &old_term, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO); // Desactivar eco y lectura línea por línea
    term.c_cc[VMIN] = vmin;
    term.c_cc[VTIME] = vtime;
    tcsetattr(0, TCSANOW, &term);
    ch = getchar();
    *c = ch;
    tcsetattr(0, TCSANOW, &old_term);
    return ch;
}

/**
 * Lee una tecla desde la entrada estándar.
 * @return: El código de la tecla leída.
 */
int readKey() {
    int number_read;
    char ch = 0;
    number_read = getch(&ch, 1, 0);
    if(number_read == -1) return number_read;
    if(ch == KEY_ESCAPE) {
        char sequence[2];
        if(getch(&sequence[0], 1, 0) == EOF) return KEY_ESCAPE;
        if(getch(&sequence[1], 1, 0) == EOF) return KEY_ESCAPE;
        if(sequence[0] == '[') {
            switch(sequence[1]) {
                case 'A': return ARROW_UP;
                case 'B': return ARROW_DOWN;
                case 'C': return ARROW_RIGHT;
                case 'D': return ARROW_LEFT;
                default: return KEY_ESCAPE;
            }
        }
        return KEY_ESCAPE;
    } else return ch;
}

/**
 * Renderiza el buffer en la consola.
 * @param lbuf: Puntero al buffer de línea.
 * @return: Desplazamiento del cursor.
 */
int render_buf(line_buffer* lbuf) {
    int shift = 0;
    for(int i = lbuf->cursor; i <= lbuf->len; i++, shift++) {
        if(lbuf->line[i]) putchar(lbuf->line[i]);
    }
    return shift;
}

/**
 * Inserta un carácter en el buffer de línea.
 * @param lbuf: Puntero al buffer de línea.
 * @param c: Carácter a insertar.
 */
void insert_char(line_buffer* lbuf, char c) {
    if(!lbuf || lbuf->len >= lbuf->size - 1) return;

    for(int i = lbuf->len; i >= lbuf->cursor; i--) {
        lbuf->line[i + 1] = lbuf->line[i];
    }
    lbuf->len++;
    lbuf->line[lbuf->cursor] = c;
    render_buf(lbuf);
    lbuf->cursor++;
    if(lbuf->len - lbuf->cursor) cursorPrev(lbuf->len - lbuf->cursor);
}

/**
 * Elimina un carácter del buffer de línea.
 * @param lbuf: Puntero al buffer de línea.
 */
void delete_char(line_buffer *lbuf) {
    if(!lbuf || !lbuf->line || lbuf->cursor == 0) return;

    lbuf->cursor--;
    for(int i = lbuf->cursor; i < lbuf->len; i++) {
        lbuf->line[i] = lbuf->line[i + 1];
    }
    lbuf->line[lbuf->len] = ' '; 
    if(lbuf->cursor >= 0) cursorPrev(1);
    render_buf(lbuf);
    lbuf->line[lbuf->len] = '\0'; 
    if(lbuf->cursor >= 0) cursorPrev(1);
    lbuf->len--;
    if(lbuf->len - lbuf->cursor) cursorPrev(lbuf->len - lbuf->cursor);
}

/**
 * Lee una línea desde la entrada estándar.
 * @return: La línea leída.
 */
char* readline() {
    static int previous_buffer_size = 0;
    static int hist = 0;
    char* temp_char;

    // Inicialización del buffer
    line_buffer ln_buffer = {NULL, 0, INPUT_SIZE, 0};
    ln_buffer.line = (char*)malloc(sizeof(char)*INPUT_SIZE);
    memset(ln_buffer.line, 0, INPUT_SIZE);

    prompt();
    while(1) {
        int c = readKey();
        if(c == -1) {
            putchar('\n');
            free(ln_buffer.line);
            return NULL;
        } else if (c == KEY_ENTER) {
            putchar('\n');
            previous_buffer_size = ln_buffer.len;
            push(history, ln_buffer.line);
            break;
        } else if(c == ARROW_LEFT && ln_buffer.cursor) {
            ln_buffer.cursor--;
            cursorPrev(1);
        } else if(c == ARROW_RIGHT && ln_buffer.cursor < ln_buffer.len) {
            ln_buffer.cursor++;
            cursorNext(1);
        } else if (c == ARROW_UP) {
            if(previous_buffer_size != 0 && hist <= history->top){
                hist++;
                if (hist > 0){
                    int idx = history->top - hist + 1;
                    for(int i = 0; i < previous_buffer_size; i++)
                        delete_char(&ln_buffer);
                    temp_char = history->base[idx];
                    previous_buffer_size = strlen(temp_char);
                    for(int i = 0; i < previous_buffer_size; i++)
                        insert_char(&ln_buffer, temp_char[i]);
                }
            }
        }  else if (c == ARROW_DOWN){ // History down
            if(previous_buffer_size != 0 && hist >= 0){
                if(hist) hist--;
                if (hist > 0){
                    int idx = history->top - hist + 1;
                    for(int i = 0; i < previous_buffer_size; i++)
                        delete_char(&ln_buffer);
                    temp_char = history->base[idx];
                    previous_buffer_size = strlen(temp_char);
                    for(int i = 0; i < previous_buffer_size; i++)
                        insert_char(&ln_buffer, temp_char[i]);
                }
                else if (!hist) for(int i = 0; i < previous_buffer_size; i++) 
                    delete_char(&ln_buffer);
            }
        }
        else if (!iscntrl(c) && c < 128) insert_char(&ln_buffer, c);
        else if (c == BACKSPACE) delete_char(&ln_buffer);
    }
    return ln_buffer.line;
}
