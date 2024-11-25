#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////

#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas


/////////////////////////////////////////////////////////////////////////////////////

// Inicializa una carta con su palo, número y puntaje correspondiente.
void inicializarCarta(myCard *carta, Palo palo, Carta numero) {
    carta->cardType = palo;  // Asigna el palo de la carta (corazones, diamantes, tréboles, picas).
    carta->cardNumber = numero;  // Asigna el número o figura de la carta.

    // Asigna el puntaje basado en el número de la carta
    if (numero >= DOS && numero <= DIEZ) {
        carta->puntaje = numero + 1; // Las cartas del 2 al 10 valen su valor numérico (DOS vale 2, DIEZ vale 10).
    } else if (numero == J || numero == Q || numero == K) {
        carta->puntaje = 10; // Las cartas J, Q, K valen 10 puntos.
    } else if (numero == A) {
        carta->puntaje = 1; // El AS se inicializa con un valor de 1 (puede cambiar a 11 según las reglas del juego).
    }
}

// Inicializa el mazo de cartas con 52 cartas (13 por cada uno de los 4 palos).
void inicializarMazo(myDeck *mazo) {
    int indice = 0;  // Índice para acceder a las posiciones del mazo

    // Recorrer todos los palos (trebol, diamante, corazón, pica)
    for (int palo = TREBOL; palo <= PICA; palo++) {
        // Recorrer los números de las cartas (A, 2, 3, ..., K)
        for (int numero = A; numero <= K; numero++) {
            mazo->cartas[indice].cardType = palo;  // Asigna el palo de la carta (TREBOL, DIAMANTE, etc.)
            mazo->cartas[indice].cardNumber = numero;  // Asigna el número o figura de la carta

            // Asignación del puntaje basado en el número de la carta
            if (numero == A) {
                mazo->cartas[indice].puntaje = 1;  // El As se inicializa con un valor de 1 (puede cambiar a 11 más adelante)
            } else if (numero >= J) {
                mazo->cartas[indice].puntaje = 10;  // Las cartas J, Q, K valen 10 puntos
            } else {
                mazo->cartas[indice].puntaje = numero + 1;  // Las cartas numeradas 2-10 valen su valor numérico (2 vale 2, 10 vale 10)
            }

            indice++;  // Avanza al siguiente índice del mazo
        }
    }
}


// Función para imprimir una carta con su nombre, palo y puntaje
void imprimirCarta(myCard carta) {
    // Arreglos de nombres para los palos y las cartas
    const char *nombresPalos[] = {"TREBOL", "DIAMANTE", "CORAZON", "PICA"};
    const char *nombresCartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    // Validar que los valores de la carta sean correctos
    if (carta.cardType < TREBOL || carta.cardType > PICA || 
        carta.cardNumber < A || carta.cardNumber > K || 
        carta.puntaje <= 0) {
        printf("Error: Carta inválida.\n");
        return;  // Termina la ejecución si la carta no es válida
    }

    // Imprimir la carta en formato: "Número de carta de Palo, Puntaje: X"
    printf("%s de %s, Puntaje: %d\n", 
        nombresCartas[carta.cardNumber],  // Nombre de la carta (A, 2, 3, ..., K)
        nombresPalos[carta.cardType],     // Nombre del palo (TREBOL, DIAMANTE, CORAZON, PICA)
        carta.puntaje);                   // Puntaje de la carta (según reglas del juego)
}


// Función de depuración para imprimir el mazo completo
void imprimirMazo(myDeck *mazo, int numCartas) {
    // Arreglos que contienen los nombres de los palos y las cartas
    const char *nombresPalos[] = {"TREBOL", "DIAMANTE", "CORAZON", "PICA"};
    const char *nombresCartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    // Imprimir el encabezado del mazo
    printf("Mazo completo:\n");
    
    // Iterar sobre cada carta del mazo e imprimir sus detalles
    for (int i = 0; i < numCartas; i++) {
        // Mostrar la carta en el formato: "Número de carta de Palo, Puntaje: X"
        printf("%s de %s, Puntaje: %d\n", 
            nombresCartas[mazo->cartas[i].cardNumber],  // Nombre de la carta (A, 2, 3, ..., K)
            nombresPalos[mazo->cartas[i].cardType],     // Nombre del palo (TREBOL, DIAMANTE, CORAZON, PICA)
            mazo->cartas[i].puntaje);                   // Puntaje de la carta (según reglas del juego)
    }
    
    // Nueva línea para separar la salida del mazo
    printf("\n");
}


// Función para barajar el mazo (algoritmo Fisher-Yates)
void barajarMazo(myDeck *mazo) {
    srand(time(NULL)); // Inicializar la semilla para números aleatorios

    // Iterar desde la última carta hasta la primera
    for (int i = TAMANO_MAZO - 1; i > 0; i--) {
        // Elegir un índice aleatorio entre 0 e i (inclusive)
        int j = rand() % (i + 1);

        // Intercambiar las cartas en las posiciones i y j
        myCard temp = mazo->cartas[i];  // Guardar la carta en la posición i en una variable temporal
        mazo->cartas[i] = mazo->cartas[j];  // Colocar la carta en la posición j en la posición i
        mazo->cartas[j] = temp;  // Colocar la carta almacenada en la variable temporal en la posición j
    }
}

// Función para pedir una carta del mazo y asignársela al jugador.
// La función verifica si hay cartas disponibles en el mazo y si el jugador
// no ha alcanzado su límite de cartas. Si ambas condiciones son válidas,
// la carta se asigna al jugador y se valida su puntaje. Si algo sale mal,
// se retorna 0 para indicar error, de lo contrario, se retorna 1 para 
// indicar que la carta fue asignada correctamente.
int pedir1carta(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador) {
    if (*indiceMazo < 0) {
        return 0; // No quedan más cartas en el mazo
    }
    if (*indiceJugador >= MAX_CARTAS_JUGADOR) {
        return 0; // El jugador alcanzó su límite
    }
    
    // Asignar la carta del mazo al jugador
    jugador->cartas[*indiceJugador] = mazo->cartas[*indiceMazo];

    // Reducir el índice del mazo y aumentar el índice del jugador
    (*indiceMazo)--;    // Reducir el índice del mazo
    (*indiceJugador)++; // Incrementar el índice del jugador

    // Validar puntaje de la carta (evitar errores en el mazo)
    int puntajeCarta = jugador->cartas[*indiceJugador - 1].puntaje;
    if (puntajeCarta < 1 || puntajeCarta > 10) {
        printf("Error: Carta con puntaje inválido (%d).\n", puntajeCarta);
        return 0; // Retorna 0 para indicar error
    }

    return 1; // Carta asignada exitosamente
}

// Función para inicializar el mazo de un jugador con valores predeterminados
// Esta función asigna valores iniciales a las cartas del mazo del jugador.
// Cada carta se inicializa con un palo (TREBOL), un número de carta (A) y un puntaje de 0,
// lo que prepara el mazo para ser llenado con cartas válidas en el transcurso del juego.
// Los valores asignados son temporales y serán modificados conforme avance el juego.
void inicializarMazoJugador(myDeck *jugador) {
    // Iterar sobre todas las cartas en el mazo del jugador
    for (int i = 0; i < MAX_CARTAS_JUGADOR; i++) {
        // Asignar el palo TREBOL (primer valor en el enum de palos)
        jugador->cartas[i].cardType = TREBOL;
        // Asignar el número de carta A (As)
        jugador->cartas[i].cardNumber = A;
        // Asignar puntaje 0 a cada carta (será asignado más tarde)
        jugador->cartas[i].puntaje = 0;
    }
}
// Función para imprimir las cartas de un jugador
// Recibe un puntero a la estructura myDeck del jugador y el número de cartas que tiene
void imprimirCartasJugador(myDeck *jugador, int numCartasJugador) {
    // Recorre el arreglo de cartas del jugador e imprime cada carta
    for (int i = 0; i < numCartasJugador; i++) {
        // Llama a la función imprimirCarta para mostrar la carta actual del jugador
        imprimirCarta(jugador->cartas[i]);
    }
}