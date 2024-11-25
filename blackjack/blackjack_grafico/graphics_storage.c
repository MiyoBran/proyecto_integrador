#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////Funciones propias////////////////////////

#include "scoreboard.h"
#include "graphics_storage.h"
#include "config.h"
#include "gamelogic.h"
#include "jugador.h"
#include "record.h"

/////////////////////////////////////////////////////////////////////////////////////

Texture2D hearts[13];
Texture2D clubs[13];
Texture2D diamonds[13];
Texture2D spades[13];
Texture2D upsideCards[9];
//Initializes array of variables that are going to hold the cards' images

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
//Declares variables whose values are going to be found in .env file

int screenState = 0;                              //Variable that changes screens
bool alreadyBet = false;                          //Checks if the player made a bet

int x_playerPosition = 0;                                               //Player's text x position
int x_crupierPosition = 0;                                               //Dealer's text x position 
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
const char *upsideCardsFiles[9] = {
                                "Blackjack cards/Upside down cards/card1.png",
                                "Blackjack cards/Upside down cards/card2.png",
                                "Blackjack cards/Upside down cards/card3.png",
                                "Blackjack cards/Upside down cards/card4.png",
                                "Blackjack cards/Upside down cards/card5.png",
                                "Blackjack cards/Upside down cards/card6.png",
                                "Blackjack cards/Upside down cards/card7.png",
                                "Blackjack cards/Upside down cards/card8.png",
                                "Blackjack cards/Upside down cards/card9.png"
};
//This are pointers to strings. The LoadTexture function needs this type of variable


//Searches for values in the .env file config
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

int chooseRandomUpsideCard() {
    int index = rand() % 9;
    return index;
}

//Loads the textures of the cards into four Texture2D arrays.
void loadCardTextures() {                                                                  
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
    for (int i = 0; i < 9; i++) {
        upsideCards[i] =  LoadTexture(upsideCardsFiles[i]);
        if (upsideCards[i].id == 0) {
            printf("\n\n%s texture not loaded properly\n\n", upsideCardsFiles[i]);
        }
    }
}

//Unloads the textures used by the cards, think of it like dynamic memory
void unloadCardTextures() {                                                                 
    for (int i = 0; i < 13; i++) {
        UnloadTexture(hearts[i]);
        UnloadTexture(clubs[i]);
        UnloadTexture(diamonds[i]);
        UnloadTexture(spades[i]);
    }
    for (int i = 0; i < 9; i++) {
        UnloadTexture(upsideCards[i]);
    }
}

//Prints cards depending on which side you want
void printCard(int *amountCards, myCard *cartas1, int playerCropier) {                       
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

//Gets set bet number
void getBet(int *bet, struct Rectangle betBox, bool *gameButtons, bool *alreadyBet) { 
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

//Gets user name
void getUserName(char *userName, int *charCount) {
    int key = GetCharPressed();
    if ((key >= 32) && (key <= 125) && (*charCount < 3)) {
        userName[*charCount] = (char)key;
        userName[(*charCount)+1] = '\0';
        (*charCount)++;
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        (*charCount)--;
        if (*charCount < 0) *charCount = 0;

        userName[*charCount] = '\0';
    }
}

//Loads scoreboard into three variables
void loadRankingVariables(const char **playerRankings, const char **playerNames, const char **playerScores) { 
    static char allRankings[100] = "";
    static char allNames[300] = "";
    static char allScores[300] = "";

    Score scoreList[TOTAL_REGISTROS] = {0};
    char *nombreArchivo = getconfig("archivo_ranking");
    if (nombreArchivo == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        return;
    }

   rankingImport(scoreList, nombreArchivo);

    allRankings[0] = '\0';
    allNames[0] = '\0';
    allScores[0] = '\0';

    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            char temp[100];
            snprintf(temp, sizeof(temp), "%d\n", scoreList[i].ranking);
            strcat(allRankings, temp);

            snprintf(temp, sizeof(temp), "%s\n", scoreList[i].name);
            strcat(allNames, temp);

            snprintf(temp, sizeof(temp), "\t\t%.0f\n", scoreList[i].money);
            strcat(allScores, temp);
        }
    }

    *playerRankings = TextFormat("%s", allRankings);  
    *playerNames = TextFormat("%s", allNames);  
    *playerScores = TextFormat("%s", allScores);  

    free(nombreArchivo);
}

//Loads game's instructions
char *loadGameInstructions(char *instructionsFile) {
    FILE *file = fopen(instructionsFile, "r");          //Opens the file reglas.txt
    if (!file) {
        printf("No se pudo abrir el archivo: %s\n", instructionsFile);
        return NULL;
    }

    fseek(file, 0, SEEK_END);                           //Takes the file variable to the end of reglas.txt
    long instructionSize = ftell(file);                 //Loads the amount of characters the file has
    rewind(file);                                       //Takes file to the start of reglas.txt

    char *buffer = malloc(instructionSize + 1);         //Dynamically assigns memory to a buffer based on the contents of reglas.txt, plus enough for \0 char
    if (!buffer) {
        printf("No se pudo asignar memoria para el buffer de las instrucciones\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, instructionSize, file);            //Reads the contents of the files and writes them into the buffer
    buffer[instructionSize] = '\0';                     //Assigns \0 to the last element of the buffer 

    fclose(file);
    return buffer;
}

//Displays three variables set in loadRankingVariables
bool showGraphicRanking(const char *playerRankings, const char *playerNames, const char *playerScores) { 
    bool showScoreboard = true;
    if (showScoreboard) {
        BeginDrawing();
        ClearBackground(BLACK);  
        DrawText("HIGHSCORE", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 6, 40, RED);
        DrawText(playerRankings, 430, 200, 40, BLUE);
        DrawText(playerNames, 500, 200, 40, DARKBLUE);
        DrawText(playerScores, 600, 200, 40, BLUE);
        DrawText("Presione cualquier tecla para salir", SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 + 270, 40, PURPLE);
        EndDrawing();

        for (int key = KEY_SPACE; key < KEY_KB_MENU; key++) {
            if (IsKeyPressed(key)) {
                showScoreboard = false;
            }
        }
    }
    return showScoreboard;
}

//Shows game instructions
bool showGameInstructions(Texture2D texture_table, const char *rules) {
    bool showInstructions = true;
    if (showInstructions) {
        BeginDrawing();
            DrawTexture(texture_table, 0, 0, WHITE);
            DrawText(rules, SCREEN_WIDTH/3-370, SCREEN_HEIGHT/3-200, 27, RAYWHITE);
            DrawText("Presione cualquier tecla para salir", SCREEN_WIDTH/3-150, SCREEN_HEIGHT/3+350, 35, GOLD);
        EndDrawing();
        for (int key = KEY_SPACE; key < KEY_KB_MENU; key++) {
            if (IsKeyPressed(key)) {
                showInstructions = false;
            }
        }
    }
    return showInstructions;
}
//showGameInstructions(texture_table, rulesContents)




