
#include <pthread.h>        //para trabajar con hilos.
#include <stdio.h>          //la biblioteca estándar de entrada/salida.
#include <stdlib.h>         //utilidades generales.
#define NUMBER_OF_THREADS 2 // Define el número de hilos que se van a crear.
#define CANTIDAD_INICIAL_HAMBURGUESAS 20
int cantidad_restante_hamburguesas = CANTIDAD_INICIAL_HAMBURGUESAS;
int turno = 0;

void *comer_hamburguesa(void *tid) // función que no devuelve nada específico. La función toma un argumento que generalmente se usa para pasar datos al hilo,tid es el identificador del hilo.
{
    while (1 == 1) // Bucle Infinito
    {
        // el hilo actual espera su turno para acceder a la zona crítica
        while (turno != (int)tid)
            // INICIO DE LA ZONA CRÍTICA
            // La zona crítica es la sección del código donde se accede a una variable compartida por múltiples hilos
            if (cantidad_restante_hamburguesas > 0)
            { // accion dentro de zona critica
                printf("Hola! soy el hilo(comensal) %d , me voy a comer una hamburguesa ! ya que todavia queda/n %d \n", (int)tid, cantidad_restante_hamburguesas);
                cantidad_restante_hamburguesas--; // me como una hamburguesa
            }
            else
            {
                printf("SE TERMINARON LAS HAMBURGUESAS :( \n");

                pthread_exit(NULL); // forzar terminacion del hilo
            }
        // turnos + 1 pero si psasa el num de hilos se reinicia a 0
        turno = (turno + 1) % NUMBER_OF_THREADS;
        // SALIDA DE LA ZONA CRÍTICA
    }
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i, ret;

    // Bucle para crear los hilos
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        printf("Hola!, soy el hilo principal. Estoy creando el hilo %d \n", i);
        // Crear un nuevo hilo, comer_hamburgues es el nombre de la función que el hilo ejecutará una vez creado. Esto devuelve 0 si se crea correctamente sino cualquier otro tipo.
        status = pthread_create(&threads[i], NULL, comer_hamburguesa, (void *)i);

        // Verificar si la creación del hilo fue exitosa
        if (status != 0)
        {
            // Imprimir un mensaje de error si la creación del hilo falla
            printf("Algo salio mal, al crear el hilo recibi el codigo de error %d \n", status);
            exit(-1); // Terminar el programa en caso de error
        }
    }

    // Bucle para esperar la terminación de los hilos antes que termine el hilo principal
    for (i = 0; i < NUMBER_OF_THREADS; i++)
    {
        void *retval;
        // Esperar la terminación de cada hilo
        // pthread_join es una función que espera a que el hilo especificado termine su ejecución
        // threads[i], es el identificador del hilo que queremos esperar
        // &retval, es un puntero al que pthread_join escribirá el valor de retorno del hilo, puede ser clq valor, por eso es un puntero.
        ret = pthread_join(threads[i], &retval);

        // Comprobar si pthread_join fue exitoso
        if (ret != 0)
        {
            printf("Error en pthread_join: %d\n", ret);
            exit(-1); // Terminar el programa en caso de error
        }
    }

    // Finalizar el hilo principal
    pthread_exit(NULL);
}