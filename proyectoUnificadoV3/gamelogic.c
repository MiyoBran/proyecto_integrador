#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h> /// para caracteres anchos / emoticones?



// Includes Propios del proyecto
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
#include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI

#define decks 1


void initDeck(myDeck Deck[],int *remaining_cards, myDeck Crupier[], myDeck Player[]){
    int index = 0;
    for (int i = 0; i < (4*decks); i++)
    {
        for (int j = 0; j < (13*decks); j++)
        {
            Deck[index].cardType = i;
            Deck[index].cardNumber = j;
            index++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        Crupier[i].cardType = -1;
        Player[i].cardType = -1;
    }
    (*remaining_cards) = 52*decks;
}



/*PARA ELEGIR UNA CARTA ALEATORIA DEL MAZO - funcion de tipo card*/
myDeck randomCard(myDeck Deck[], int *remaining_cards){
    myDeck Card;
    int randomIndex = rand() % *remaining_cards;
    Card = Deck[randomIndex];
    Deck[randomIndex] = Deck[(*remaining_cards)-1];
    (*remaining_cards)--;
    return Card;
};



/*VER SI HAY QUE CAMBIARLE EL NOMBRE A LA FUNCION ESTA*/
int gamelogic(){
    srand(time(NULL));
    myDeck Deck[52*decks], Crupier[5], Player[5];
    int remaining_cards;
    initDeck(Deck,&remaining_cards,Crupier,Player);
}




/////////////////////////////////////////////////////////////////////////////////////
bool compareScores(int puntajeJugador, int puntajeCroupier) {
    
    // Si el puntaje del jugador excede 21, el jugador ha perdido
    if (puntajeJugador > 21) {
        return false; // El jugador se pasa de 21
    }
    
    // Si el croupier se pasa de 21, o el puntaje del jugador es mayor que el del croupier, el jugador gana
    else if (puntajeCroupier > 21 || puntajeJugador > puntajeCroupier) {
        return true;  // El jugador gana
    }
    
    // Si el puntaje del jugador es igual o menor que el del croupier, el jugador pierde o empata
    else {
        return false; // Empate o el croupier gana
    }
}


/////////////////////////////////////////////////////////////////////////////////////
int getPlayerMoney(int bet, bool *playerWin) {
    int money = 10000;
    if (*playerWin) {
        money = money + bet;
    }   else {
        money = money - bet;
    }
    return money;
}

void getCard(myDeck *deck, int *amountCards) {
    if (*amountCards == MAX_CARDS_DISPLAYED) {
        *amountCards = MAX_CARDS_DISPLAYED;
    }   else {
        deck[*amountCards].cardType = rand() % 4;
        deck[*amountCards].cardNumber = rand() % 13;
        (*amountCards)++;
    }

}

int calculatePoints(myDeck *deck, int *amountCards) {
    int totalPoints = 0;
    for (int i = 0; i < *amountCards; i++) {
        totalPoints = totalPoints + deck[i].cardNumber+1; 
    }
    return totalPoints;
}
/////////////////////////////////////////////////////////////////////////////////////