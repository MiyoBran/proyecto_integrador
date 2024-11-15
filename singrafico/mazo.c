#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mazo.h"


// Función para inicializar una carta
void inicializarCarta(myCard *carta, Palo palo, Carta numero) {
    carta->cardType = palo;
    carta->cardNumber = numero;

    // Asignar puntaje según el número de la carta
    if (numero >= DOS && numero <= DIEZ) {
        carta->puntaje = numero + 1; // DOS vale 2, DIEZ vale 10
    } else if (numero == J || numero == Q || numero == K) {
        carta->puntaje = 10; // J, Q, K valen 10
    } else if (numero == A) {
        carta->puntaje = 1; // El AS tendrá inicialmente un valor de 1 (puede cambiar a 11 según el juego)
    }
}

// Función para inicializar el mazo completo
void inicializarMazo(myDeck *mazo) {
    int index = 0; // Índice para recorrer el mazo

    for (Palo palo = 0; palo < NUM_PALOS; palo++) {
        for (Carta numero = 0; numero < CARTAS_POR_PALO; numero++) {
            inicializarCarta(&mazo->cartas[index], palo, numero);
            index++;
        }
    }
}

// Función para imprimir una carta (para verificar el mazo)
void imprimirCarta(myCard carta) {
    const char *nombresPalos[] = {"TREBOL", "DIAMANTE", "CORAZON", "PICA"};
    const char *nombresCartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    // Validar que la carta sea válida
    if (carta.cardType < TREBOL || carta.cardType > PICA || 
        carta.cardNumber < A || carta.cardNumber > K || 
        carta.puntaje <= 0) {
        printf("Error: Carta inválida.\n");
        return;
    }

    printf("%s de %s, Puntaje: %d\n", 
        nombresCartas[carta.cardNumber], 
        nombresPalos[carta.cardType], 
        carta.puntaje);
}

// Función para imprimir el mazo completo
// Función para imprimir el mazo completo antes de barajar
void imprimirMazo(myDeck *mazo, int numCartas) {
    const char *nombresPalos[] = {"TREBOL", "DIAMANTE", "CORAZON", "PICA"};
    const char *nombresCartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    printf("Mazo completo:\n");
    for (int i = 0; i < numCartas; i++) {
        printf("%s de %s, Puntaje: %d\n", 
            nombresCartas[mazo->cartas[i].cardNumber], 
            nombresPalos[mazo->cartas[i].cardType], 
            mazo->cartas[i].puntaje);
    }
    printf("\n");
}

// Función para barajar el mazo (algoritmo Fisher-Yates)
void barajarMazo(myDeck *mazo) {
    srand(time(NULL)); // Inicializar la semilla para números aleatorios

    // Iterar desde la última carta hasta la primera
    for (int i = TAMANO_MAZO - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Elegir un índice aleatorio entre 0 e i

        // Intercambiar las cartas en las posiciones i y j
        myCard temp = mazo->cartas[i];
        mazo->cartas[i] = mazo->cartas[j];
        mazo->cartas[j] = temp;
    }
}


int pedir1carta(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador) {
    if (*indiceMazo < 0) return 0; // No quedan más cartas en el mazo
    if (*indiceJugador >= MAX_CARTAS_JUGADOR) return 0; // El jugador alcanzó su límite

    // Asignar la carta al jugador
    jugador->cartas[*indiceJugador] = mazo->cartas[*indiceMazo];
    (*indiceMazo)--;    // Reducir el índice del mazo
    (*indiceJugador)++; // Incrementar el índice del jugador
    return 1; // Carta asignada exitosamente
}

void inicializarJugador(myDeck *jugador) {
    for (int i = 0; i < MAX_CARTAS_JUGADOR; i++) {
        jugador->cartas[i].cardType = TREBOL;
        jugador->cartas[i].cardNumber = A;
        jugador->cartas[i].puntaje = 0;
    }
}
void imprimirCartasJugador(myDeck *jugador, int numCartasJugador) {
    printf("Cartas del Jugador:\n");
    for (int i = 0; i < numCartasJugador; i++) {
        imprimirCarta(jugador->cartas[i]);
    }
}
