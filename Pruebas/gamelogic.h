#ifndef GAMELOGIC_H
#define GAMELOGIC_H

// Enumeraciones para los palos de las cartas
typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

// Enumeración para identificar cada carta
typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;

// Estructura que define una carta en el mazo
typedef struct {
    Palo cardType;
    Carta cardNumber;
    int puntaje; // Puntaje asociado a la carta (por ejemplo, valor de la carta)
} myDeck;

// Definiciones de constantes
#define TOTAL_CARTAS 52
#define MAX_CARTAS_MANO 11

// Estructura del jugador
typedef struct {
    int dinero;                     // Dinero inicial del jugador
    int puntaje;                    // Puntaje acumulado en la ronda
    myDeck cartas[MAX_CARTAS_MANO]; // Cartas del jugador
    int numCartas;                  // Número actual de cartas en la mano
} Jugador;

// Declaración de funciones
// Inicializa el mazo de cartas
void inicializarMazo(myDeck *mazo);

// Mezcla el mazo de cartas
void mezclarMazo(myDeck *mazo);

// Inicializa las estructuras de los jugadores y sus índices en el mazo
void inicializarIndicesYEstructuras(Jugador *jugador, Jugador *croupier, int *indiceJugador, int *indiceCroupier);

// Reparte las cartas al jugador
void repartirCartas(myDeck *mazo, Jugador *jugador, int *indice);

// Muestra las cartas iniciales de los jugadores
void mostrarCartasIniciales(myDeck *mazo, int indiceJugador, int indiceCroupier);

// Calcula los puntajes de la ronda inicial y reparte las cartas correspondientes
void calcularRondaInicial(myDeck *mazo, Jugador *jugador, Jugador *croupier, int *indiceMazo);

// Reinicia la ronda, restaurando los índices y las cartas
void reiniciarRonda(int *indiceJugador, int *indiceCroupier, Jugador *jugador, Jugador *croupier);
// 
bool calcularResultado(Jugador *jugador, Jugador *croupier);
//
void calcularDineroFinal(Jugador *jugador, int apuesta, bool gano);

#endif // GAMELOGIC_H
