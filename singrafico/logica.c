
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Para manejar valores booleanos

////////////////////////Funciones propias////////////////////////

#include "mazo.h"
#include "logica.h"

///////////////////////////////////////////////////////////////////

int calcularPuntaje(myDeck *jugador, int numCartas) {
    int puntaje = 0, ases = 0;
    for (int i = 0; i < numCartas; i++) {
        int valor = jugador->cartas[i].puntaje;
        if (valor == 1) ases++;  // Contar los ases
        puntaje += valor;
    }
    // Ajustar el valor de los ases
    while (ases > 0 && puntaje + 10 <= 21) {
        puntaje += 10;
        ases--;
    }
    return puntaje;
}

bool evaluarResultado(int puntajeJugador, int puntajeCroupier) {
    if (puntajeJugador > 21) {
        return false; // Jugador se pasa
    } else if (puntajeCroupier > 21 || puntajeJugador > puntajeCroupier) {
        return true;  // Jugador gana
    } else {
        return false; // Empate o crupier gana
    }
}

void turnoJugador(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador) {
    char accion;
    do {
        imprimirCartasJugador(jugador, *indiceJugador);
        int puntaje = calcularPuntaje(jugador, *indiceJugador);
        printf("Tu puntaje actual es: %d\n", puntaje);

        // Si el puntaje supera 21, el turno termina automáticamente
        if (puntaje > 21) {
            printf("¡Te pasaste de 21! Fin del turno.\n");
            break;
        }

        // Preguntar al jugador qué desea hacer
        printf("¿Deseas otra carta? (s para sí, n para no): ");
        scanf(" %c", &accion);

        if (accion == 's' || accion == 'S') {
            if (!pedir1carta(mazo, jugador, indiceMazo, indiceJugador)) {
                printf("No quedan cartas en el mazo.\n");
                break;
            }
        } else if (accion == 'n' || accion == 'N') {
            printf("Te plantas con un puntaje de %d.\n", puntaje);
            break;
        } else {
            printf("Entrada inválida. Por favor, ingresa 's' o 'n'.\n");
        }
    } while (true);
}


void turnoCroupier(myDeck *mazo, myDeck *croupier, int *indiceMazo, int *indiceCroupier) {
    while (calcularPuntaje(croupier, *indiceCroupier) < 17) {
        if (!pedir1carta(mazo, croupier, indiceMazo, indiceCroupier)) break;
    }
}

void mostrarMensajeResultado(int puntajeJugador, int puntajeCroupier, bool jugadorGano) {
    printf("Puntaje del Jugador: %d\n", puntajeJugador);
    printf("Puntaje del Croupier: %d\n", puntajeCroupier);

    if (puntajeJugador > 21) {
        printf("Jugador se pasa. Pierde.\n");
    } else if (puntajeCroupier > 21) {
        printf("Croupier se pasa. Jugador gana.\n");
    } else if (jugadorGano) {
        printf("Jugador gana.\n");
    } else if (puntajeJugador == puntajeCroupier) {
        printf("Empate.\n");
    } else {
        printf("Croupier gana.\n");
    }
}

