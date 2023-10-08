# Shell Personalizado

Este proyecto es una implementación simple de un shell personalizado. Proporciona funcionalidades básicas como la ejecución de comandos, redirección, y navegación por el historial.

## Características

- **Ejecución de Comandos**: El shell puede ejecutar comandos básicos y mostrar su salida.
- **Redirección**: Es posible redirigir la salida de un comando a un archivo.
- **Historial**: El shell mantiene un historial de comandos ejecutados, permitiendo al usuario navegar a través de ellos.
- **Prompt Personalizado**: El shell muestra un prompt personalizado al usuario.

## Estructura del Código

El código está organizado en varios archivos para modularizar y mantener separadas las diferentes funcionalidades:

- `builtin.c`: Contiene funciones para comandos incorporados como `exit`, `cd`, y `path`.
- `command.c`: Funciones relacionadas con la estructura y manipulación de comandos.
- `execution.c`: Funciones para la ejecución de comandos.
- `io_prompt.c`: Funciones relacionadas con la entrada/salida y la visualización del prompt.
- `main.c`: Punto de entrada principal del programa.
- `parser.c`: Funciones para analizar la entrada del usuario y convertirla en comandos.
- `shell.c`: Funciones principales del shell, incluyendo el bucle principal.
- `stack.c`: Implementación de una pila utilizada para el historial de comandos.

## Compilación y Ejecución

Para compilar el programa, se ha proporcionado un `Makefile`. Simplemente navega hasta el directorio del proyecto y ejecuta:

```bash
make
```

Esto generará un ejecutable llamado `wish`. Para ejecutar el shell, usa:

```bash
./wish
```

## Limpieza

Para eliminar los archivos objeto y el ejecutable, ejecuta:

```bash
make clean
```

## Contribuciones

Las contribuciones son bienvenidas. Si encuentras algún error o deseas agregar nuevas funcionalidades, no dudes en hacer un pull request o abrir un issue.

## Licencia

Este proyecto está bajo la licencia MIT.