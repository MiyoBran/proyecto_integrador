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

Texture2D hearts[13];
Texture2D clubs[13];
Texture2D diamonds[13];
Texture2D spades[13];

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int MAX_CARDS_DISPLAYED;

bool playerWin = false;
bool roundEnd = false;
bool gameStop = false;                           //THIS VARIABLE STOPS THE WINDOW FROM OPENING
bool alreadyBet = false;

int x_playerPosition = 0;                                               //Player's text x position
int x_dealerPosition = 0;                                               //Dealer's text x position 
int y_position = 520;                                                   //General text y position
int buttonXPosition = 100;                                              //Difference between window "wall" and buttons
int buttonYPosition = 290;                                              //Difference between window "roof" and buttons

const char *diamondsFiles[13] = {
                                "Blackjack cards/Diamonds/Diamonds ace.png",
                                "Blackjack cards/Diamonds/Diamonds 2.png",
                                "Blackjack cards/Diamonds/Diamonds 3.png",
                                "Blackjack cards/Diamonds/Diamonds 4.png",
                                "Blackjack cards/Diamonds/Diamonds 5.png",
                                "Blackjack cards/Diamonds/Diamonds 6.png",
                                "Blackjack cards/Diamonds/Diamonds 7.png",
                                "Blackjack cards/Diamonds/Diamonds 8.png",
                                "Blackjack cards/Diamonds/Diamonds 9.png",
                                "Blackjack cards/Diamonds/Diamonds 10.png",
                                "Blackjack cards/Diamonds/Diamonds joker.png",
                                "Blackjack cards/Diamonds/Diamonds queen.png",
                                "Blackjack cards/Diamonds/Diamonds king.png"
};
const char *heartsFiles[13] = {
                                "Blackjack cards/Hearts/Hearts ace.png",
                                "Blackjack cards/Hearts/Hearts 2.png",
                                "Blackjack cards/Hearts/Hearts 3.png",
                                "Blackjack cards/Hearts/Hearts 4.png",
                                "Blackjack cards/Hearts/Hearts 5.png",
                                "Blackjack cards/Hearts/Hearts 6.png",
                                "Blackjack cards/Hearts/Hearts 7.png",
                                "Blackjack cards/Hearts/Hearts 8.png", 
                                "Blackjack cards/Hearts/Hearts 9.png", 
                                "Blackjack cards/Hearts/Hearts 10.png",
                                "Blackjack cards/Hearts/Hearts joker.png",
                                "Blackjack cards/Hearts/Hearts queen.png", 
                                "Blackjack cards/Hearts/Hearts king.png"
};
const char *clubsFiles[13] = {
                                "Blackjack cards/Clubs/Clubs ace.png",
                                "Blackjack cards/Clubs/Clubs 2.png",
                                "Blackjack cards/Clubs/Clubs 3.png",
                                "Blackjack cards/Clubs/Clubs 4.png",
                                "Blackjack cards/Clubs/Clubs 5.png",
                                "Blackjack cards/Clubs/Clubs 6.png",
                                "Blackjack cards/Clubs/Clubs 7.png",
                                "Blackjack cards/Clubs/Clubs 8.png",
                                "Blackjack cards/Clubs/Clubs 9.png",
                                "Blackjack cards/Clubs/Clubs 10.png",
                                "Blackjack cards/Clubs/Clubs joker.png",
                                "Blackjack cards/Clubs/Clubs queen.png",
                                "Blackjack cards/Clubs/Clubs king.png"
};
const char *spadesFiles[13] = {
                                "Blackjack cards/Spades/Spades ace.png",
                                "Blackjack cards/Spades/Spades 2.png",
                                "Blackjack cards/Spades/Spades 3.png",
                                "Blackjack cards/Spades/Spades 4.png",
                                "Blackjack cards/Spades/Spades 5.png",
                                "Blackjack cards/Spades/Spades 6.png",
                                "Blackjack cards/Spades/Spades 7.png",
                                "Blackjack cards/Spades/Spades 8.png",
                                "Blackjack cards/Spades/Spades 9.png",
                                "Blackjack cards/Spades/Spades 10.png",
                                "Blackjack cards/Spades/Spades joker.png",
                                "Blackjack cards/Spades/Spades queen.png",
                                "Blackjack cards/Spades/Spades king.png"
};
//This are pointers to strings. The LoadTexture function needs this type of variable



void initializeGraphicsConfig(){
    char *stringScreenWidth = getconfig("SCREEN_WIDTH");
    char *stringScreenHeight = getconfig("SCREEN_HEIGHT");
    char *stringMaxCards = getconfig("MAX_CARDS_DISPLAYED");

    if (stringScreenWidth != NULL) {
        SCREEN_WIDTH = atoi(stringScreenWidth);
        free(stringScreenWidth);
    } else {
        printf("SCREEN_WIDTH no encontrado en la configuracion. Usando valor predeterminado\n");
        SCREEN_WIDTH = 1280;  // Default value
    }

    if (stringScreenHeight != NULL) {
        SCREEN_HEIGHT = atoi(stringScreenHeight);
        free(stringScreenHeight);
    } else {
        printf("SCREEN_HEIGHT not found in configuration. Using default value.\n");
        SCREEN_HEIGHT = 720;  // Default value
    }

    if (stringMaxCards != NULL) {
        MAX_CARDS_DISPLAYED = atoi(stringMaxCards);
        free(stringMaxCards);
    } else {
        printf("MAX_CARDS_DISPLAYED no encontrado en la configuracion. Usando valor predeterminado.\n");
        MAX_CARDS_DISPLAYED = 5;
    }
}

void loadCardTextures() {               //Loads the textures of the cards into four Texture2D arrays.
    for (int i = 0; i < 13; i++) {
        hearts[i] = LoadTexture(heartsFiles[i]);
        clubs[i] = LoadTexture(clubsFiles[i]);
        diamonds[i] = LoadTexture(diamondsFiles[i]);
        spades[i] = LoadTexture(spadesFiles[i]);
        if (clubs[i].id == 0) {
            printf("\n\n%s texture not loaded properly\n\n", clubsFiles[i]);
        }
        if (hearts[i].id == 0) {
            printf("\n\n%s texture not loaded properly\n\n", heartsFiles[i]);
        }
        if (diamonds[i].id == 0) {
            printf("\n\n%s texture not loaded properly\n\n", diamondsFiles[i]);
        }
        if (spades[i].id == 0) {
            printf("\n\n%s texture not loaded properly\n\n", spadesFiles[i]);
        }
    }
}


void unloadCardTextures() {                 //Unloads the textures used by the cards, think of it like dynamic memory
    for (int i = 0; i < 13; i++) {
        UnloadTexture(hearts[i]);
        UnloadTexture(clubs[i]);
        UnloadTexture(diamonds[i]);
        UnloadTexture(spades[i]);
    }
}


void printCard(int *amountCards, myDeck *cartas1, int playerCropier) {          //Prints cards depending on which side you want
    if (playerCropier == DEALER) {
        for (int i = 0; i < *amountCards; i ++) {
            switch (cartas1[i].cardType) {
                case TREBOL:
                    DrawTexture(clubs[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), VERTICAL_MARGIN*2, WHITE);
                    break;
                case DIAMANTE:
                    DrawTexture(diamonds[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), VERTICAL_MARGIN*2, WHITE);
                    break;
                case CORAZON:
                    DrawTexture(hearts[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), VERTICAL_MARGIN*2, WHITE);
                    break;
                case PICA:
                    DrawTexture(spades[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), VERTICAL_MARGIN*2, WHITE);
                    break;
            }
        }
    }   else {
        for (int i = 0; i < *amountCards; i ++) {
            switch (cartas1[i].cardType) {
                case TREBOL:
                    DrawTexture(clubs[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), SCREEN_HEIGHT-CARD_HEIGHT - VERTICAL_MARGIN, WHITE);
                    break;
                case DIAMANTE:
                    DrawTexture(diamonds[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), SCREEN_HEIGHT-CARD_HEIGHT - VERTICAL_MARGIN, WHITE);
                    break;
                case CORAZON:
                    DrawTexture(hearts[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), SCREEN_HEIGHT-CARD_HEIGHT - VERTICAL_MARGIN, WHITE);
                    break;
                case PICA:
                    DrawTexture(spades[cartas1[i].cardNumber], CARD_WIDTH*(i+1)+(CARD_DISTANCE*i), SCREEN_HEIGHT-CARD_HEIGHT - VERTICAL_MARGIN, WHITE);
                    break;
            }
        }
    }
}



void getBet(int *bet, struct Rectangle betBox, bool *gameButtons, bool *alreadyBet) {                       //Gets set bet number
    Vector2 mousePosition = GetMousePosition();
    Rectangle bet100 = {betBox.x+170, betBox.y-55, 100, 50};
    Rectangle bet200 = {betBox.x+170, betBox.y+20, 100, 50};
    Rectangle bet300 = {betBox.x+170, betBox.y+95, 100, 50};
    for (int i = 0; i < 3; i++) {
        DrawRectangle(betBox.x+170, betBox.y + (75*i)-55, 100, 50, WHITE);
        const char *text = TextFormat("%d", (i+1)*100);
        DrawText(text, betBox.x+175, betBox.y + (75*i)-50, 35, BLACK);
    }
    if((CheckCollisionPointRec(mousePosition, bet100)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
        *bet = 100;
        *gameButtons = false;
        *alreadyBet = true;
    }   else if ((CheckCollisionPointRec(mousePosition, bet200)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
        *bet = 200;
        *gameButtons = false;
        *alreadyBet = true;
    }   else if ((CheckCollisionPointRec(mousePosition, bet300)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
        *bet = 300;
        *gameButtons = false;
        *alreadyBet = true;
    }
}


char *askUserName() {                                           //Asks user's name
    char *userName = NULL; 
    size_t length = 0; 
    printf("Escriba su nickname\nNickname: ");
    getline(&userName, &length, stdin);

    if (userName[length - 1] == '\n') {
        userName[length - 1] = '\0'; 
    }
    return userName;
}

