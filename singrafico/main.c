
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////

#include "mazo.h"
#include "logica.h"

/////////////////////////////////////////////////////////////////////////////////////


int main() {
    myDeck mazo, jugador1, croupier;

    // Inicializar el mazo y los jugadores
    inicializarMazo(&mazo);
    inicializarJugador(&jugador1);
    inicializarJugador(&croupier);

    // Mezclar el mazo
    barajarMazo(&mazo);     //Para corroborar     imprimirMazo(&mazo,TAMANO_MAZO);

    int indiceMazo = TAMANO_MAZO - 1; // Inicia en la última carta del mazo
    int indiceJ1 = 0, indiceC = 0; // cada jugador con un indice propio

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
