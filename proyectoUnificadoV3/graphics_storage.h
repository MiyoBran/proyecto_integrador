#ifndef graphics_storage
#define graphics_storage

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////

#include "config.h"
#include "scoreboard.h"
#include "graphics_storage.h"
#include "gamelogic.h"

/////////////////////////////////////////////////////////////////////////////////////

#define DISTANCE_CARDS 20
#define CARD_DISTANCE 20
#define CARD_WIDTH 120
#define CARD_HEIGHT 170
#define BUTTON_WIDTH  145
#define BUTTON_HEIGHT 50
#define VERTICAL_MARGIN 50

typedef enum {                                 
    DEALER, PLAYER
}   whichSidetoPrint;
//This enum is for the printCard function, it tells the function which side it should print the cards.

typedef struct {
    Rectangle holdBox;
    Rectangle betBox;
    Rectangle hitBox;
    Rectangle gameContinueBox;
    Rectangle gameEndBox;
    Rectangle menuPlay;
    Rectangle menuScoreboard;
    Rectangle menuQuit;
    Rectangle menuRecord;
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
extern Texture2D upsideCards[9];
//Variables that hold all the card textures

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
//Variables searched in .env file

extern int screenState;
extern bool alreadyBet;                                                   //Variable to check if player already made bet

extern int x_playerPosition;                                             //Player's text 'x' position
extern int x_dealerPosition;                                             //Dealer's text 'x' position 
extern int y_position;                                                   //General text 'y' position
extern int buttonXPosition;                                              //Difference between window "wall" and buttons
extern int buttonYPosition;                                              //Difference between window "roof" and buttons

//Searches for values in the .env file config
void initializeGraphicsConfig();
//Chooses a random index for the upside down cards
int chooseRandomUpsideCard();
//Loads the textures of the cards into five Texture2D arrays.
void loadCardTextures();
//Unloads the textures used by the cards
void unloadCardTextures();
//Prints cards depending on which side you want
void printCard(int *amountCards, myCard *cartas1, int playerCropier);
//Gets set bet number
void getBet(int *bet, struct Rectangle betBox, bool *gameButtons, bool *alreadyBet);
//Gets user name
void getUserName(char *userName, int *charCount);
//Loads scoreboard into three variables
void loadRankingVariables(const char **playerRankings, const char **playerNames, const char **playerScores);
//Displays three variables set in loadRankingVariables
bool showGraphicRanking(const char *playerRankings, const char *playerNames, const char *playerScores);
//Shows game instructions
bool showGameInstructions(Texture2D texture_table);



#endif // graphics_storage