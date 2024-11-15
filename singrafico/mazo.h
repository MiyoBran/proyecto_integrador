#ifndef MAZO_h
#define MAZO_h

#define TAMANO_MAZO 52  // Número total de cartas en el mazo
#define CARTAS_POR_JUGADOR 10  // Máximo número de cartas por jugador
#define NUM_PALOS 4       // Número total de palos en el mazo
#define CARTAS_POR_PALO 13 // Número total de cartas por palo
#define MAX_CARTAS_JUGADOR 10 // Límite de cartas por jugador


typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;

typedef struct {
    Palo cardType;     // Palo de la carta (TREBOL, DIAMANTE, etc.)
    Carta cardNumber;  // Valor de la carta (A, DOS, etc.)
    int puntaje;       // Puntaje asignado a la carta
} myCard;

typedef struct {
    myCard cartas[52]; // Mazo completo de 52 cartas
} myDeck;

// Declaración de funciones

// Inicializa una carta con un palo, un número y su puntaje correspondiente
void inicializarCarta(myCard *carta, Palo palo, Carta numero);

// Inicializa un mazo completo con 52 cartas en orden
void inicializarMazo(myDeck *mazo);

// Imprime una carta específica (para verificar su contenido)
void imprimirCarta(myCard carta);

// Imprime todas las cartas del mazo completo
void imprimirMazo(myDeck mazo[], int numCartas);

// Mezcla el mazo utilizando el algoritmo Fisher-Yates
void barajarMazo(myDeck *mazo);

// Asigna una carta del mazo a un jugador, actualizando los índices correspondientes
int pedir1carta(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador);

// Inicializa las cartas del mazo de un jugador con valores predeterminados
void inicializarJugador(myDeck *jugador);

// Imprime todas las cartas del mazo hasta una posicion
void imprimirCartasJugador(myDeck jugador[], int numCartasJugador);




#endif// MAZO_h
