#ifndef LOGICA_H
#define LOGICA_h


#include "mazo.h"



//declaracion de funciones
int calcularPuntaje(myDeck *jugador, int numCartas);
// Comparo resultados
bool evaluarResultado(int puntajeJugador, int puntajeCroupier);
void mostrarMensajeResultado(int puntajeJugador, int puntajeCroupier, bool jugadorGano);


//Simular Turnos
//Jugador
bool evaluarResultado(int puntajeJugador, int puntajeCroupier);
void mostrarEstadoJugador(myDeck *jugador, int numCartas);
char preguntarAccionJugador();
bool verificarPasoDePuntaje(myDeck *jugador, int numCartas);
bool realizarAccionJugador(char accion, myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador);
void turnoJugador(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador);
//Croupier
bool debePedirCarta(int puntajeCroupier);
void turnoCroupier(myDeck *mazo, myDeck *croupier, int *indiceMazo, int *indiceCroupier);



#endif // LOGICA_H