#ifndef JUGADOR_H
#define JUGADOR_H

////////////////////////Funciones propias////////////////////////

#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas


/////////////////////////////////////////////////////////////////////////////////////

#define MAX_NOMBRE 50

// Estructura completa para un jugador
typedef struct {
    char nombre[MAX_NOMBRE];  // Nombre del jugador
    int saldo;                // Dinero del jugador
    int victorias;            // Número de partidas ganadas
    int derrotas;             // Número de partidas perdidas
    int blackjack;              // Número de partidas empatadas
} Jugador;

// Declaracion de funciones -> Jugador
// Configura los valores iniciales de un jugador al inicio de la sesión de juego.
void inicializarJugadorGlobal(Jugador *jugador, const char *nombre, int saldoInicial);
// Esta función actualiza las estadísticas del jugador según el resultado de la partida.
void actualizarEstadisticas(Jugador *jugador, bool gano, bool blackjack);
// Esta función permite sumar o restar una cantidad al saldo del jugador.
void modificarSaldo(Jugador *jugador, int cantidad);
// Imprime la información relevante de un jugador, como su nombre, saldo y estadísticas.
void imprimirJugador(const Jugador *jugador);
// Pregunta al jugador si desea jugar otra partida y valida la entrada.
bool preguntarJugarOtra();

// Mensaje inicial al iniciar la ejecución del programa
void mensajeBienvenida();
// Mensaje donde nos pide ingresar un nombre usando MAX_NOMBRE de límite
void preguntarNombre(char *nombreJugador);






#endif // JUGADOR_H