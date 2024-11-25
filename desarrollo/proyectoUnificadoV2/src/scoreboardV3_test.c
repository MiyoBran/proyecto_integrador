// scoreboardV3_test.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Includes propios del proyecto
#include "scoreboardV3.h"
#include "config.h"

void mostrarMenu() {
    printf("\n--- Menú de Opciones ---\n");
    printf("1. Cargar el archivo de puntajes\n");
    printf("2. Guardar el archivo de puntajes\n");
    printf("3. Agregar jugador aleatorio al ranking\n");
    printf("4. Imprimir el ranking en la terminal\n");
    printf("5. Borrar archivo de Scores Jugadores\n");
    printf("6. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    srand(time(NULL)); // Inicializar la semilla aleatoria
    
    // Asigna memoria dinámica para el arreglo de jugadores
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }

    // Obtener el nombre del archivo de configuración
    char *nombreArchivo = getconfig("archivo_datos");
    if (nombreArchivo == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }

    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Usé &scoreList para mantener el puntero doble,
                fileImport(&scoreList, nombreArchivo);  // Cargar el archivo de puntajes en el arreglo
                printf("Archivo Importado!\n");
                break;
            case 2:
                fileSave(scoreList, nombreArchivo);  // Guardar el arreglo de puntajes en el archivo
                printf("Archivo Guardado!\n");
                break;
            case 3: {
                char *nombre = generarNombreAleatorio();
                float dinero = (rand() % 9501) + 500; // Genera entre 500 y 10000
                Score nuevoJugador = crearScore(nombre, dinero); // Convierte nombre y dinero a un Score

                // También pasé &scoreList para que checkScore pueda modificar el puntero si necesita realocar
                checkScore(&scoreList, nuevoJugador, nombreArchivo); // Verifica y agrega el jugador
                break;
            }
            case 4:
                showRanking(scoreList, nombreArchivo);  // Muestra el ranking en la terminal
                break;
            
            case 5:  // Opción para borrar el archivo
                if (remove(nombreArchivo) == 0) {
                    memset(scoreList, 0, TOTAL_REGISTROS * sizeof(Score)); // Reinicia el contenido
                    printf("Datos borrados y reiniciados.\n");  
                    printf("Archivo borrado con éxito.\n");
                } else {
                    printf("Error al borrar el archivo.\n");
                }
                break;

            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    // Liberar la memoria dinámica antes de salir
    free(scoreList);
    free(nombreArchivo);

    return 0;
}