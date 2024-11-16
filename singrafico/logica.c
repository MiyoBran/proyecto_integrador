
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
// Comparo resultados
bool evaluarResultado(int puntajeJugador, int puntajeCroupier) {
    if (puntajeJugador > 21) {
        return false; // Jugador se pasa
    } else if (puntajeCroupier > 21 || puntajeJugador > puntajeCroupier) {
        return true;  // Jugador gana
    } else {
        return false; // Empate o crupier gana
    }
}
// Muestra mensaje segun "como" gano o perdio
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

// Turno Jugador
void mostrarEstadoJugador(myDeck *jugador, int numCartas) {
    imprimirCartasJugador(jugador, numCartas);
    int puntaje = calcularPuntaje(jugador, numCartas);
    printf("Tu puntaje actual es: %d\n", puntaje);
}
char preguntarAccionJugador() {
    char accion;
    printf("¿Deseas otra carta? (s para sí, n para no): ");
    scanf(" %c", &accion);
    return accion;
}
bool verificarPasoDePuntaje(myDeck *jugador, int numCartas) {
    int puntaje = calcularPuntaje(jugador, numCartas);
    if (puntaje > 21) {
        printf("¡Te pasaste de 21! Fin del turno.\n");
        return true; // El jugador se pasó
    }
    return false; // El jugador no se pasó
}
bool realizarAccionJugador(char accion, myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador) {
    if (accion == 's' || accion == 'S') {
        if (!pedir1carta(mazo, jugador, indiceMazo, indiceJugador)) {
            printf("No quedan cartas en el mazo.\n");
            return false; // Fin del turno por falta de cartas
        }
    } else if (accion == 'n' || accion == 'N') {
        printf("Te plantas.\n");
        return false; // Fin del turno por decisión del jugador
    } else {
        printf("Entrada inválida. Por favor, ingresa 's' o 'n'.\n");
    }
    return true; // Continuar el turno
}
// Esta función orquesta todas las funciones auxiliares:
void turnoJugador(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador) {

    while (true) {
        mostrarEstadoJugador(jugador, *indiceJugador);

        // Verificar si el jugador se pasó
        if (verificarPasoDePuntaje(jugador, *indiceJugador)) {
            break; // Fin del turno si el puntaje supera 21
        }

        // Preguntar acción al jugador
        char accion = preguntarAccionJugador();

        // Realizar acción y decidir si continuar o terminar el turno
        if (!realizarAccionJugador(accion, mazo, jugador, indiceMazo, indiceJugador)) {
            break;
        }
    }
}


// Turno Croupier
bool debePedirCarta(int puntajeCroupier) {
    return puntajeCroupier < 17;
}

void turnoCroupier(myDeck *mazo, myDeck *croupier, int *indiceMazo, int *indiceCroupier) {

    while (true) {
        imprimirCartasJugador(croupier, *indiceCroupier);
        int puntajeCroupier = calcularPuntaje(croupier, *indiceCroupier);
        printf("Puntaje del Croupier: %d\n", puntajeCroupier);

        // Si el puntaje es 17 o más, el crupier se planta
        if (!debePedirCarta(puntajeCroupier)) {
            printf("El Croupier se planta con un puntaje de %d.\n", puntajeCroupier);
            break;
        }

        // Pedir una carta y verificar si quedan cartas en el mazo
        if (!pedir1carta(mazo, croupier, indiceMazo, indiceCroupier)) {
            printf("No quedan cartas en el mazo. Fin del turno del Croupier.\n");
            break;
        }

        // Si el puntaje supera 21, el crupier se pasa
        if (puntajeCroupier > 21) {
            printf("El Croupier se pasa de 21. Fin del turno.\n");
            break;
        }
    }
}


