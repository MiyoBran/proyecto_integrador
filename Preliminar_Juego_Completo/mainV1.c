
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////
#include "config.h"     // funcion para buscar configuraciones del .env
#include "scoreboard.h"  // funciones para manejo de ranking
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego
#include "jugador.h"     // donde estan declaradas las funciones del JUGADOR durante la SESION

/////////////////////////////////////////////////////////////////////////////////////


int main() {
    myDeck mazo, jugador1, croupier;

    // Inicializar el mazo general y de los jugadores
    inicializarMazo(&mazo);
    inicializarJugador(&jugador1);
    inicializarJugador(&croupier);

    // Mezclar el mazo
    barajarMazo(&mazo);     //Para corroborar     imprimirMazo(&mazo,TAMANO_MAZO);

    int indiceMazo = TAMANO_MAZO - 1; // Índice de la última carta del mazo
    int indiceJ1 = 0, indiceC = 0;    // Índices para el jugador y el croupier

    //Turnos
    printf("Turno del jugador:\n");
    turnoJugador(&mazo, &jugador1, &indiceMazo, &indiceJ1);

    printf("Turno del croupier:\n");
    turnoCroupier(&mazo, &croupier, &indiceMazo, &indiceC);


    // Resultados
    int puntajeJugador = calcularPuntaje(&jugador1, indiceJ1);
    int puntajeCroupier = calcularPuntaje(&croupier, indiceC);
    bool jugadorGano = evaluarResultado(puntajeJugador, puntajeCroupier);

    // Mostrar mensajes
    mostrarMensajeResultado(puntajeJugador, puntajeCroupier, jugadorGano);


    return 0;
}
