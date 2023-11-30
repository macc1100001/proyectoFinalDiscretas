#!/bin/bash

# El primer argumento del script es el nombre del archivo del cual se van a calcular las frecuencias
# la expresion regular en el comando 'sed' separa todo el texto en lineas de 1 caracter
cat $1 | sed -E 's/(.)/\1\n/g' | sort | uniq -c	| column

