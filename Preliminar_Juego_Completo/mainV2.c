#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> // Para usar system() <-- se cambia?

////////////////////////Funciones propias////////////////////////
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
// VERIFICAR SI FUNCIONA
void limpiarPantalla() {
    // Determina el comando de limpieza según el sistema operativo
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int main() {
    myDeck mazo, mazoJugador, mazoCroupier;
    Jugador jugador1; // Estructura con Nombre, Saldos, victorias y empates

    // Inicializar el mazo general y de los jugadores
    inicializarMazo(&mazo);
    inicializarJugadorGlobal(&jugador1, "Jugador 1", 1000);

    // Mezclar el mazo
    barajarMazo(&mazo);
    // Depuración: verificar mazo mezclado
    // imprimirMazo(&mazo, TAMANO_MAZO);

    // INICIO del BUCLE
    int opcion;
    bool salir = false;

    while (!salir) {

        mostrarMenuPrincipal();             // Inicio menu principal
        scanf("%d", &opcion);
        
        // // Opcional
        // limpiarPantalla(); // Limpia la pantalla después de seleccionar una opción
        // printf("Opcion elegida : %d \n", opcion);


        switch (opcion) { 
            case 1:
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

                    // Turno del jugador
                    printf("\n**************\n");
                    printf("Turno del jugador:\n");
                    bool pasoDePuntajeJugador = false;
                    turnoJugador(&mazo, &mazoJugador, &indiceMazo, &indiceJ1, &pasoDePuntajeJugador);

                    // Mostrar estado final del jugador después del turno
                    // Calcular puntaje
                    int puntajeJugador;  

                    if (!pasoDePuntajeJugador) {
                        puntajeJugador = calcularPuntaje(&mazoJugador, indiceJ1);
                        printf("Tus cartas: \n");
                        imprimirCartasJugador(&mazoJugador,indiceJ1);
                        printf("\n**************\n");
                        printf("Tu puntaje final: %d\n", puntajeJugador);
                    }
                    // Turno del croupier
                    printf("\n**************\n");
                    turnoCroupier(&mazo, &mazoCroupier, &indiceMazo, &indiceC);

                    // Mostrar estado final del croupier
                    // Calcular puntaje
                    int puntajeCroupier = calcularPuntaje(&mazoCroupier, indiceC);
                    printf("Cartas del croupier: \n");    
                    imprimirCartasJugador(&mazoCroupier, indiceC);

                    // Evaluar resultado
                    bool jugadorGano = evaluarResultado(puntajeJugador, puntajeCroupier);

                    // Actualizar estadísticas y saldo
                    actualizarEstadisticas(&jugador1, jugadorGano, puntajeJugador == puntajeCroupier);
                    modificarSaldo(&jugador1, jugadorGano ? 100 : -100);


                    // Mostrar mensaje Resultado
                    mostrarMensajeResultado(puntajeJugador, puntajeCroupier, jugadorGano);

                    // Preguntar si desea jugar otra partida. Devuelve true=SI
                    jugarOtra = preguntarJugarOtra();
                    if (jugarOtra)
                    {
                        limpiarPantalla(); // Limpia la pantalla después de seleccionar una opción
                    }
                    
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
