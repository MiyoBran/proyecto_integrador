#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

// Includes Propios del proyecto
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
#include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI

int main() {
    struct card testCard;
    testCard.palo = TREBOL;
    testCard.carta = A;
    testCard.puntaje = 11; // O el valor que necesites

    imprimircarta(testCard);
    return 0;
}
