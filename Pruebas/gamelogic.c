#include<time.h>
#include <stdbool.h>

#include "gamelogic.h" // Incluye las estructuras y enumeraciones definidas

// Aquí se inicializa el mazo y el jugador con dinero inicial.
void inicializarMazo(myDeck *mazo) {
    int indice = 0;
    for (int i = 0; i < 4; i++) { // 4 palos
        for (int j = 0; j < 13; j++) { // 13 valores por palo
            mazo[indice].cardType = i; 
            mazo[indice].cardNumber = j; 
            mazo[indice].puntaje = (j + 1); // Asignar puntaje (1-13)
            if (j == 0) mazo[indice].puntaje = 1; // As = 1 por defecto, pero podría ser 11
            if (j >= 10) mazo[indice].puntaje = 10; // J, Q, K = 10
            indice++;
        }
    }
}

// Mezcla el mazo de cartas
void mezclarMazo(myDeck *mazo) {
    srand((unsigned int)time(NULL)); // Asegura aleatoriedad en cada ejecución
    for (int i = TOTAL_CARTAS - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Intercambia posiciones
        myDeck temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

// Inicializa las estructuras de jugadores y los índices
void inicializarIndicesYEstructuras(Jugador *jugador, Jugador *croupier, int *indiceJugador, int *indiceCroupier) {
    *indiceJugador = 0;
    *indiceCroupier = TOTAL_CARTAS - 1;

    jugador->numCartas = 0;
    jugador->puntaje = 0;
    croupier->numCartas = 0;
    croupier->puntaje = 0;
}

// Reparte cartas al jugador y actualiza su puntaje
void repartirCartas(myDeck *mazo, Jugador *jugador, int *indice) {
    jugador->cartas[jugador->numCartas++] = mazo[*indice];
    jugador->puntaje += mazo[*indice].puntaje;
    (*indice)++;
}

// Muestra las cartas iniciales de los jugadores
void mostrarCartasIniciales(myDeck *mazo, int indiceJugador, int indiceCroupier) {
    printf("Cartas iniciales repartidas:\n");
    printf("Jugador: Carta 1 - Palo %d, Número %d | Carta 2 - Palo %d, Número %d\n", 
           mazo[indiceJugador].cardType, mazo[indiceJugador].cardNumber,
           mazo[indiceJugador + 1].cardType, mazo[indiceJugador + 1].cardNumber);
    printf("Croupier: Carta 1 - Palo %d, Número %d | Carta 2 - Palo %d, Número %d\n", 
           mazo[indiceCroupier].cardType, mazo[indiceCroupier].cardNumber,
           mazo[indiceCroupier - 1].cardType, mazo[indiceCroupier - 1].cardNumber);
}

// Calcula los puntajes de la ronda inicial
void calcularRondaInicial(myDeck *mazo, Jugador *jugador, Jugador *croupier, int *indiceMazo) {
    if (*indiceMazo + 4 > TOTAL_CARTAS) { // Verifica que haya cartas suficientes
        printf("No hay suficientes cartas en el mazo para la ronda inicial.\n");
        return;
    }

    // Reparte dos cartas al jugador
    for (int i = 0; i < 2; i++) {
        repartirCartas(mazo, jugador, indiceMazo);
    }

    // Reparte dos cartas al crupier
    for (int i = 0; i < 2; i++) {
        repartirCartas(mazo, croupier, indiceMazo);
    }

    printf("Cartas iniciales repartidas.\n");
    printf("Puntaje del jugador: %d\n", jugador->puntaje);
    printf("Puntaje del crupier: %d\n", croupier->puntaje);
}

// Reinicia la ronda
void reiniciarRonda(int *indiceJugador, int *indiceCroupier, Jugador *jugador, Jugador *croupier) {
    *indiceJugador = 0;
    *indiceCroupier = TOTAL_CARTAS - 1;

    // Limpiar cartas y puntajes de jugadores
    jugador->numCartas = 0;
    jugador->puntaje = 0;
    croupier->numCartas = 0;
    croupier->puntaje = 0;
}
// Para determinar si el jugador gano= TRUE o perdio=FALSE
void calcularResultadoRonda(Jugador *jugador, Jugador *croupier) {
    printf("Resultado de la ronda: \n");
    printf("Puntaje del jugador: %d\n", jugador->puntaje);
    printf("Puntaje del croupier: %d\n", croupier->puntaje);

    if (jugador->puntaje > 21) {
        printf("El jugador ha perdido, su puntaje es mayor a 21.\n");
    } else if (croupier->puntaje > 21 || jugador->puntaje > croupier->puntaje) {
        printf("¡El jugador ha ganado!\n");
    } else if (jugador->puntaje < croupier->puntaje) {
        printf("El croupier ha ganado.\n");
    } else {
        printf("Empate.\n");
    }
}
// Calcular el saldo, luego de haber ganado o perdido
void calcularDineroFinal(Jugador *jugador, int apuesta, bool gano) {
    if (gano) {
        jugador->dinero += apuesta;  // Si ganó, se le agrega la apuesta
        printf("¡Has ganado! Tu nuevo saldo es: %d\n", jugador->dinero);
    } else {
        jugador->dinero -= apuesta;  // Si perdió, se le resta la apuesta
        printf("Has perdido. Tu saldo restante es: %d\n", jugador->dinero);
    }
}
void mostrarCartasJugador(Jugador *jugador) {
    printf("Cartas del jugador: ");
    for (int i = 0; i < jugador->numCartas; i++) {
        printf("Palo %d, Número %d | ", jugador->cartas[i].cardType, jugador->cartas[i].cardNumber);
    }
    printf("\n");
}

