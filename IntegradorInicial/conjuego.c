#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "archivo_configuracion.h"

#define TOTAL_REGISTROS 10

typedef struct {
    int ranking;
    char name[50];
    float money;
} Jugador;

void importarDesdeArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void guardarEnArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void agregarJugador(Jugador scoreList[TOTAL_REGISTROS], Jugador nuevoJugador);
void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]);
Jugador crearJugador();
void ordenarJugadores(Jugador scoreList[TOTAL_REGISTROS]);

// Funciones específicas de blackjack
void iniciarJuegoBlackjack(Jugador *jugador);
int obtenerPuntajeCarta();
int calcularPuntaje(int puntajeActual, int nuevaCarta);
void determinarGanador(Jugador *jugador, int puntajeJugador, int puntajeDealer);

int main() {
    srand(time(NULL)); // Inicializa el generador de números aleatorios
    Jugador scoreList[TOTAL_REGISTROS] = {0};
    int opcion;
    char *nombreArchivo = obtenerValorConfiguracion("archivo_datos");

    importarDesdeArchivo(scoreList, nombreArchivo);

    do {
        printf("\nMenú:\n");
        printf("1. Crear un jugador\n");
        printf("2. Jugar al Blackjack\n");
        printf("3. Mostrar lista de jugadores\n");
        printf("4. Terminar el programa\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarJugador(scoreList, crearJugador());
                guardarEnArchivo(scoreList, nombreArchivo);
                break;
            case 2:
                iniciarJuegoBlackjack(&scoreList[0]); // Usa el primer jugador como ejemplo
                guardarEnArchivo(scoreList, nombreArchivo);
                break;
            case 3:
                mostrarJugadores(scoreList);
                break;
            case 4:
                printf("Terminando el programa.\n");
                break;
            default:
                printf("Opción inválida. Inténtalo nuevamente.\n");
        }
    } while (opcion != 4);

    free(nombreArchivo);
    return 0;
}

// Función para iniciar el juego de blackjack
void iniciarJuegoBlackjack(Jugador *jugador) {
    printf("\n** Iniciando juego de Blackjack para %s **\n", jugador->name);
    
    int puntajeJugador = 0;
    int puntajeDealer = obtenerPuntajeCarta() + obtenerPuntajeCarta();

    char eleccion;

    do {
        int nuevaCarta = obtenerPuntajeCarta();
        puntajeJugador = calcularPuntaje(puntajeJugador, nuevaCarta);
        printf("Tu puntaje es: %d\n", puntajeJugador);

        if (puntajeJugador > 21) {
            printf("Te pasaste de 21. Perdiste la ronda.\n");
            jugador->money -= 50; // Ejemplo: resta dinero
            return;
        }

        printf("¿Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

    } while (eleccion == 's' || eleccion == 'S');

    // Finaliza el turno y determina el ganador
    determinarGanador(jugador, puntajeJugador, puntajeDealer);
}

// Función para obtener una carta aleatoria entre 1 y 11 puntos
int obtenerPuntajeCarta() {
    return rand() % 11 + 1;
}

// Función para sumar puntaje y ajustar si el jugador tiene Ases
int calcularPuntaje(int puntajeActual, int nuevaCarta) {
    puntajeActual += nuevaCarta;
    return puntajeActual;
}

// Determina el ganador entre el jugador y el dealer
void determinarGanador(Jugador *jugador, int puntajeJugador, int puntajeDealer) {
    printf("Puntaje del dealer: %d\n", puntajeDealer);

    if (puntajeDealer > 21 || puntajeJugador > puntajeDealer) {
        printf("¡Ganaste!\n");
        jugador->money += 100; // Ejemplo: agrega dinero si gana
    } else if (puntajeJugador == puntajeDealer) {
        printf("Empate.\n");
    } else {
        printf("Perdiste contra el dealer.\n");
        jugador->money -= 50; // Ejemplo: resta dinero si pierde
    }
}

// Funciones de gestión de jugadores (importar, guardar, etc.)
void importarDesdeArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("No se encontró el archivo de registros.\n");
        return;
    }
    fread(scoreList, sizeof(Jugador), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

void guardarEnArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al guardar el archivo.\n");
        return;
    }
    fwrite(scoreList, sizeof(Jugador), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

void agregarJugador(Jugador scoreList[TOTAL_REGISTROS], Jugador nuevoJugador) {
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;
            ordenarJugadores(scoreList);
        }
    } else {
        for (int i = 0; i < TOTAL_REGISTROS; i++) {
            if (scoreList[i].money == 0) {
                scoreList[i] = nuevoJugador;
                break;
            }
        }
        ordenarJugadores(scoreList);
    }

    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            scoreList[i].ranking = i + 1;
        }
    }
}

Jugador crearJugador() {
    Jugador nuevoJugador;
    char vocales[] = {'a', 'e', 'i', 'o', 'u'};

    nuevoJugador.name[0] = 'A' + (rand() % 26);
    nuevoJugador.name[1] = vocales[rand() % 5];
    nuevoJugador.name[2] = '0' + (rand() % 10 + 1);
    nuevoJugador.name[3] = '\0';

    nuevoJugador.money = (float)(rand() % 10001);
    return nuevoJugador;
}

void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]) {
    printf("\nRanking\tNombre\tDinero\n");
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        }
    }
}

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
