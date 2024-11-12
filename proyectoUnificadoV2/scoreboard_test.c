#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Includes Propios del proyecto
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env

#define MAX_LINEA 256


char *generarNombreAleatorio();
// Funcion para "contruir" un score y mandarlo a comparar
Score crearScore(const char *nombre, float dinero);



// con el ultimo cambio, ya no es necesario usar las funciones 1 y 2
void mostrarMenu() {
    printf("\n--- Menú de Opciones ---\n");
    printf("1. Cargar el archivo de puntajes\n");
    printf("2. Guardar el archivo de puntajes\n");
    printf("3. Agregar jugador aleatorio al ranking\n");
    printf("4. Imprimir el ranking en la terminal\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}



int main() {
    Score scoreList[TOTAL_REGISTROS] = {0};
    ////++++++ TIENE QUE ESTAR EN EL MAIN, nombrearchivo es un parametro que todos usan
    //// importante Obtener aca el valor del archivo de datos???? , sino cambio las funciones
    char *nombreArchivo = getconfig("archivo_datos");
    int opcion;
    
    if (nombreArchivo == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        return 1;
    }

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            //Esta opcion nos llena el arreglo aca, con lo que dice el archivo
            case 1:
                fileImport(scoreList, nombreArchivo);  // Cargar el archivo de puntajes en el arreglo
                printf("Archivo Importado!\n");
                break;
            //Esta opcion guarda en el archivo, suponiendo que hagamos un cambio por fuera de las otras funciones
            case 2:
                fileSave(scoreList, nombreArchivo);  // Guardar el arreglo de puntajes en el archivo
                printf("Archivo Guardado!\n");
                break;

            case 3: {
                // aca podriamos preguntar el nombre o usar esta funcion
                char *nombre = generarNombreAleatorio();
                float dinero = (rand() % 9501) + 500; // Genera entre 500 y 10000


                // CON ESTO CONVERTIMOS UN NOMBRE Y un monto de dinero, en la struct de chequeo de scores
                Score nuevoJugador = crearScore(nombre, dinero);
                checkScore(scoreList, nuevoJugador,nombreArchivo);
                break;
            }
            case 4:
                showRanking(scoreList, nombreArchivo);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    free(nombreArchivo);
    return 0;
}



