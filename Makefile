# Variables
CC = gcc
CFLAGS = -Wall -Wextra
OBJS = builtin.o command.o execution.o io_prompt.o main.o parser.o shell.o stack.o

# Target principal
all: wish

# Compilación del programa
wish: $(OBJS)
	$(CC) $(CFLAGS) -o wish $(OBJS)

# Reglas de compilación para cada archivo objeto
builtin.o: src/builtin.c
	$(CC) $(CFLAGS) -c src/builtin.c

command.o: src/command.c
	$(CC) $(CFLAGS) -c src/command.c

execution.o: src/execution.c
	$(CC) $(CFLAGS) -c src/execution.c

io_prompt.o: src/io_prompt.c
	$(CC) $(CFLAGS) -c src/io_prompt.c

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

parser.o: src/parser.c
	$(CC) $(CFLAGS) -c src/parser.c

shell.o: src/shell.c
	$(CC) $(CFLAGS) -c src/shell.c

stack.o: src/stack.c
	$(CC) $(CFLAGS) -c src/stack.c

# Limpieza
clean:
	rm -f *.o wish
