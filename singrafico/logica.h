#ifndef LOGICA_H
#define LOGICA_h


#include "mazo.h"



//declaracion de funciones
int calcularPuntaje(myDeck *jugador, int numCartas);
// Comparo resultados
bool evaluarResultado(int puntajeJugador, int puntajeCroupier);
void mostrarMensajeResultado(int puntajeJugador, int puntajeCroupier, bool jugadorGano);


//Simular Turnos
void turnoCroupier(myDeck *mazo, myDeck *croupier, int *indiceMazo, int *indiceCroupier);
void turnoJugador(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador);



#endif // LOGICA_H