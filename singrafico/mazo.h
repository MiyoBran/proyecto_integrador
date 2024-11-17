#ifndef MAZO_h
#define MAZO_h

#define TAMANO_MAZO 52  // Número total de cartas en el mazo
#define CARTAS_POR_JUGADOR 10  // Máximo número de cartas por jugador
#define NUM_PALOS 4       // Número total de palos en el mazo
#define CARTAS_POR_PALO 13 // Número total de cartas por palo
#define MAX_CARTAS_JUGADOR 10 // Límite de cartas por jugador

// Structs-Enums para manejo de Cartas y Barajas
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

// Declaración de funciones -> Mazo

// Inicializa una carta con su palo, número y puntaje correspondiente.
void inicializarCarta(myCard *carta, Palo palo, Carta numero);

// Inicializa el mazo de cartas con 52 cartas (13 por cada uno de los 4 palos).
void inicializarMazo(myDeck *mazo);

// Función para imprimir una carta con su nombre, palo y puntaje
void imprimirCarta(myCard carta);

// Función de depuración para imprimir el mazo completo
void imprimirMazo(myDeck mazo[], int numCartas);

// Función para barajar el mazo (algoritmo Fisher-Yates)
void barajarMazo(myDeck *mazo);

// Función para pedir una carta del mazo y asignársela al jugador.
int pedir1carta(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador);

// Inicializa las cartas del mazo de un jugador con valores predeterminados
void inicializarMazoJugador(myDeck *jugador);

// Imprime todas las cartas del mazo hasta una posicion
void imprimirCartasJugador(myDeck jugador[], int numCartasJugador);




#endif// MAZO_h
