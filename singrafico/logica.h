#ifndef LOGICA_H
#define LOGICA_H

#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "jugador.h"    // donde estan declaradas las funciones del JUGADOR durante la SESION


//declaracion de funciones -> LOGICA
// La partida completa de Blackjack
void jugarPartida(myDeck *mazo, Jugador *jugador1);


int calcularPuntaje(const myDeck *jugador, int numCartas);
// Función para comparar los puntajes del jugador y el croupier
bool evaluarResultado(int puntajeJugador, int puntajeCroupier);
// Muestra mensaje segun "como" gano o perdio
void mostrarMensajeResultado(int puntajeJugador, int puntajeCroupier, bool jugadorGano);

// Turno Jugador

// Pregunta si desea otra carta
bool preguntarAccionJugador(int puntaje);
// Retorna 'true' si el puntaje del jugador excede 21, 'false' en caso contrario
bool verificarPasoDePuntaje(myDeck *jugador, int numCartas);
// Función que realiza la acción del jugador (pedir otra carta o no) y decide si continuar o terminar el turno
bool realizarAccionJugador(bool accion, myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador);
// Esta función orquesta el turno del jugador, manejando las acciones durante su turno (pedir carta, plantarse, etc.)
void turnoJugador(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador, bool *pasoDePuntaje);
// Esta función maneja el reparto inicial de cartas tanto al jugador como al croupier
void manoInicial(myDeck *mazo, myDeck *jugador, myDeck *croupier, int *indiceMazo, int *indiceJugador, int *indiceCroupier);


//Turno Croupier
// Determina si el croupier debe pedir otra carta basado en su puntaje actual
bool debePedirCarta(int puntajeCroupier);
/// Gestiona el turno del Croupier, determinando si debe pedir una carta o plantarse automáticamente según las reglas del Blackjack.
void turnoCroupier(myDeck *mazo, myDeck *croupier, int *indiceMazo, int *indiceCroupier);



#endif // LOGICA_H