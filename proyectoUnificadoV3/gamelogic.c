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
int MAX_CARDS_DISPLAYED;

void initDeck(myCard Deck[],int *remaining_cards, myCard Crupier[], myCard Player[]){
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
myCard randomCard(myCard Deck[], int *remaining_cards){
    myCard Card;
    int randomIndex = rand() % *remaining_cards;
    Card = Deck[randomIndex];
    Deck[randomIndex] = Deck[(*remaining_cards)-1];
    (*remaining_cards)--;
    return Card;
};



/*VER SI HAY QUE CAMBIARLE EL NOMBRE A LA FUNCION ESTA*/
int gamelogic(){
    srand(time(NULL));
    myCard Deck[52*decks], Crupier[5], Player[5];
    int remaining_cards;
    initDeck(Deck,&remaining_cards,Crupier,Player);
}




/////////////////////////////////////////////////////////////////////////////////////
bool compareScores(int puntajeJugador, int puntajeCroupier) {
    // Si el croupier se pasa de 21, o el puntaje del jugador es mayor que el del croupier, el jugador gana
    if (puntajeJugador > puntajeCroupier) {
        return true;  // El jugador gana
    } else {
        return false; // Empate o el croupier gana
    }
}


/////////////////////////////////////////////////////////////////////////////////////
int getPlayerMoney(int playerMoney, int bet, bool playerWin) {
    if (playerWin) {
        playerMoney = playerMoney + bet;
    }   else {
        playerMoney = playerMoney - bet;
    }
    return playerMoney;
}

void getCard(myCard *deck, int *amountCards) {
    if (*amountCards == MAX_CARDS_DISPLAYED) {
        *amountCards = MAX_CARDS_DISPLAYED;
    }   else {
        deck[*amountCards].cardType = rand() % 4;
        deck[*amountCards].cardNumber = rand() % 13;
        (*amountCards)++;
    }

}

int calculatePoints(myCard *deck, int *amountCards) {
    int totalPoints = 0;
    for (int i = 0; i < *amountCards; i++) {
        totalPoints = totalPoints + deck[i].cardNumber+1; 
    }
    return totalPoints;
}

//Checks if player got a blackjack win
void allowBlackjackWin(int playerPoints, int amountCardsPlayer, gameState *currentGame) {
    if (playerPoints == 21 && amountCardsPlayer == 2) {
        currentGame->playerBlackjack = true;
        currentGame->roundEnd = true;
        currentGame->allowMoneyUpdate = true;
    } 
}

//Check if player went above 21 points
bool playerAbove21(int points) {
    if (points > 21) {
        return true;     
    }
    return false;
}


//Starts a new round, might need to compress the parameters a bit
void startRound(int *amountCardsPlayer, int *amountCardsDealer, int *playerPoints, int *dealerPoints, int *bet, myCard playerDeck[MAX_CARDS_DISPLAYED], myCard dealerDeck[MAX_CARDS_DISPLAYED], gameState *currentGame) {
    *amountCardsPlayer = 0;
    *amountCardsDealer = 0;
    *bet = 100;
    for (int i = 0; i < 2; i++) {
        getCard(playerDeck, amountCardsPlayer);
    }
    getCard(dealerDeck, amountCardsDealer); 
    *playerPoints = calculatePoints(playerDeck, amountCardsPlayer);
    *dealerPoints = calculatePoints(dealerDeck, amountCardsDealer);
    currentGame->playerWin = false;
    currentGame->roundEnd = false;
    currentGame->allowMoneyUpdate = false;
    currentGame->playerBlackjack = false;
}

/////////////////////////////////////////////////////////////////////////////////////