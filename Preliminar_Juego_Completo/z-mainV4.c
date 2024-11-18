#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> // Para calloc y realloc

////////////////////////Funciones propias////////////////////////
#define SALDO_INICIAL 1000
#include "config.h"     // donde esta la funcion para buscar configuracion en .env
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego
#include "jugador.h"    // donde estan declaradas las funciones del JUGADOR durante la SESION
#include "scoreboard.h" // donde estan declaradas las estructuras y funciones para persistencia ranking

/////////////////////////////////////////////////////////////////////////////////////
void mostrarMenuPrincipal() {
        printf("\n=== Menú Principal ===\n");
        printf("1. Imprimir los datos actuales del jugador\n");
        printf("2. Jugar una partida\n");
        printf("3. Mostrar Ranking actual\n");
        printf("4. Mostrar Historial de Partidas\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
}


int main() {
    // Variables necesarias
    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Asignando memoria dinámica para el arreglo de lista Ranking
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }


    // Buscando Nombre del Archivo de Ranking
    char *nombreArchivoRanking = getconfig("archivo_ranking");
    if (nombreArchivoRanking == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }

    // Asignando memoria dinámica para el arreglo de historial
    Jugador *historial = calloc(1, sizeof(Jugador)); // Inicialmente espacio para 1 Jugador
    if (historial == NULL) {
        printf("Error al asignar memoria para historial.\n");
        free(historial); // Liberar historial antes de salir
        return 1;
    }
    // Buscando Nombre del Archivo de Historial
    char *nombreArchivoHistorial = getconfig("archivo_historial");
    if (nombreArchivoHistorial == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(historial);
        return 1;
    }


    char nombreJugador[MAX_NOMBRE];
    myDeck mazo, mazoJugador, mazoCroupier;
    Jugador jugador1; // Estructura con Nombre, Saldos, victorias y empates

    // Mostrar mensaje de bienvenida
    mensajeBienvenida();

    // Pedir el nombre del jugador
    preguntarNombre(nombreJugador);

    // Inicializar el jugador con el nombre ingresado
    inicializarJugadorGlobal(&jugador1, nombreJugador, SALDO_INICIAL);

    // Inicializar el mazo general y Barajar
    inicializarMazo(&mazo);
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
                // Si saco la verificacion, podriamos dejar en el historial saldos negativos de partidas
                if (jugador1.saldo <= 0) {
                    printf("No tienes saldo suficiente para jugar. ¡Vuelve cuando tengas más dinero!\n");
                } else {
                    jugarPartida(&mazo, &jugador1);
                }
                break;
            }
            case 3:
                showRanking(scoreList, nombreArchivoRanking);  // Actualiza y muestra el ranking en la terminal
                break;
            case 4:
                // Falta crear funciones para Ver historial
                break;
            case 5:
                salir = true;
                printf("Gracias por jugar. ¡Hasta pronto!\n");
                break;
            
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                        
        
        }//Fin Menu Principal
    } // Fin While Externo
    // Actualizacion del Ranking
    rankingImport(scoreList, nombreArchivoRanking);


    // Enviamos a verificar el jugador de la partida actual
    Score nuevoJugador = crearScore(jugador1.nombre, jugador1.saldo); // Convierte nombre y dinero a tipo Score
    checkScore(scoreList, nuevoJugador, nombreArchivoRanking); // Verifica y agrega el jugador
    // Decidir si mostrar o no ranking al final
    printf("\n=================== RANKING ACTUALIZADO ===================\n");
    printf("----------------------------------------------------------\n");

    showRanking(scoreList, nombreArchivoRanking);
    printf("=======================================\n");
    printf(" Gracias por jugar. ¡Hasta pronto!🎉\n");
    printf("=======================================\n");
 

    // Liberar la memoria dinámica antes de salir
    free(scoreList);
    free(nombreArchivoRanking);
    free(historial);
    free(nombreArchivoHistorial);


    return 0;
}
