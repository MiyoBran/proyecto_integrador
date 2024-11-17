#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> // Para usar system() <-- se cambia al guardarlo es otra libreria?

////////////////////////Funciones propias////////////////////////
#define SALDO_INICIAL 1000
#include "config.h"     // funcion para buscar configuraciones del .env
#include "scoreboard.h"  // funciones para manejo de ranking
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego
#include "jugador.h"     // donde estan declaradas las funciones del JUGADOR durante la SESION

/////////////////////////////////////////////////////////////////////////////////////
void mostrarMenuPrincipal() {
        printf("\n=== Menú Principal ===\n");
        printf("1. Imprimir los datos actuales del jugador\n");
        printf("2. Jugar una partida\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
}


int main() {
    myDeck mazo, mazoJugador, mazoCroupier;
    Jugador jugador1; // Estructura con Nombre, Saldos, victorias y empates

    // Inicializar el mazo general y de los jugadores
    inicializarMazo(&mazo);
    inicializarJugadorGlobal(&jugador1, "Jugador 1", SALDO_INICIAL);

    // Mezclar el mazo
    barajarMazo(&mazo);
    // Depuración: verificar mazo mezclado
    // imprimirMazo(&mazo, TAMANO_MAZO);

    // INICIO del BUCLE
    int opcion;
    bool salir = false;

    while (!salir) {
        printf("\n=============================\n");
        printf("           MENÚ             \n");
        printf("=============================\n");

        mostrarMenuPrincipal(); // Mostrar el menú
        scanf("%d", &opcion);

        printf("\n-----------------------------\n");
       
        switch (opcion) { 
            case 1:
                printf("=== Datos del Jugador ===\n");
                imprimirJugador(&jugador1);
                break;
            case 2: {
                bool jugarOtra = true;
                while (jugarOtra) {
                    barajarMazo(&mazo);
                    inicializarMazoJugador(&mazoJugador);
                    inicializarMazoJugador(&mazoCroupier);
                    int indiceMazo = TAMANO_MAZO - 1; // Índice de la última carta del mazo
                    int indiceJ1 = 0, indiceC = 0;    // Índices para el jugador y el croupier

                    // Repartir la mano inicial
                    manoInicial(&mazo, &mazoJugador, &mazoCroupier, &indiceMazo, &indiceJ1, &indiceC);
                    int puntajeJugador = calcularPuntaje(&mazoJugador, indiceJ1);  

                    //SI obtuvimos BLACKJACK
                    bool jugadorBlackjack = false ; 
                    if (puntajeJugador == 21)
                    {
                        jugadorBlackjack = true ;
                        printf("FELICITACIONES! Obtuviste BLACKJACK.\n");
                    }else{
                    // Turno del jugador
                    printf("\n******EN CASE 2 -> Jugador********\n");
                    printf("Turno del jugador (EN MAIN):\n");
                    bool pasoDePuntajeJugador = false;
                    turnoJugador(&mazo, &mazoJugador, &indiceMazo, &indiceJ1, &pasoDePuntajeJugador);

                    // Mostrar estado final del jugador después del turno
                    // Calcular puntaje
                    puntajeJugador = calcularPuntaje(&mazoJugador, indiceJ1);  

                    if (!pasoDePuntajeJugador) {
                        puntajeJugador = calcularPuntaje(&mazoJugador, indiceJ1);
                        
                        printf("\n=================== RESULTADO FINAL ===================\n");
                        printf("Tus cartas:\n");
                        imprimirCartasJugador(&mazoJugador, indiceJ1);
                        printf("-------------------------------------------------------\n");
                        printf("Tu puntaje final: %d\n", puntajeJugador);
                        printf("=======================================================\n");
                    }
                    
                    // Turno del croupier
                    printf("\n******EN CASE 2 -> CROUPIER********\n");
                    turnoCroupier(&mazo, &mazoCroupier, &indiceMazo, &indiceC);
                    } // termina el Else -> Si no obtuvimos Blackjack

                    // Mostrar estado del croupier
                    // Calcular puntaje
                    int puntajeCroupier = calcularPuntaje(&mazoCroupier, indiceC);
                    printf("Cartas del croupier: \n");    
                    imprimirCartasJugador(&mazoCroupier, indiceC);


                    // Evaluar resultado
                    bool jugadorGano = evaluarResultado(puntajeJugador, puntajeCroupier);


                    // Actualizar estadísticas y saldo
                    actualizarEstadisticas(&jugador1, jugadorGano, jugadorBlackjack);
    /////////////////// REVISAR APUESTA
                    int apuesta = 200; // por ahora es 200
                    if (jugadorBlackjack) {
                        apuesta *= 1.5; // Multiplica la apuesta por 1.5 si tiene blackjack
                        jugadorGano=true; // es redundante?
                    }
                                        
                    modificarSaldo(&jugador1, jugadorGano ? apuesta : -apuesta);

                    printf("\n*******EN CASE 2 -> DATOS ACTUALIZADOS*******\n");
                    // Mostrar mensaje Resultado
                    mostrarMensajeResultado(puntajeJugador, puntajeCroupier, jugadorGano);
                    // Preguntar si desea jugar otra partida. Devuelve true=SI
                    imprimirJugador(&jugador1); // verificar si es redundante
                    jugarOtra = preguntarJugarOtra();

                }
                break;
            }
            case 3:
                salir = true;
                printf("Gracias por jugar. ¡Hasta pronto!\n");
                break;
            
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                        
        
        }//Fin Menu Principal
    } // Fin While Externo
                  
    return 0;
}
