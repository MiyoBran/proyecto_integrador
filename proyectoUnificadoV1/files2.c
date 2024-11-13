#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "files2.h"
// #include "gamelogic.h" // para usar el main, comentar este
// #include "graphics_storage.h" /// para usar el main comentar esto

// Este main es solo para pruebas en files2.c, eventualmente se moverá a gamelogic.c
int main() {
    srand(time(NULL)); // Inicializa el generador de números aleatorios
    
    int opcion;
    /*Si uso malloc, tendria que hacer un for que recorre  el arreglo inicializando las variables, 
    o sino pueden tener cualquier cosa, */
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria dinámica y CALLOC inicializa con 0 
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1; // Termina si hay un error en la asignación
    }

    char *nombreArchivo = obtenerValorConfiguracion("archivo_datos");
    
    if (nombreArchivo == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Libera la memoria antes de salir
        return 1; // Termina si no se obtiene un archivo válido
    }

    importarDesdeArchivo(scoreList, nombreArchivo);

    /* MENU DE OPCIONES PARA PROBAR EL MANEJO DE ARCHIVOS */
    do {
        printf("\nMenú:\n");
        printf("1. Jugar una partida de Blackjack\n");
        printf("2. Mostrar lista de jugadores\n");
        printf("3. Borrar archivo de jugadores\n");
        printf("4. Borrar datos y reiniciar\n");
        printf("5. Terminar el programa\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            printf("Iniciando una nueva partida de Blackjack...\n");

            // Aquí debería ir la lógica principal del juego.

            // Crear un jugador con datos derivados del juego
            Score nuevoJugador;
            strcpy(nuevoJugador.name, "JugadorDinamico");
            nuevoJugador.money = 2000+(rand() % 10001);

            agregarJugador(scoreList, nuevoJugador);
            guardarEnArchivo(scoreList, nombreArchivo);
            break;

        case 2:
            mostrarJugadores(scoreList);
            break;

        case 3:  // Opción para borrar el archivo
            if (remove(nombreArchivo) == 0) {
                printf("Archivo borrado con éxito.\n");
            } else {
                printf("Error al borrar el archivo.\n");
            }
            break;

        case 4:
            memset(scoreList, 0, TOTAL_REGISTROS * sizeof(Score)); // Reinicia el contenido
            printf("Datos borrados y reiniciados.\n");
            break;

        case 5:
            printf("Terminando el programa.\n");
            break;

        default:
            printf("Opción inválida. Inténtalo nuevamente.\n");
        }
    } while (opcion != 5);

    free(nombreArchivo); // Libera la memoria del nombre del archivo
    free(scoreList); // Libera la memoria dinámica
    return 0;
}

// Función para importar datos de jugadores desde un archivo
void importarDesdeArchivo(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo no existe, se creará al guardar.\n");
        return;
    }

    if (fread(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo) != TOTAL_REGISTROS) {
        printf("Error al leer del archivo.\n");
    }
    fclose(archivo);
}

// Función para guardar datos de jugadores en un archivo
void guardarEnArchivo(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    if (fwrite(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo) != TOTAL_REGISTROS) {
        printf("Error al escribir en el archivo.\n");
    }
    fclose(archivo);
}

// Función para agregar un jugador al ranking
void agregarJugador(Score scoreList[TOTAL_REGISTROS], Score nuevoJugador) {
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        // Reemplazar al último si el nuevo jugador tiene más dinero
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;
            ordenarJugadores(scoreList);
        } else {
            printf("El jugador no tiene suficiente dinero para entrar en el ranking.\n");
        }
    } else {
        // Agregar el nuevo jugador al primer lugar vacío
        for (int i = 0; i < TOTAL_REGISTROS; i++) {
            if (scoreList[i].money == 0) {
                scoreList[i] = nuevoJugador;
                break;
            }
        }
        ordenarJugadores(scoreList);
    }

    // Actualizar los rankings
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            scoreList[i].ranking = i + 1;
        }
    }
}

// Función para mostrar los jugadores en el ranking
void mostrarJugadores(Score scoreList[TOTAL_REGISTROS]) {
    printf("\nRanking\tNombre\tDinero\n");
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        }
    }
}

// Función para ordenar la lista de jugadores en función del dinero (descendente) - Bubble Sort porque son pocos
void ordenarJugadores(Score scoreList[TOTAL_REGISTROS]) {
    for (int i = 0; i < TOTAL_REGISTROS - 1; i++) {
        for (int j = 0; j < TOTAL_REGISTROS - 1 - i; j++) {
            if (scoreList[j].money < scoreList[j + 1].money) {
                Score temp = scoreList[j];
                scoreList[j] = scoreList[j + 1];
                scoreList[j + 1] = temp;
            }
        }
    }
}
/*De semana 11 git materia lo que esta en el .env, se saca con esta funcion */
char* obtenerValorConfiguracion(const char *clave) {
    FILE *archivo = fopen(".env", "r"); //<- si hago un archivo txt tengo que cambiar aca el nombre
    if (archivo == NULL) {
        printf("Error al abrir el archivo de configuración.\n");
        return NULL;
    }

    char linea[MAX_LINEA];
    char *valor = NULL;

    while (fgets(linea, sizeof(linea), archivo) && valor == NULL) {
        // Verifica si la línea contiene la clave buscada
        if (strncmp(linea, clave, strlen(clave)) == 0) {
            // Busca el caracter '=' en la línea
            char *igual = strchr(linea, '=');
            if (igual != NULL) {
                // El valor está después del símbolo '='
                valor = strdup(igual + 1);
                
                // Eliminar salto de línea si lo hay
                valor[strcspn(valor, "\n")] = '\0';
            }
        }
    }

    fclose(archivo);
    return valor;
}
