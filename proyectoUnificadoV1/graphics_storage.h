
#ifndef graphics_storage
#define graphics_storage

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////

#include "scoreboard.h"
#include "graphics_storage.h"
#include "config.h"

/////////////////////////////////////////////////////////////////////////////////////



#define DISTANCE_CARDS 20
#define CARD_DISTANCE 20
#define CARD_WIDTH 120
#define CARD_HEIGHT 170
#define BUTTON_WIDTH  145
#define BUTTON_HEIGHT 50
#define VERTICAL_MARGIN 50


typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;


typedef struct  {
    int cardType;
    int cardNumber;
}   myDeck;



typedef enum {                                 
    DEALER, PLAYER
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



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int MAX_CARDS_DISPLAYED;
//Variables searched in .env file


extern bool playerWin;
extern bool roundEnd;
extern bool gameStop;
extern bool alreadyBet;

extern int ranking;
extern char playerName[];
extern int playerScore;

extern int x_playerPosition;                                               //Player's text x position
extern int x_dealerPosition;                                               //Dealer's text x position 
extern int y_position;                                                   //General text y position
extern int buttonXPosition;                                              //Difference between window "wall" and buttons
extern int buttonYPosition;                                               //Difference between window "roof" and buttons


void initializeGraphicsConfig();
void loadCardTextures();
void unloadCardTextures();
void printCard(int *amountCards, myDeck *cartas1, int playerCropier);
void getBet(int *bet, struct Rectangle betBox, bool *gameButtons, bool *alreadyBet);
char *askUserName();



#endif // graphics_storage