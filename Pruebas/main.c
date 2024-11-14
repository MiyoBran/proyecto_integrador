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

/////////////////////////////////////////////////////////////////////////////////////
bool randomWin(bool playerWin) {
    int aaaa = rand() % 2;
    if (aaaa == 1) {
        playerWin = true;
    }   else {
        playerWin = false;
    }
    return playerWin;
}
//function to test player or dealer win

int getPlayerMoney(int bet, bool playerWin) {
    int money = 5000;
    if (playerWin) {
        money = money + bet;
    }   else {
        money = money - bet;
    }
    return money;
}

void getCard(myDeck *deck) {
    for (int i = 0; i < MAX_CARDS_DISPLAYED; i++) {
        deck[i].cardType = rand() % 4;
        deck[i].cardNumber = rand() % 13;
    }

}

int calculatePoints(myDeck *deck, int *amountCards) {
    int totalPoints = 0;
    for (int i = 0; i < *amountCards; i++) {
        totalPoints = totalPoints + deck[i].cardNumber; 
    }
    return totalPoints;
}
/////////////////////////////////////////////////////////////////////////////////////



int main() {
    srand(time(NULL));
    initializeGraphicsConfig();                                             //Busca los valores de configuracion
    int charCount = 0;
    char *userName = malloc(4*sizeof(char));
    myDeck playerDeck[MAX_CARDS_DISPLAYED];
    myDeck dealerDeck[MAX_CARDS_DISPLAYED];
    int amountCardsPlayer = 2;
    int amountCardsDealer = 1;
    int playerPoints = 0;
    int dealerPoints = 0;
    int bet = 0;
    int playerMoney = getPlayerMoney(bet, playerWin);
    getCard(dealerDeck);                                                    //Draw entire dealer's deck
    getCard(playerDeck);                                                    //Draw entire player's deck

    buttons gameButtons = {false, false, false, false, false};              //Struct for logic with buttons
    buttonBoxes gameBoxes = {                                               //Struct for logic with buttons

        //      x,                       y,                 wid,         heig
        {buttonXPosition      , buttonYPosition      , BUTTON_WIDTH, BUTTON_HEIGHT},          //Hold box
        {buttonXPosition + 200, buttonYPosition + 40 , BUTTON_WIDTH, BUTTON_HEIGHT},          //Bet box
        {buttonXPosition      , buttonYPosition + 60 , BUTTON_WIDTH, BUTTON_HEIGHT},          //Hit box
        {buttonXPosition + 250, buttonYPosition + 110, BUTTON_WIDTH, BUTTON_HEIGHT},          //gameContinue box
        {buttonXPosition + 400, buttonYPosition + 110, BUTTON_WIDTH, BUTTON_HEIGHT}           //gameEnd box
    };
    Vector2 mousePosition = { 0.0f, 0.0f };                             //Initialize variable that tracks mouse position.

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blackjack");               //Initialize Window parameters.
    SetTargetFPS(60); 
    loadCardTextures();
    Texture2D texture_table = LoadTexture("Blackjack cards/Table blank.png");


    while (!WindowShouldClose())                                //Loop to maintain window working
    {
        mousePosition = GetMousePosition();                             //Update mouse position

        switch (gameState) {
            case 0:                         //Main menu
                BeginDrawing();
                DrawTexture(texture_table, 0, 0, WHITE);                        //Loads table texture into the screen
                DrawText("BLACKJACK", SCREEN_WIDTH/3-125, 100, 125, GOLD);
                DrawText("Menu principal:", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+50, 60, BLACK);
                DrawText("Jugar", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+125, 60, BLACK);
                DrawText("Scoreboard", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+200, 60, BLACK);
                DrawText("Salir", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+275, 60, BLACK);
                EndDrawing();
                break;
            case 1:                         //Play
                BeginDrawing();

                DrawTexture(texture_table, 0, 0, WHITE);                    //Loads table texture into the screen
                const char *moneyPrint = TextFormat("Dinero: %d", playerMoney);     
                const char *playerPointPrint = TextFormat("Puntos: %d", playerPoints);
                const char *dealerPointPrint = TextFormat("Puntos: %d", dealerPoints);
                const char *betPrint = TextFormat("Apuesta: %d", bet);

                if (amountCardsPlayer <= 2) {
                    x_playerPosition = (CARD_WIDTH*3)+50;
                }   else {
                    x_playerPosition = (CARD_WIDTH + CARD_DISTANCE)*(amountCardsPlayer+1);
                }

                if (amountCardsDealer <= 2) {
                    x_dealerPosition = (CARD_WIDTH*3)+50;
                }   else {
                    x_dealerPosition = (CARD_WIDTH + CARD_DISTANCE)*(amountCardsDealer+1);
                }
                DrawText(moneyPrint, x_playerPosition, y_position, 40, BLACK);                      //Relative coordinates of total money coordinates
                DrawText(betPrint, x_playerPosition, y_position+60, 40, BLACK);                     //Relative coordinates of bet coordinates
                DrawText(playerPointPrint, x_playerPosition, y_position+120, 40, BLACK);            //Relative coordinates of points coordinates
                DrawText(dealerPointPrint, x_dealerPosition, y_position-400, 40, BLACK);


                DrawRectangle(gameBoxes.betBox.x , gameBoxes.betBox.y, gameBoxes.betBox.width, gameBoxes.betBox.height, WHITE);             //Everything about bet functions
                DrawText ("Apostar", gameBoxes.betBox.x+5, gameBoxes.betBox.y, 35, BLACK);
                if (!alreadyBet || amountCardsPlayer == 2) {
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.betBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !roundEnd) {
                        gameButtons.betButton = true;
                    }
                    if (gameButtons.betButton) {
                        DrawText("Cuanto quiere apostar?", gameBoxes.betBox.x+280, gameBoxes.betBox.y, 30, BLACK);
                            getBet(&bet, gameBoxes.betBox, &gameButtons.betButton, &alreadyBet);
                    }
                }
                //This if control structure works so that player bets at least 100 to start the game
                if (bet != 0) {
                    DrawRectangle(gameBoxes.hitBox.x, gameBoxes.hitBox.y, gameBoxes.hitBox.width, gameBoxes.hitBox.height, WHITE);              //Everything about hit functions
                    DrawText("Hit", gameBoxes.hitBox.x+10, gameBoxes.hitBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.hitBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !roundEnd) {
                        gameButtons.hitButton = true;
                        amountCardsPlayer++;
                        if (amountCardsPlayer > MAX_CARDS_DISPLAYED) {
                            amountCardsPlayer = MAX_CARDS_DISPLAYED;
                        }
                    }
                    if (gameButtons.hitButton) {   

                        playerPoints = calculatePoints(playerDeck, &amountCardsPlayer);
                        gameButtons.hitButton = false;
                    }

                    DrawRectangle(gameBoxes.holdBox.x, gameBoxes.holdBox.y, gameBoxes.holdBox.width, gameBoxes.holdBox.height, WHITE);          //Everything about hold functions
                    DrawText("Hold", gameBoxes.holdBox.x+10, gameBoxes.holdBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.holdBox )) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !roundEnd) {
                        gameButtons.holdButton = true;
                    }
                    if (gameButtons.holdButton) {
                        //amountCardsDealer = dealerCards();
                        //int dealerPoint = dealerPoints();   //To change name */
                                                            //Functions related to logic with dealer go here. Only works after user clicked on hold
                        roundEnd = true;
                        //playerWin = randomWin(playerWin);
                        gameButtons.holdButton = false;
                    }
                    if (playerPoints > 21) {                            //PLAYER LOSES
                                                                        //HAVE TO PRINT PLAYER LOSES             
                        roundEnd = true;
                        playerWin = false;
                    }

                    printCard(&amountCardsPlayer, playerDeck, PLAYER);                       //This prints the cards that correspond to the user, variable to decide
                    printCard(&amountCardsDealer, dealerDeck, DEALER);
                    
                }
                

                if (roundEnd) {                                               //End Round is a variable that I'm still thinking about, will probably need to wait for logical part
                    playerMoney = getPlayerMoney(bet, playerWin);
                    DrawRectangle(0, buttonYPosition, SCREEN_WIDTH, 200, RED);
                    DrawText("Quiere continuar el juego?", SCREEN_HEIGHT/2, buttonYPosition+75, 35, BLACK);
                    DrawRectangle(gameBoxes.gameContinueBox.x, gameBoxes.gameContinueBox.y, gameBoxes.gameContinueBox.width, gameBoxes.gameContinueBox.height, WHITE);
                    DrawText("Seguir", gameBoxes.gameContinueBox.x + 10, gameBoxes.gameContinueBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameContinueBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameContinueButton = true;
                    }
                    if (gameButtons.gameContinueButton) {   
                        amountCardsPlayer = 2;
                        amountCardsDealer = 1;
                        bet = 100;
                        getCard(playerDeck);
                        getCard(dealerDeck);
                        playerPoints = calculatePoints(playerDeck, &amountCardsPlayer);
                        //Dealer points function

                        roundEnd = false;
                        playerWin = false;
                        gameButtons.gameContinueButton = false;

                    }

                    DrawRectangle(gameBoxes.gameEndBox.x, gameBoxes.gameEndBox.y, gameBoxes.gameEndBox.width, gameBoxes.gameEndBox.height, WHITE);
                    DrawText("Salir", gameBoxes.gameEndBox.x + 15, gameBoxes.gameEndBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameEndBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameEndButton = true;

                    }
                    if (gameButtons.gameEndButton) {   
                        gameState = 2;
                        gameButtons.gameEndButton = false;
                        break;
                    }
                    if (playerWin) {
                        DrawText("Usted gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    }   else if (playerPoints > 21) {
                        DrawText("Se paso de 21 puntos\nLa casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    } else {
                        DrawText("La casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    }

                }
                EndDrawing();
                break;
            case 2:                         //Finish game
            getUserName(userName, &charCount); 
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Escriba su nombre, maximo 3 letras", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3, 40, BLUE);
            if (charCount == 0) {
                DrawText("...", SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 40, BLUE);
            }   else {
                DrawText(TextFormat("%s", userName), SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 40, BLUE);
            }
            DrawText(TextFormat("%d/3", charCount), SCREEN_WIDTH/3, SCREEN_HEIGHT/2+50, 40, BLUE);
            DrawText("Presione enter para continuar.", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/2+200, 40, BLUE);
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER)){
                //SOMETHING
                gameState = 3;
            }
            break;
            case 3:                         //  Check scoreboard
                const char *playerRankings = NULL;
                const char *playerNames = NULL;
                const char *playerScores = NULL;
                loadRankingVariables(&playerRankings, &playerNames, &playerScores);
                if (!showGraphicRanking(playerRankings, playerNames, playerScores)) gameState = 0;
                break;
            case 4:                         //Exit
                    unloadCardTextures();
                    UnloadTexture(texture_table);
                    CloseWindow();
                break;
        }
    }
    



    //userName = getUserName(userName, &charCount);                                   //Function that asks user to input their name after game ends
    // Scoreboard functions go here?

    for (int i = 0; i < MAX_CARDS_DISPLAYED; i++) {
        printf("\nPlayer = [%d], [%d]\n", playerDeck[i].cardNumber, playerDeck[i].cardType);
        printf("\nDealer = [%d], [%d]\n", dealerDeck[i].cardNumber, dealerDeck[i].cardType);
    }
    //All of this printf functions are to test, can be deleted later

    printf("------------------\n%d\n------------------", gameState);
    printf("%s", userName);
    free(userName);
    return 0;
}

/*
            const char *text = TextFormat("%d", plata);     // Function to write variables on screen
            DrawText(text, 760, 540, 40, BLACK);            // Money coordinates
            DrawText(text, 800, 600, 40, BLACK);            // Bet coordinates

            DrawTexture(clubs[0], 133, 82, WHITE);          //Dealers's first card position
            DrawTexture(clubs[0], 267, 82, WHITE);          //Dealers's second card position
            DrawTexture(clubs[0], 400, 82, WHITE);          //Dealers's third card position

            DrawTexture(clubs[0], 133, 512, WHITE);         //Player's first card position
            DrawTexture(clubs[0], 267, 512, WHITE);         //Player's second card position
            DrawTexture(clubs[0], 400, 512, WHITE);         //Player's third card position
            Succesion to print cards with a 'for' has to be "133*(i+1)"

*/