///////////////////Include para main de prueba ///////////////////
// #include "raylib.h" // este es el que hace dificil compilar
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////////////////////////////////////////




////////////////////////Funciones propias////////////////////////

#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
#include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI

/////////////////////////////////////////////////////////////////


int main() {
    ////////////////////////Bloques Importantes en main////////////////////////
    srand(time(NULL)); // Inicializar la semilla aleatoria
    
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }

    // esta en la funcion loadRankingVariables , pero esto puede ir aca y pasarlo como argumento
    char *scoreDB = getconfig("archivo_datos"); // obtiene nombre del archivo-base de datos del rankin
    if (scoreDB == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }
    ///////////************//////////////





}
