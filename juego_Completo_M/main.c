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
#include "record.h"     // donde estan declaradas las funciones para la persistencia del historial de partidas
// Espacio para nueva funcionalidad o juego
// Espacio para nueva funcionalidad o juego
// Espacio para nueva funcionalidad o juego

/////////////////////////////////////////////////////////////////////////////////////
void mostrarMenuPrincipal() {
        printf("\n=== Menú Principal ===\n");
        printf("1. Imprimir los datos actuales del jugador\n");
        printf("2. Jugar una partida\n");
        printf("3. Mostrar Ranking actual\n");
        printf("4. Mostrar Historial de Partidas\n");
        // Espacio para nueva funcionalidad o juego
        // Espacio para nueva funcionalidad o juego
        // Espacio para nueva funcionalidad o juego
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
}


int main() {
    // Variables necesarias
    srand(time(NULL)); // Inicializar la semilla aleatoria
    Jugador *historial = NULL;  // Puntero al arreglo de jugadores

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

    // Buscando Nombre del Archivo de Historial
    char *recordFileName = getconfig("archivo_historial");
    if (recordFileName == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(historial);
        return 1;
    }

    // Verificar cuántos registros existen en el archivo
    int cantidadRegistros = recordSize(recordFileName);  // Verificar cuántos registros existen en el archivo
    // Importar registros del archivo
    recordImport(&historial, recordFileName);


    char nombreJugador[MAX_NOMBRE];
    myDeck mazo;
    myDeck mazoJugador;
    myDeck mazoCroupier;
    Jugador jugador1; // Estructura con Nombre, Saldos, victorias y empates

    // Mostrar mensaje de bienvenida
    mensajeBienvenida();

    // Pedir el nombre del jugador
    preguntarNombre(nombreJugador);

    // Inicializar el jugador con el nombre ingresado
    inicializarJugadorGlobal(&jugador1, nombreJugador, SALDO_INICIAL);

    // Inicializar el mazo general y Barajar - > cada partida igual lo vuelve a hacer
    inicializarMazo(&mazo);
    barajarMazo(&mazo);
    // Depuración: verificar mazo mezclado
    // imprimirMazo(&mazo, TAMANO_MAZO);

    // Declaracion inicial de indices. -> CUIDADO quien puede modificarlo
    // Nos dicen hasta donde llenamos de cartas el mazo de cada Jugador
    int indiceMazo = TAMANO_MAZO - 1; // Índice de la última carta en el mazo
    int indiceJ1 = 0;
    int indiceC = 0;    // Índices para el jugador y el croupier

    int apuesta = 200; // Apuesta inicial, "cambiar" antes de mandar a jugarpartida

    // Este booleando Nos indica si la partida termina de manera forzada
    // Se modifica en turnoJugador , adentro de jugarPartida
    bool pasoDePuntajeJugador = false;


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
                printf("\n=== Datos del Jugador ===\n");
                imprimirJugador(&jugador1);
                break;
            case 2: {
                // Si saco la verificacion, podriamos dejar en el historial saldos negativos de partidas
                if (jugador1.saldo <= apuesta) {
                    printf("\n*** No tienes saldo suficiente para jugar. ¡Vuelve cuando tengas más dinero! ***\n");
                } else {
                    // Simulacion de una Ronda completa -> Verificar paso de punteros correctamente
                    jugarPartida(&mazo, &jugador1,&mazoJugador, &mazoCroupier, &indiceMazo, &indiceJ1, &indiceC, apuesta, &pasoDePuntajeJugador);
                    
                }   
                break;
            }
            case 3:
                showRanking(scoreList, nombreArchivoRanking);  // Actualiza y muestra el ranking en la terminal
                break;
            case 4:
                printf("\n=== Historial de Jugadores ===\n");
                showRecord(historial, cantidadRegistros);  // Llamamos a showRecord para imprimir el historial
                break;
            case 5:
                salir = true;
                printf("\n=== Gracias por jugar. ¡Hasta pronto! 🎉 ===\n");
                break;
            
            default:
            printf("\n*** Opción no válida. Intente de nuevo. ***\n");
                                    
        
        }//Fin Menu Principal
        
    } // Fin While Externo

    // Actualizacion del Ranking
    rankingImport(scoreList, nombreArchivoRanking);

    // Verificar y agregar el jugador al ranking
    Score nuevoJugador = crearScore(jugador1.nombre, jugador1.saldo); // Convierte nombre y dinero a tipo Score
    checkScore(scoreList, nuevoJugador, nombreArchivoRanking); // Verifica y agrega el jugador


    // Mostrar el ranking actualizado
    printf("\n=================== RANKING ACTUALIZADO ===================\n");
    printf("----------------------------------------------------------\n");

    showRanking(scoreList, nombreArchivoRanking);

    // Línea decorativa final
    printf("==========================================================\n");

    // Mensaje de despedida
    printf("Gracias por jugar. ¡Hasta pronto! 🎉\n");
    printf("==========================================================\n");

        
    // Agregar el nuevo registro al historial
    insertRecordEOF(&historial, jugador1, cantidadRegistros);

    // Guardar el historial actualizado
    cantidadRegistros++;  // Incrementar el número de registros
    recordSave(historial, recordFileName, cantidadRegistros);
 

    // Liberar la memoria dinámica antes de salir
    free(scoreList);
    free(nombreArchivoRanking);
    free(historial);
    free(recordFileName);


    return 0;
}
