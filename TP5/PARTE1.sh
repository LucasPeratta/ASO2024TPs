#!/bin/bash

function generar_numero_aleatorio {
    echo $((1 + RANDOM % 100))
}

function jugar_adivina_numero {
    local numero_secreto=$(generar_numero_aleatorio)
    local intentos_realizados=0
    
    echo "¡Bienvenido al juego deadivinar el numero!"
    echo "Intenta adivinar el numero secreto entre 1 y 100."

    while true; do
        echo -n "Introduce tu intento: "
        read intento
        
        if ! [[ $intento =~ ^[0-9]+$ ]]; then
            echo "Por favor, introduce un número válido."
            continue
        fi
        
        if [ $intento -lt $numero_secreto ]; then
            echo "El número es más alto. Intenta de nuevo."
        elif [ $intento -gt $numero_secreto ]; then
            echo "El número es más bajo. Intenta de nuevo."
        else
            echo "¡Felicidades! ¡Has adivinado el número $numero_secreto en $((intentos_realizados+1)) intentos!"
            return
        fi
        
        intentos_realizados=$((intentos_realizados + 1))
    done
}

jugar_adivina_numero
