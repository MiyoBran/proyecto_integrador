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
    gameState currentGame = {false, false};             //Makes struct that tracks if the player won or if the round ended
    
    /////////////////////////////
    int amountCardsPlayer = 0;
    int amountCardsDealer = 0;
    int playerPoints = 0;
    int dealerPoints = 0;
    int bet = 0;
    int playerMoney = getPlayerMoney(bet, &currentGame.playerWin);
    ////////////////////////////        All of this variables can go into a struct if we really wanted

    buttons gameButtons = {false, false, false, false, false};              //Struct for logic with buttons. The order is hold, bet, hit, gameContinue and gameEnd
    buttonBoxes gameBoxes = {                                               //Struct for logic with buttons
        //      x,                       y,                 wid,         height
        {buttonXPosition      , buttonYPosition      , BUTTON_WIDTH    , BUTTON_HEIGHT},           //Hold box
        {buttonXPosition + 200, buttonYPosition + 40 , BUTTON_WIDTH    , BUTTON_HEIGHT},           //Bet box
        {buttonXPosition      , buttonYPosition + 60 , BUTTON_WIDTH    , BUTTON_HEIGHT},           //Hit box
        {buttonXPosition + 250, buttonYPosition + 110, BUTTON_WIDTH    , BUTTON_HEIGHT},           //gameContinue box
        {buttonXPosition + 400, buttonYPosition + 110, BUTTON_WIDTH    , BUTTON_HEIGHT},           //gameEnd box
        {SCREEN_WIDTH/3  - 110, SCREEN_HEIGHT /3+ 125, BUTTON_WIDTH+40 , BUTTON_HEIGHT+10},        //menuPlay box
        {SCREEN_WIDTH/3  - 110, SCREEN_HEIGHT /3+ 200, BUTTON_WIDTH+235, BUTTON_HEIGHT+10},        //menuScoreboard box
        {SCREEN_WIDTH/3  - 110, SCREEN_HEIGHT /3+ 275, BUTTON_WIDTH+15 , BUTTON_HEIGHT+10}         //menuQuit box
    };
    Vector2 mousePosition = { 0.0f, 0.0f };                                  //Declares and initializes variable that tracks mouse position.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blackjack");                    //Initializes Window parameters.
    Texture2D texture_table = LoadTexture("Blackjack cards/Table blank.png");//Loads table's image into a variable
    SetTargetFPS(60);   //Makes the game run at 60 frames per second because we clearly need those 60 FPS for a card game
    loadCardTextures(); //Loads all the cards so they can be drawn later
    
    while (!WindowShouldClose())                                //Loop to maintain window working
    {
        mousePosition = GetMousePosition();                             //Updates mouse's position

         if (texture_table.id == 0 && !tableUnloaded) {                 //Checks if the table's image needs to be loaded
            texture_table = LoadTexture("Blackjack cards/Table blank.png");
        } 
        DrawTexture(texture_table, 0, 0, WHITE);        //Shows the table's image 
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
                //Button that lets you play the game
                DrawRectangle(gameBoxes.menuScoreboard.x, gameBoxes.menuScoreboard.y, gameBoxes.menuScoreboard.width, gameBoxes.menuScoreboard.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuScoreboard) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 3;
                }
                DrawText("Scoreboard", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+200, 60, BLACK);
                //Button that takes you to scoreboard screen
                DrawRectangle(gameBoxes.menuQuit.x, gameBoxes.menuQuit.y, gameBoxes.menuQuit.width, gameBoxes.menuQuit.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuQuit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 4;
                }
                DrawText("Salir", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+275, 60, BLACK);
                //Button to quit game instead of clicking the 'x' or pressing ESC
                EndDrawing();
                break;
            case 1:                         //Play
                BeginDrawing();
                const char *moneyPrint = TextFormat("Dinero: %d", playerMoney);     
                const char *playerPointPrint = TextFormat("Puntos: %d", playerPoints);
                const char *dealerPointPrint = TextFormat("Puntos: %d", dealerPoints);
                const char *betPrint = TextFormat("Apuesta: %d", bet);
                //Transforms variables in order to be shown on screen
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
                //Checks the amount of cards the dealer/player has so the variables from earlier can move with the cards

                DrawText(moneyPrint, x_playerPosition, y_position, 40, BLACK);                      //Relative coordinates of total money coordinates
                DrawText(betPrint, x_playerPosition, y_position+60, 40, BLACK);                     //Relative coordinates of bet coordinates
                DrawText(playerPointPrint, x_playerPosition, y_position+120, 40, BLACK);            //Relative coordinates of points coordinates
                DrawText(dealerPointPrint, x_dealerPosition, y_position-400, 40, BLACK);
                //Draws the variables from before into the screen

                DrawRectangle(gameBoxes.betBox.x , gameBoxes.betBox.y, gameBoxes.betBox.width, gameBoxes.betBox.height, WHITE);
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
                //Button to let the player bet between 100, 200 and 300. If the player hasn't made a bet or their amount of cards is 2, they can bet

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
                //Button to let the player get another card, calculates points right after the card

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
                //Button to let the player end their turn

                if (playerPoints > 21) {
                    currentGame.roundEnd = true;        
                    currentGame.playerWin = false;
                }   else if (playerPoints == 21) {
                    currentGame.roundEnd = true;        
                    currentGame.playerWin = false;
                }
                //Condition that constantly checks if the player went above 21

                printCard(&amountCardsPlayer, playerDeck, PLAYER);
                printCard(&amountCardsDealer, dealerDeck, DEALER);
                //Both of this functions show the current cards of both parties
                

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
                    //Button to let the player continue playing after the round ended

                    DrawRectangle(gameBoxes.gameEndBox.x, gameBoxes.gameEndBox.y, gameBoxes.gameEndBox.width, gameBoxes.gameEndBox.height, WHITE);
                    DrawText("Salir", gameBoxes.gameEndBox.x + 15, gameBoxes.gameEndBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameEndBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameEndButton = true;

                    }
                    if (gameButtons.gameEndButton) {   
                        screenState = 2;                        //Switches to name input after game ends
                        gameButtons.gameEndButton = false;
                        break;
                    }
                    //Button to let the player end the game
                    currentGame.playerWin = compareScores(playerPoints, dealerPoints);  //Compare function goes here
                    if (currentGame.playerWin) {
                        DrawText("Usted gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    }   else if (!currentGame.playerWin && playerPoints > 21) {
                        DrawText("Se paso de 21 puntos\nLa casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    } else if (currentGame.playerWin && dealerPoints > 21){
                        DrawText("Dealer se pasa de 21 puntos\nLa casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    } else {
                        DrawText("La casa gana!", SCREEN_HEIGHT/2, buttonYPosition, 35, BLACK);
                    }
                    //If compareScores returns boolean, I could use a switch instead
                    //Maybe disable first if condition in order to explain the reason for a win/loss?

                }
                EndDrawing();
                break;
            case 2:                         //Finish game
            UnloadTexture(texture_table);
            texture_table.id = 0;
            tableUnloaded = true;

            rankingImport(scoreList, scoreFileName);    //Loads current scoreboard
            getUserName(playerName, &charCount); 
            //Asks the player for their name with a maximum of 3 letters because it is clearly fitting for a good old fashioned scoreboard
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Escriba su nombre, maximo 3 letras", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3, 40, BLUE);
            if (charCount == 0) {
                DrawText("...", SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 40, BLUE);
            }   else {
                DrawText(TextFormat("%s", playerName), SCREEN_WIDTH/3, SCREEN_HEIGHT/2, 40, BLUE);
            }
            DrawText(TextFormat("%d/3", charCount), SCREEN_WIDTH/3, SCREEN_HEIGHT/2+50, 40, BLUE);
            //This is to show the player's name as they are writing it and the amount of letters they're using
            DrawText("Presione enter para continuar.", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/2+200, 40, BLUE);
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER)){
                    Score newPlayer;
                if (playerName[0] == '\0') {
                    newPlayer = crearScore("UNI", playerMoney); // Player too shy to input their name will be called UNI instead (User Not Inserted)
                }   else {
                    newPlayer = crearScore(playerName, playerMoney); // Converts player's name and their money into newPlayer struct
                }

                checkScore(scoreList, newPlayer, scoreFileName); // Checks scoreboard and decides if player is able to get into the list
                rankingSave(scoreList, scoreFileName);           //Saves the scoreboard
                charCount = 0;
                screenState = 3;                                //Switches to scoreboard screen
            }
            break;
            case 3:                         //  Check scoreboard
                if (texture_table.id != 0 && !tableUnloaded) {    //Checks if the player has been through the name asking screen, to see if it needs to unload the table
                    UnloadTexture(texture_table);
                    texture_table.id = 0;
                    tableUnloaded = true;
                }
                const char *playerRankings = '\0';
                const char *playerNames = '\0';
                const char *playerScores = '\0';
                //Declares three variables that will be used to show the scoreboard. They are initialized to \0 to avoid problems if the player decides to check more than once
                loadRankingVariables(&playerRankings, &playerNames, &playerScores);
                if (!showGraphicRanking(playerRankings, playerNames, playerScores)) { 
                     //If the player presses ENTER they will be taken into the main menu once again
                    playerName[0] = '\0';
                    //Deletes whatever the player wrote in their name to make sure it doesn't appear the next time someone goes to the name asking screen
                    tableUnloaded = false;
                    screenState = 0;            //Player forcibly gets moved to the main menu
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