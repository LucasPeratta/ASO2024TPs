#!/bin/bash

echo "Ingrese un nombre:"
read nombre

url="https://api.genderize.io/?name=${nombre}"

response=$(curl -s "$url")

echo "Respuesta de la API:"
echo "$response"

genero=$(echo "$response" | jq -r '.gender')

case "$genero" in
    "male")
        genero="masculino"
        ;;
    "female")
        genero="femenino"
        ;;
    *)
        genero="desconocido"
        ;;
esac

echo "El género asociado al nombre \"$nombre\" es: $genero"
