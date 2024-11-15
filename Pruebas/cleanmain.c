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
void mostrarMenu() {
    printf("\n--- Menú de Opciones ---\n");
    printf("1. Inicializar Mazos y jugador\n"); 
    //1 - Inicializo fullDeck (1 mazo con 52 cartas ), mas adelante puede que sean mas mazos 
    //El jugador por ahora se inicializa como jugador y tiene dinero 5000
    //el As vale 11 salvo si al usarlo como 11, la suma da >21 , entonces vale 1

    printf("2. Calculo ronda inicial (mostrar puntaje 1 carta croupier y 2 jugador \n");
    //2 - 20 diff random positions, 10 for croupierDeck Player & 10 for croupierDeck Player
    //Hay que devolver al main para imprimir el puntaje que resulta en croupierDeck[0] y en playerDeck[1]+[2]
    //Llamar una funcion que nos dice si el jugador aposto 100 , 200 o 300
    
    printf("3. Simular jugador pide o no\n");
    //3 - Funcion aparte que devuelve bool player hit true o false. 
    //Si jugador Tiene A+Figura --> gana directo 
    //False guarda hasta que posicion mostrar del array y el puntaje
    //En True tiene que volver a calcular el puntaje del jugador para imprimir, y volver a simulurar un hit
    //Si el puntaje resulta mayor a 21 --> Jugador pierde directamente
    
    printf("4. Resultado de la ronda  \n");
    //4 - Ahora la posicion a mostrar carta del croupierDeck cambio, y se ven la carta [0]y[1]
    //Aca si el jugador no gano o perdio directamente - se muestran las 2 cartas de cada uno, un mensaje GANO ... PERDIO
    //Si no se determino directo, hay que llamar una funcion que determine hasta que posicion pide cartas el croupier (>=17 no pide mas)
    //Ahora tenemos que tener al jugador con un valor actrualizado de dinero
    //Mostrar el array del jugador y del croupier hasta donde corresponde con sus "puntajes" actualizado
    printf("5. Jugar nueva ronda\n");
    //5 - No estoy seguro si esto va aca
    printf("6. Salir\n");
    // Al salir preguntamos nombre del jugador y guardamos el nombre y el dinero final en 2 variables que luego imprimimos
    printf("Seleccione una opción: ");
}
////////////////////////Menu Pruebas Logicas-FIN///////////////////////////
////////////////////////Funciones propias del test INICIO////////////////////////
////////////////////////Funciones propias del test FIN///////////////////////////

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
    ////////////////////////Bloques Importantes en main - FIN////////////////////////
    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                printf("Preparando para jugar una nueva ronda...\n");
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

