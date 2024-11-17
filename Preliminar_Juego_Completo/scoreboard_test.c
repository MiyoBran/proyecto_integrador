///////////////////Include para main de prueba ///////////////////

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////////////////////////////////////////

////////////////////////Funciones propias////////////////////////

#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego

/////////////////////////////////////////////////////////////////


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
    ////////////////////////Bloques Importantes en main////////////////////////
    srand(time(NULL)); // Inicializar la semilla aleatoria
    
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }

    char *scoreDB = getconfig("archivo_datos"); // obtiene nombre del archivo-base de datos del rankin
    if (scoreDB == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }
    ////////////////////////Bloques Importantes en main////////////////////////
    
    
    int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                fileImport(scoreList, scoreDB);  // Cargar el archivo de puntajes en el arreglo
                printf("Archivo Importado!\n");
                break;
            case 2:
                fileSave(scoreList, scoreDB);  // Guardar el arreglo de puntajes en el archivo
                printf("Archivo Guardado!\n");
                break;
            case 3: {
                char *nombre = generarNombreAleatorio();
                float dinero = (rand() % 9501) + 500; // Genera entre 500 y 10000

                Score nuevoJugador = crearScore(nombre, dinero); // Convierte nombre y dinero a un Score
                checkScore(scoreList, nuevoJugador, scoreDB); // Verifica y agrega el jugador
                break;
            }
            case 4:
                showRanking(scoreList, scoreDB);  // Muestra el ranking en la terminal
                break;
            
            case 5:  // Opción para borrar el archivo
            if (remove(scoreDB) == 0) {
                // sin memset, puedo mantener el arreglo en la ejecucion aunque borre el archivo
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
    free(scoreDB);

    return 0;
}
