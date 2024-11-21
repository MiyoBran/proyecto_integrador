#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h> /// para caracteres anchos / emoticones?
#include "gamelogic.h"



////////////////////////Funciones propias////////////////////////
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
#include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI
////////////////////////Funciones propias////////////////////////

//Funcion que mezcla el mazo
void shuffleDeck(myDeck Deck[], int n){
    for (int i = n - 1; i > 0; i--) {
        // Genera un índice aleatorio entre 0 e i
        int j = rand() % (i + 1);
        
        // Intercambia los elementos en las posiciones i y j
        myDeck temp = Deck[i];
        Deck[i] = Deck[j];
        Deck[j] = temp;
    }
}

void initDeck(myDeck Deck[],int *remaining_cards/*, myDeck Crupier[], myDeck Player[]*/){
    int index = 0;
    for (int i = 0; i < (4*decks); i++)
    {
        for (int j = 0; j < (13*decks); j++)
        {
            Deck[index].cardType = i;
            Deck[index].cardNumber = j;
            if(j <= DIEZ){
                Deck[index].puntaje = j+1;
            }else{
                Deck[index].puntaje = 10;
            }
            index++;
        }
    }
    (*remaining_cards) = 52*decks;
}

void orderAs(myDeck Deck[], int amountCards) {
    myDeck temp;
    bool flag = true;

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

int calculatePoints(myDeck Deck[], int amountCards){
    myDeck orderedDeck[amountCards];
    int points = 0;

    for (int i = 0; i < amountCards; i++) {
        orderedDeck[i] = Deck[i];
    }

    orderAs(orderedDeck,amountCards);

    for (int i = 0; i < amountCards; i++){
        if (orderedDeck[i].cardNumber != A){
            points = points+orderedDeck[i].puntaje;
        }else{
            if (points+11 > 21){
                points = points+1;
            }else{
                points = points+11;
            }
        }
    }

    return points;
}

void getCard(int countCard, int *dealtCards, int *dealtCardsTarget, myDeck Deck[], myDeck target[]){
    for(int i=0 ; i<countCard ; i++){    
        target[*dealtCardsTarget]=Deck[*dealtCards]; 
        (*dealtCards)++;
        (*dealtCardsTarget)++;
    }
}

void crupierLogic(myDeck Deck[], int *dealtCards, myDeck Crupier[], int *dealtCardsCrupier){
    while (calculatePoints(Crupier,*dealtCardsCrupier) < 17){
        getCard(1,dealtCards,dealtCardsCrupier,Deck,Crupier);
        (*dealtCards)++;
    }
}

bool blackJack(myDeck Player[]){
    if(calculatePoints(Player,2) == 21){
        return true;
    }
    return false;
}

bool defineWinner(int playerPoints, int crupierPoints){
    if (playerPoints > 21){
        return false;    
    }
    
    if (crupierPoints > 21){
        return true;
    }

    if (playerPoints > crupierPoints)
    {
        return true;
    }

    return false;
    
}


/*VER SI HAY QUE CAMBIARLE EL NOMBRE A LA FUNCION ESTA*/
int gamelogic(){
    srand(time(NULL));
    myDeck Deck[52*decks], Crupier[5], Player[5];
    int remaining_cards;
    initDeck(Deck,&remaining_cards/*,Crupier,Player*/);
}