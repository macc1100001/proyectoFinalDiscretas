#!/bin/bash

VAR1="$(md5sum -b $1 | cut -d' ' -f1)"
VAR2="$(md5sum -b $2 | cut -d' ' -f1)"

if [ $VAR1 = $VAR2 ]; then
	echo "Archivo correctamente decodificado"
else
	echo "Error"
	echo $VAR1
	echo $VAR2
fi
