#include "gamelogic.h"
#include <stdio.h>

int main() {
    struct card testCard;
    testCard.palo = TREBOL;
    testCard.carta = A;
    testCard.puntaje = 11; // O el valor que necesites

    imprimircarta(testCard);
    return 0;
}
