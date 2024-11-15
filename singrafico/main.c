
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////

#include "mazo.h"


/////////////////////////////////////////////////////////////////////////////////////


int main() {
    myDeck mazo, jugador1, jugador2;

    // Inicializar el mazo y los jugadores
    inicializarMazo(&mazo);
    //Para corroborar
    imprimirMazo(&mazo,TAMANO_MAZO);


    inicializarJugador(&jugador1);
    inicializarJugador(&jugador2);

    // Mezclar el mazo
    barajarMazo(&mazo);
    //Para corroborar
    imprimirMazo(&mazo,TAMANO_MAZO);

    int indiceMazo = TAMANO_MAZO - 1; // Inicia en la última carta del mazo
    int indiceJ1 = 0, indiceJ2 = 0;

    // Jugador 1 y Jugador 2 piden cartas hasta completar su mano
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        if (!pedir1carta(&mazo, &jugador1, &indiceMazo, &indiceJ1)) break;
        if (!pedir1carta(&mazo, &jugador2, &indiceMazo, &indiceJ2)) break;
    }

    // Imprimir las cartas de los jugadores
    printf("\nCartas de Jugador 1:\n");
    imprimirCartasJugador(&jugador1,CARTAS_POR_JUGADOR);

    printf("\nCartas de Jugador 2:\n");
    imprimirCartasJugador(&jugador2,CARTAS_POR_JUGADOR);

    ///---> en este punto tenemos 2 mazos &jugador1 y &jugador2 que tienen solo 10 cartas con valores >0 

    return 0;
}
