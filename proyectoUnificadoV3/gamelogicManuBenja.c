#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h> /// para caracteres anchos / emoticones?



// Includes Propios del proyecto
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
#include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI

#define decks 1
int MAX_CARDS_DISPLAYED;

void initDeck(myCard Deck[],int *remaining_cards){
    int index = 0;

    //Recorre el mazo llenando los 4 tipos de cartas
    for (int i = 0; i < (4*decks); i++){
        //Recorre el mazo llenando los 13 valores de cartas
        for (int j = 0; j < (13*decks); j++){
            Deck[index].cardType = i;
            Deck[index].cardNumber = j;

            //Asigna el puntaje respectivo de cada carta
            if(j <= DIEZ){
                Deck[index].puntaje = j+1;
            }else{
                Deck[index].puntaje = 10;
            }

            index++;
        }
    }

    (*remaining_cards) = 52*decks;  //Guarda la cantidad de cartas que contiene el mazo;
}

//Funcion que mezcla el mazo por algorito de Fisher-Yates
void shuffleDeck(myCard Deck[], int amountCards){
    for (int i = amountCards - 1; i > 0; i--) {
        // Genera un índice aleatorio entre 0 e i
        int j = rand() % (i + 1);
        
        // Intercambia los elementos en las posiciones i y j
        myCard temp = Deck[i];
        Deck[i] = Deck[j];
        Deck[j] = temp;
    }
}

//Funcion especifica para calculatePoints()
void orderAs(myCard Deck[], int amountCards) {
    myCard temp;
    bool flag = true;

    //Ordena el mazo recibido por burbujeo dejando al final los As
    for (int j = 0; j < amountCards - 1 && flag; j++) {
        flag = false;
        for (int i = 0; i < amountCards - 1 - j; i++) {
            if (Deck[i].cardNumber == A) {
                temp = Deck[i];
                Deck[i] = Deck[i + 1];
                Deck[i + 1] = temp;
                flag = true;
            }
        }
    }

    return;
}

//Calcula los puntos de un Mazo
int calculatePoints(myCard Deck[], int amountCards){
    myCard orderedDeck[amountCards];    //Crea un mazo para usar de forma temporal
    int points = 0;

    //Copia el mazo recibido por la funcion en el temporal
    for (int i = 0; i < amountCards; i++) {
        orderedDeck[i] = Deck[i];
    }

    orderAs(orderedDeck,amountCards);   //Ordena el mazo temporal dejando al final los Ases

    //Suma los puntos de cada carta a la varible points
    for (int i = 0; i < amountCards; i++){
        //Verfica si la carta a sumar es un As o no
        if (orderedDeck[i].cardNumber != A){
            points = points+orderedDeck[i].puntaje;
        }else{
            //Evalua que valor del As usar si 11 o 1
            if (points+11 > 21){
                points = points+1;
            }else{
                points = points+11;
            }
        }
    }

    return points;  //Retorna los puntos del mazo como un entero
}

//Esta funcion aumenta el tamaño del mazo entregado y le agrega una carta al final, la cantidad de veces que se le indique
void getCard(int amountCards, int *dealtCards, int *dealtCardsTarget, myCard Deck[], myCard **target){
    *target = (myCard *)realloc(*target, (*dealtCardsTarget + amountCards) * sizeof(myCard)); //Aumenta el tamaño del arreglo
    //For encargado de repetir el proceso de ingresar una carta al final del arreglo
    for(int i=0 ; i<amountCards ; i++){  
        (*target)[*dealtCardsTarget] = Deck[*dealtCards];   //Ingresa la proxima carta de la pila al mazo del target
        (*dealtCards)++;    //Aumenta la cantidad de cartas repartidas totales
        (*dealtCardsTarget)++;  //Aumenta la cantidad de cartas repartidas al target
    }
}


//Funcion encargada de gestionar si el crupier pide una carta o no
void crupierLogic(myCard Deck[], int *dealtCards, myCard **Crupier, int *dealtCardsCrupier) {
    //Mientras la sumatoria de puntos del crupier no sea mayor a 17 pide cartas
    while (calculatePoints(*Crupier, *dealtCardsCrupier) < 17) {
        getCard(1, dealtCards, dealtCardsCrupier, Deck, Crupier);
    }
}

//Define si gana el jugador o la casa
bool defineWinner(int playerPoints, int crupierPoints){
    //Si el jugador se paso de 21 automaticamente pierde
    if (playerPoints > 21){
        return false;    
    }
    
    //Si el crupier se pasa de 21 el jugador automaticamente gana
    if (crupierPoints > 21){
        return true;
    }

    //Si el jugador tiene mas puntos que el crupier gana el jugador
    if (playerPoints > crupierPoints)
    {
        return true;
    }

    return false; //Si no se cumplio ninguno de los casos quiere decir que el jugador perdio;
    
}

/*VER SI HAY QUE CAMBIARLE EL NOMBRE A LA FUNCION ESTA*/
int gamelogic(){
    srand(time(NULL));
    myCard Deck[52*decks], Crupier[5], Player[5];
    int remaining_cards;
    initDeck(Deck,&remaining_cards);
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

/*void getCard(myCard *deck, int *amountCards) {
    if (*amountCards == MAX_CARDS_DISPLAYED) {
        *amountCards = MAX_CARDS_DISPLAYED;
    }   else {
        deck[*amountCards].cardType = rand() % 4;
        deck[*amountCards].cardNumber = rand() % 13;
        (*amountCards)++;
    }

}*/

/*int calculatePoints(myCard *deck, int *amountCards) {
    int totalPoints = 0;
    for (int i = 0; i < *amountCards; i++) {
        totalPoints = totalPoints + deck[i].cardNumber+1; 
    }
    return totalPoints;
}*/

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
void startRound(int *amountCardsPlayer, int *amountCardsCrupier, int *remainingCards, int *dealtCards, int *playerPoints, int *crupierPoints, int *bet, myCard **playerDeck, myCard **crupierDeck, myCard Deck[], gameState *currentGame) {
    *amountCardsPlayer = 0;
    *amountCardsCrupier = 0;
    *bet = 100;
    initDeck(Deck,remainingCards);
    shuffleDeck(Deck,*remainingCards);
    getCard(2, dealtCards, amountCardsPlayer, Deck, playerDeck);
    getCard(1, dealtCards, amountCardsCrupier, Deck, crupierDeck);
    *playerPoints = calculatePoints(*playerDeck, *amountCardsPlayer);
    *crupierPoints = calculatePoints(*crupierDeck, *amountCardsCrupier);
    currentGame->playerWin = false;
    currentGame->roundEnd = false;
    currentGame->allowMoneyUpdate = false;
    currentGame->playerBlackjack = false;
}

/////////////////////////////////////////////////////////////////////////////////////