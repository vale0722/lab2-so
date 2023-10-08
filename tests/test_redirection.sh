#!/bin/bash

# Ejecuta el shell y redirige la salida a un archivo
echo "ls > output.txt" | ./../wish

# Verifica si el archivo output.txt fue creado
if [ -f "output.txt" ]; then
    echo "Redirection test passed!"
    rm output.txt
else
    echo "Redirection test failed!"
fi
