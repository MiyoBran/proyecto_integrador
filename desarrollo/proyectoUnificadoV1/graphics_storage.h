
#ifndef graphics_storage
#define graphics_storage

#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_CARDS_DISPLAYED 6
#define DISTANCE_CARDS 20
#define CARD_DISTANCE 20
#define CARD_WIDTH 120
#define CARD_HEIGHT 170
#define BUTTON_WIDTH  145
#define BUTTON_HEIGHT 50
#define VERTICAL_MARGIN 50

// ESTO COMENTARLO SI SE COMPILA sin el gamelogic.h en la carpeta
typedef struct  {
    int cardType;
    int cardNumber;
}   myDeck;

// Protoype of a struct containing the specifics of a card.




typedef enum {                                 
    CROUPIER, PLAYER
}   whichSidetoPrint;
//This enum is for the printCard function, it tells the function which side it should print the cards.



/* typedef struct {
    char playerName;
    int playerBet;
    int playerTotalMoney;
    int amountCards;
    myDeck cardDeck[52];
}   gameSpecifics; */



typedef struct {
    Rectangle holdBox;
    Rectangle betBox;
    Rectangle hitBox;
    Rectangle gameContinueBox;
    Rectangle gameEndBox;
}   buttonBoxes;
//Struct for button logic

typedef struct {
    bool holdButton;
    bool betButton;
    bool hitButton;
    bool gameContinueButton;
    bool gameEndButton;
}   buttons;
//Struct for button logic

extern Texture2D hearts[13];
extern Texture2D clubs[13];
extern Texture2D diamonds[13];
extern Texture2D spades[13];


void loadCardTextures();
void unloadCardTextures();
void printCard(int *amountCards, myDeck *cartas1, int playerCropier);
void getBet(int *bet, struct Rectangle betBox, bool *gameButtons, bool *alreadyBet);
char *askUserName();

//////////////////////////////////////////////////////////////////////////////////////////////////////
int playerHit(int *amountCardsPlayer);
int dealerCards();
int getPlayerMoney();
//////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // graphics_storage