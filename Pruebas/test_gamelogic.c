// archivo test_gamelogic.c
///////////////////Include INICIO /////////////////////////////
//#include "raylib.h" // este es el que hace dificil compilar
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///////////////////Include FIN ///////////////////////////////

////////////////////////INCLUDE Propios INICIO//////////////////

#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
// #include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI

////////////////////////INCLUDE Propios FIN////////////////////

////////////////////////Menu Pruebas Logicas-INICIO////////////////////////
// archivo test_gamelogic.c
void mostrarMenu() {
    printf("\n--- Menú de Opciones ---\n");
    printf("1. Inicializar mazos y jugador\n"); 
    printf("2. Calcular ronda inicial\n");
    printf("3. Simular jugador pide o no\n");
    printf("4. Resultado de la ronda\n");
    printf("5. Jugar nueva ronda\n");
    printf("6. Salir\n");
    printf("Seleccione una opción: ");
}
////////////////////////Menu Pruebas Logicas-FIN///////////////////////////

////////////////////////Funciones propias del test////////////////////////

bool simularJugadorPide(myDeck *mazo, Jugador *jugador, int *indiceJugador) {
    if (*indiceJugador >= TOTAL_CARTAS) {
        printf("No hay más cartas disponibles para el jugador.\n");
        return false;  // Si no hay más cartas, no puede pedir
    }

    // Simular si el jugador pide o no (50% de probabilidad)
    bool pideCarta = rand() % 2 == 0;

    if (pideCarta) {
        jugador->cartas[jugador->numCartas] = mazo[*indiceJugador];
        jugador->puntaje += mazo[*indiceJugador].puntaje;
        jugador->numCartas++;
        (*indiceJugador)++;

        printf("El jugador ha pedido una carta.\n");
        printf("Nueva carta: Palo %d, Número %d\n", 
               mazo[*indiceJugador - 1].cardType, 
               mazo[*indiceJugador - 1].cardNumber);
        printf("Puntaje actual: %d\n", jugador->puntaje);
    } else {
        printf("El jugador no ha pedido una carta.\n");
    }

    return pideCarta;  // Retorna true si pidió carta, false si no
}


////////////////////////MAIN////////////////////////

int main() {
    ////////////////////////Bloques Importantes en main - INICIO////////////////////////
    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Asignación de memoria para el puntaje del ranking
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) {
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }

    // Cargar el archivo de configuración
    char *scoreDB = getconfig("archivo_datos"); // obtiene nombre del archivo-base de datos del ranking
    if (scoreDB == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }


    // Declarar el mazo y los jugadores
    myDeck mazo[TOTAL_CARTAS];  // Suponiendo que ya tenemos las cartas en el mazo
    Jugador jugador, croupier;

    // Declarar los índices para el mazo
    int indiceJugador = 0, indiceCroupier = 0; // Asegúrate de inicializarlos
    int indiceMazo = 0; // Esto inicializa el índice del mazo
    ////////////////////////Bloques Importantes en main - FIN////////////////////////

    int opcion;
    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada no válida. Intente nuevamente.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        switch (opcion) {
            case 1:
                // Inicializar y mezclar el mazo antes de repartir las cartas
                inicializarMazo(mazo);   // Inicializar el mazo en orden
                mezclarMazo(mazo);       // Mezclar el mazo
                
                // Llamar a las funciones para inicializar mazo y jugadores
                inicializarIndicesYEstructuras(&jugador, &croupier, &indiceJugador, &indiceCroupier);
                repartirCartasJugador(mazo, &jugador, &indiceJugador);
                repartirCartasCroupier(mazo, &croupier, &indiceCroupier);
                mostrarCartasIniciales(mazo, indiceJugador, indiceCroupier);
                break;

            case 2:
                // Asegúrate de pasar el índice correcto que controla la posición en el mazo
                calcularRondaInicial(mazo, &jugador, &croupier, &indiceMazo); // Pasar el puntero de indiceMazo
                break;

            case 3:
                // Llamar a la función para simular que el jugador pide una carta
                // Cambiamos simularJugadorPide para que retorne un booleano

                bool jugadorDecidePedir = simularJugadorPide(mazo, &jugador, &indiceJugador);

                if (jugadorDecidePedir) {
                    // Si el jugador decide pedir una carta más, recalcular su puntaje y mostrar cartas
                    printf("El jugador ha decidido pedir una carta más.\n");
                    printf("Puntaje actual: %d\n", jugador.puntaje);

                    // Aquí faltaría agregar la lógica para mostrar las cartas del jugador y recalcular el puntaje
                    // Mostramos las cartas actuales del jugador
                    mostrarCartasJugador(&jugador);  // Esta función debería estar definida

                    // Faltaría verificar si el jugador ha superado los 21 puntos
                    if (jugador.puntaje > 21) {
                        printf("El jugador ha superado los 21 puntos. ¡Perdió!\n");
                        // Aquí se podría añadir la lógica para restar dinero al jugador o finalizar la ronda
                        break;
                    }
                } else {
                    // Si el jugador decide no pedir más cartas, se termina la acción de pedir
                    printf("El jugador ha decidido no pedir más cartas.\n");
                    // Mostrar el puntaje final del jugador
                    printf("Puntaje final del jugador: %d\n", jugador.puntaje);

                    // Aquí se podría añadir la lógica para mostrar el resultado de la ronda
                    // Se debería comparar el puntaje del jugador con el del croupier y determinar el resultado
                    // Llamamos a la función que calcula el resultado entre el jugador y el croupier
                    // Esto debería estar implementado en la función calcularResultadoRonda
                    calcularResultadoRonda(&jugador, &croupier);  // Esta función debería estar definida

                    // También faltaría actualizar el dinero final del jugador, basado en el resultado
                    // Esta parte debería ser manejada por la función calcularDineroFinal
                    calcularDineroFinal(&jugador, apuesta, gano);  // Esta función también debería estar definida
                }

                break;

            case 4:
                // Llamar a la función para calcular el resultado de la ronda
                calcularResultadoRonda(&jugador, &croupier);
                break;

            case 5:
                // Llamar a la función para reiniciar la ronda
                reiniciarRonda(&indiceJugador, &indiceCroupier, &jugador, &croupier);
                break;

            case 6:
                printf("Gracias por jugar. Saliendo...\n");
                break;

            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 6);

    free(scoreList); // Liberar memoria antes de finalizar
    return 0;
}