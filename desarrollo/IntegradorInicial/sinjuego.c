#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "archivo_configuracion.h"

#define TOTAL_REGISTROS 10

typedef struct {
    int ranking;
    char name[50];
    float money;
} Jugador;

// Declaración de funciones
void importarDesdeArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void guardarEnArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void agregarJugador(Jugador scoreList[TOTAL_REGISTROS], Jugador nuevoJugador);
void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]);
void ordenarJugadores(Jugador scoreList[TOTAL_REGISTROS]);

int main() {
    srand(time(NULL));
    Jugador scoreList[TOTAL_REGISTROS] = {0}; // Lista de jugadores en el ranking
    int opcion;
    char *nombreArchivo = obtenerValorConfiguracion("archivo_datos");

    importarDesdeArchivo(scoreList, nombreArchivo);

    do {
        printf("\nMenú:\n");
        printf("1. Jugar una partida de Blackjack\n");
        printf("2. Mostrar lista de jugadores\n");
        printf("3. Terminar el programa\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            printf("Iniciando una nueva partida de Blackjack...\n");
            
            //          ****************************************************
            //          * Aquí debería ir la lógica principal del juego.   *
            //          * - Generar/usar jugadores activos                 *
            //          * - Determinar ganadores y actualizar dinero       *
            //          ****************************************************

            // Crear un jugador con datos derivados del juego
            Jugador nuevoJugador;
            strcpy(nuevoJugador.name, "Jugador"); // Reemplazar con nombre del juego
            nuevoJugador.money = 1000; // Actualizar con monto ganado/perdido

            agregarJugador(scoreList, nuevoJugador);
            guardarEnArchivo(scoreList, nombreArchivo);
            break;

        case 2:
            mostrarJugadores(scoreList);
            break;

        case 3:
            printf("Terminando el programa.\n");
            break;

        default:
            printf("Opción inválida. Inténtalo nuevamente.\n");
        }
    } while (opcion != 3);

    free(nombreArchivo);
    return 0;
}

// Función para importar datos de jugadores desde un archivo
void importarDesdeArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo no existe, se creará al guardar.\n");
        return;
    }

    fread(scoreList, sizeof(Jugador), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

// Función para guardar datos de jugadores en un archivo
void guardarEnArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(scoreList, sizeof(Jugador), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

// Función para agregar un jugador al ranking
void agregarJugador(Jugador scoreList[TOTAL_REGISTROS], Jugador nuevoJugador) {
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        // Reemplazar al último si el nuevo jugador tiene más dinero
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;
            ordenarJugadores(scoreList);
        } else {
            printf("El nuevo jugador no tiene suficiente dinero para entrar en el ranking.\n");
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
void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]) {
    printf("\nRanking\tNombre\tDinero\n");
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        }
    }
}

// Función para ordenar la lista de jugadores en función del dinero (descendente)
void ordenarJugadores(Jugador scoreList[TOTAL_REGISTROS]) {
    for (int i = 0; i < TOTAL_REGISTROS - 1; i++) {
        for (int j = 0; j < TOTAL_REGISTROS - 1 - i; j++) {
            if (scoreList[j].money < scoreList[j + 1].money) {
                Jugador temp = scoreList[j];
                scoreList[j] = scoreList[j + 1];
                scoreList[j + 1] = temp;
            }
        }
    }
}
