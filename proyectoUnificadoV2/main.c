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



////////////////////////////////////////////////////////////////

int main() {
    srand(time(NULL));
    initializeGraphicsConfig();                                             //Searches for configuration values
    char *playerName = malloc(4*sizeof(char));
    playerName[0] = '\0';

    bool tableUnloaded = false;                                             //This variable prevents the compiler to keep unloading the table image during
                                                                            //Scoreboard screen

    int charCount = 0;
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score));
    char *scoreFileName = getconfig("archivo_datos");
    if (scoreList == NULL) {
        printf("Error al asignar memoria para lista de puntaje\n");
        return 1;
    }
    if (playerName == NULL) {
        printf("Error al asignar memoria para nombre de usuario\n");
        return 1;
    }
    if (scoreFileName == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        return 1;
    }
    
    myDeck playerDeck[MAX_CARDS_DISPLAYED];
    myDeck dealerDeck[MAX_CARDS_DISPLAYED];
    gameState currentGame = {false, false};
    
    int amountCardsPlayer = 0;
    int amountCardsDealer = 0;
    
    int playerPoints = 0;
    int dealerPoints = 0;

    int bet = 0;
    int playerMoney = getPlayerMoney(bet, &currentGame.playerWin);

    buttons gameButtons = {false, false, false, false, false};              //Struct for logic with buttons
    buttonBoxes gameBoxes = {                                               //Struct for logic with buttons

        //      x,                       y,                 wid,         height
        {buttonXPosition      , buttonYPosition      , BUTTON_WIDTH, BUTTON_HEIGHT},          //Hold box
        {buttonXPosition + 200, buttonYPosition + 40 , BUTTON_WIDTH, BUTTON_HEIGHT},          //Bet box
        {buttonXPosition      , buttonYPosition + 60 , BUTTON_WIDTH, BUTTON_HEIGHT},          //Hit box
        {buttonXPosition + 250, buttonYPosition + 110, BUTTON_WIDTH, BUTTON_HEIGHT},          //gameContinue box
        {buttonXPosition + 400, buttonYPosition + 110, BUTTON_WIDTH, BUTTON_HEIGHT},           //gameEnd box
        {SCREEN_WIDTH/3-110, SCREEN_HEIGHT/3+125, BUTTON_WIDTH+40, BUTTON_HEIGHT+10},     //menuPlay box
        {SCREEN_WIDTH/3-110, SCREEN_HEIGHT/3+200, BUTTON_WIDTH+235, BUTTON_HEIGHT+10},     //menuScoreboard box
        {SCREEN_WIDTH/3-110, SCREEN_HEIGHT/3+275, BUTTON_WIDTH+15, BUTTON_HEIGHT+10}      //menuQuit box
    };
    Vector2 mousePosition = { 0.0f, 0.0f };                             //Initialize variable that tracks mouse position.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blackjack");               //Initialize Window parameters.
    Texture2D texture_table = LoadTexture("Blackjack cards/Table blank.png");
    SetTargetFPS(60); 
    loadCardTextures();
    


    while (!WindowShouldClose())                                //Loop to maintain window working
    {

        mousePosition = GetMousePosition();                             //Update mouse position
         if (texture_table.id == 0 && !tableUnloaded) {
            texture_table = LoadTexture("Blackjack cards/Table blank.png");

        } 
        DrawTexture(texture_table, 0, 0, WHITE);
        switch (screenState) {
            case 0:                         //Main menu
                BeginDrawing();

                DrawText("BLACKJACK", SCREEN_WIDTH/3-125, 100, 125, GOLD);
                DrawText("Menu principal:", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+50, 60, BLACK);
                DrawRectangle(gameBoxes.menuPlay.x, gameBoxes.menuPlay.y, gameBoxes.menuPlay.width, gameBoxes.menuPlay.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuPlay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 1;
                    startRound(&amountCardsPlayer, &amountCardsDealer, &playerPoints, &dealerPoints, &bet, playerDeck, dealerDeck, &currentGame);
                }
                DrawText("Jugar", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+125, 58, BLACK);
                DrawRectangle(gameBoxes.menuScoreboard.x, gameBoxes.menuScoreboard.y, gameBoxes.menuScoreboard.width, gameBoxes.menuScoreboard.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuScoreboard) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 3;
                }
                DrawText("Scoreboard", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+200, 60, BLACK);
                DrawRectangle(gameBoxes.menuQuit.x, gameBoxes.menuQuit.y, gameBoxes.menuQuit.width, gameBoxes.menuQuit.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuQuit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 4;
                }
                DrawText("Salir", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+275, 60, BLACK);

                EndDrawing();
                break;
            case 1:                         //Play
                BeginDrawing();
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
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.betBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !currentGame.roundEnd) {
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
                    
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.hitBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !currentGame.roundEnd) {
                        gameButtons.hitButton = true;
                    }
                    if (gameButtons.hitButton) {   
                        getCard(playerDeck, &amountCardsPlayer);
                        playerPoints = calculatePoints(playerDeck, &amountCardsPlayer);
                        gameButtons.hitButton = false;
                    }

                    DrawRectangle(gameBoxes.holdBox.x, gameBoxes.holdBox.y, gameBoxes.holdBox.width, gameBoxes.holdBox.height, WHITE);          //Everything about hold functions
                    DrawText("Hold", gameBoxes.holdBox.x+10, gameBoxes.holdBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.holdBox )) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !currentGame.roundEnd) {
                        gameButtons.holdButton = true;
                    }
                    if (gameButtons.holdButton) {
                        for (int i = 0; i < MAX_CARDS_DISPLAYED; i++) {
                            getCard(dealerDeck, &amountCardsDealer);
                            dealerPoints = calculatePoints(dealerDeck, &amountCardsDealer);
                        }
                                                            //Functions related to logic with dealer go here. Only works after user clicked on hold
                        currentGame.roundEnd = true;
                        gameButtons.holdButton = false;
                    }
                    
                    if (playerPoints > 21) {
                        currentGame.roundEnd = true;        
                        currentGame.playerWin = false;
                    }


                    printCard(&amountCardsPlayer, playerDeck, PLAYER);                       //Both of this functions print the current cards of both parties
                    printCard(&amountCardsDealer, dealerDeck, DEALER);
                    
                }
                

                if (currentGame.roundEnd) {                                                                 //Checks if round has ended
                    playerMoney = getPlayerMoney(bet, &currentGame.playerWin);
                    DrawRectangle(0, buttonYPosition, SCREEN_WIDTH, 200, RED);
                    DrawText("Quiere continuar el juego?", SCREEN_HEIGHT/2, buttonYPosition+75, 35, BLACK);
                    DrawRectangle(gameBoxes.gameContinueBox.x, gameBoxes.gameContinueBox.y, gameBoxes.gameContinueBox.width, gameBoxes.gameContinueBox.height, WHITE);
                    DrawText("Seguir", gameBoxes.gameContinueBox.x + 10, gameBoxes.gameContinueBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameContinueBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameContinueButton = true;
                    }
                    if (gameButtons.gameContinueButton) {                               //If player continues playing, the variables are set back to their inital value
                        startRound(&amountCardsPlayer, &amountCardsDealer, &playerPoints, &dealerPoints, &bet, playerDeck, dealerDeck, &currentGame);
                        gameButtons.gameContinueButton = false;

                    }

                    DrawRectangle(gameBoxes.gameEndBox.x, gameBoxes.gameEndBox.y, gameBoxes.gameEndBox.width, gameBoxes.gameEndBox.height, WHITE);
                    DrawText("Salir", gameBoxes.gameEndBox.x + 15, gameBoxes.gameEndBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameEndBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameEndButton = true;

                    }
                    if (gameButtons.gameEndButton) {   
                        screenState = 2;
                        gameButtons.gameEndButton = false;
                        break;
                    }
                    currentGame.playerWin = compareScores(playerPoints, dealerPoints);
                    if (currentGame.playerWin) {
                        DrawText("Usted gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    }   else if (!currentGame.playerWin && playerPoints > 21) {
                        DrawText("Se paso de 21 puntos\nLa casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    } else {
                        DrawText("La casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    }

                }
                EndDrawing();
                break;
            case 2:                         //Finish game
            startRound(&amountCardsPlayer, &amountCardsDealer, &playerPoints, &dealerPoints, &bet, playerDeck, dealerDeck, &currentGame);
            UnloadTexture(texture_table);
            texture_table.id = 0;
            tableUnloaded = true;

            rankingImport(scoreList, scoreFileName);
            getUserName(playerName, &charCount); 
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Escriba su nombre, maximo 3 letras", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3, 40, BLUE);
            if (charCount == 0) {
                DrawText("...", SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 40, BLUE);
            }   else {
                DrawText(TextFormat("%s", playerName), SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 40, BLUE);
            }
            DrawText(TextFormat("%d/3", charCount), SCREEN_WIDTH/3, SCREEN_HEIGHT/2+50, 40, BLUE);
            DrawText("Presione enter para continuar.", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/2+200, 40, BLUE);
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER)){
                    Score newPlayer;
                if (playerName[0] == '\0') {
                    newPlayer = crearScore("UNI", playerMoney); // Convierte nombre sin ingresar y dinero a un score
                }   else {
                    newPlayer = crearScore(playerName, playerMoney); // Convierte nombre y dinero a un Score
                }

                checkScore(scoreList, newPlayer, scoreFileName); // Verifica y agrega el jugador
                rankingSave(scoreList, scoreFileName);
                charCount = 0;
                screenState = 3;
            }
            break;
            case 3:                         //  Check scoreboard
                if (texture_table.id != 0 && !tableUnloaded) {                   //Checks if the player has been through the name asking part, to see if it needs to unload the table
                    UnloadTexture(texture_table);
                    texture_table.id = 0;
                    tableUnloaded = true;
                }
                const char *playerRankings = '\0';
                const char *playerNames = '\0';
                const char *playerScores = '\0';
                loadRankingVariables(&playerRankings, &playerNames, &playerScores);
                if (!showGraphicRanking(playerRankings, playerNames, playerScores)) {
                    playerName[0] = '\0';
                    tableUnloaded = false;
                    screenState = 0;
                }
                break;
            case 4:                         //Exit
                    unloadCardTextures();
                    CloseWindow();
                break;
        }
    }

    for (int i = 0; i < MAX_CARDS_DISPLAYED; i++) {
        printf("\nPlayer = [%d], [%d]\n", playerDeck[i].cardNumber, playerDeck[i].cardType);
        printf("\nDealer = [%d], [%d]\n", dealerDeck[i].cardNumber, dealerDeck[i].cardType);
    }
    //All of this printf functions are to test, can be deleted later

    printf("------------------\n%d\n------------------", screenState);
    printf("%s", playerName);
    showRanking(scoreList, scoreFileName);
    free(scoreList);
    free(playerName);
    free(scoreFileName);
    return 0;
}

/*
            const char *text = TextFormat("%d", plata);     // Function to write variables on screen

*/