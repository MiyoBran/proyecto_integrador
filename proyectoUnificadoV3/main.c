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
#include "record.h"
#include "jugador.h"

////////////////////////////////////////////////////////////////

int main() {
    srand(time(NULL));
    initializeGraphicsConfig();                                             //Searches for configuration values
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blackjack");                    //Initializes Window parameters.

//////////Variables related to user//////////
    char *playerName = malloc(4*sizeof(char));
    Jugador mainCharacter = {0};
    int charCount = 0;
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score));
    char *scoreFileName = getconfig("archivo_ranking");
    Jugador *allGamesPlayed = NULL;
    char *recordFileName = getconfig("archivo_historial");
    int amountRegisters = recordSize(recordFileName); //Verifies how many games were played before
////////////////////////////////////////////

/////Measures to stop program if variables fail/////
    if (scoreList == NULL) {
        printf("Error al asignar memoria para lista de puntaje\n");
        free(scoreList);
        return 1;
    }
    if (playerName == NULL) {
        printf("Error al asignar memoria para nombre de usuario\n");
        free(playerName);
        return 1;
    }   else {
        playerName[0] = '\0';
    }
    if (scoreFileName == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreFileName);
        return 1;
    }
    if (recordFileName == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(allGamesPlayed);
        return 1;
    }
/////////////////////////////////////////////////



///////Variables related to game logic///////
    myCard playerDeck[MAX_CARDS_DISPLAYED];
    myCard dealerDeck[MAX_CARDS_DISPLAYED];
/////////////////////////////////THE WAY THE DECKS ARE INITIALIZED NEEDS TO BE CHANGED😀😀😀😀😀😀😀
    int amountCardsPlayer = 0;
    int amountCardsDealer = 0;
/////////////////////////////////THESE VARIABLES ARE TO TRACK AMOUNT OF CARDS TO PRINT THEM, YOU COULD USE THEM IN LOGIC AS WELL😀😀😀😀😀😀😀

    gameState currentGame = {false, false, false, false};             //Makes struct that tracks if the player won or if the round ended
    int playerPoints = 0;
    int dealerPoints = 0;
    int playerBet = 0;
////////////////////////////////////////////

////////Variables related to graphics////////
    int indexUpsideCards;
    bool tableUnloaded = false;                                       //This variable prevents the compiler to keep unloading the table image during
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
        {SCREEN_WIDTH/3  - 110, SCREEN_HEIGHT /3+ 275, BUTTON_WIDTH+15 , BUTTON_HEIGHT+10},         //menuQuit box
        {SCREEN_WIDTH/3  + 110, SCREEN_HEIGHT /3+ 275, BUTTON_WIDTH+300 , BUTTON_HEIGHT+10}        //menuRecord box

    };
    Vector2 mousePosition = { 0.0f, 0.0f };                                  //Declares and initializes variable that tracks mouse position.
    Texture2D upsideDownCard = LoadTexture("Blackjack cards/Upside down card.png");
    Texture2D texture_table  = LoadTexture("Blackjack cards/Table blank.png");//Loads table's image into a variable

/////////////////////////////////////////////


    recordImport(&allGamesPlayed, recordFileName);    //Imports the record of games played into allGamesPlayed
    SetTargetFPS(60);   //Makes the game run at 60 frames per second because we clearly need those 60 FPS for a card game
    loadCardTextures(); //Loads all the cards so they can be drawn later
    
    while (!WindowShouldClose())                                //Loop to maintain window working
    {
        mousePosition = GetMousePosition();                             //Updates mouse's position

         if (texture_table.id == 0 && !tableUnloaded) {                 //Checks if the table's image needs to be loaded
            texture_table = LoadTexture("Blackjack cards/Table blank.png");
            indexUpsideCards = chooseRandomUpsideCard();
   //         upsideDownCard = LoadTexture("Blackjack cards/Upside down card.png");
        } 
        DrawTexture(texture_table, 0, 0, WHITE);        //Shows the table's image 
        switch (screenState) {
///////////////////////////////////////////////////////////////////////// CASE 1: MAIN MENU /////////////////////////////////////////////////////////////////////////
            case 0:                         //Main menu
                BeginDrawing();
                DrawText("BLACKJACK", SCREEN_WIDTH/3-125, 100, 125, GOLD);
                DrawText("BLACKJACK", SCREEN_WIDTH/3-125, 100, 125, GOLD);
                DrawText("Menu principal:", SCREEN_WIDTH/3-100, SCREEN_HEIGHT/3+50, 60, BLACK);
                DrawRectangle(gameBoxes.menuPlay.x, gameBoxes.menuPlay.y, gameBoxes.menuPlay.width, gameBoxes.menuPlay.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuPlay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 1;
                    mainCharacter.saldo = 10000;
    
    /////////////////////////////😀😀😀😀😀😀😀
                    startRound(&amountCardsPlayer, &amountCardsDealer, &playerPoints, &dealerPoints, &playerBet, playerDeck, dealerDeck, &currentGame);
                    allowBlackjackWin(playerPoints, amountCardsPlayer, &currentGame);
                    if (playerAbove21(playerPoints)) {
                        currentGame.roundEnd = true;
                        currentGame.allowMoneyUpdate = true;
                    }
    //////////////HERE GO FUNCTIONS TO START ROUND, ALLOW BLACKJACK WIN AND CHECKS IF PLAYER WENT ABOVE 21 WITH THEIR FIRST TWO CARDS😀😀😀😀😀😀😀
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

                DrawRectangle(gameBoxes.menuRecord.x, gameBoxes.menuRecord.y, gameBoxes.menuRecord.width, gameBoxes.menuRecord.height, WHITE);
                if (CheckCollisionPointRec(mousePosition, gameBoxes.menuRecord) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    screenState = 5;
                }
                DrawText("Instrucciones", SCREEN_WIDTH/3+115, SCREEN_HEIGHT/3+275, 60, BLACK);
                //Button that takes you to record screen

                EndDrawing();
                break;
///////////////////////////////////////////////////////////////////////// CASE 1: GAME STARTS /////////////////////////////////////////////////////////////////////////
            case 1:
                BeginDrawing();
                const char *moneyPrint = TextFormat("Dinero: %d", mainCharacter.saldo);     
                const char *playerPointPrint = TextFormat("Puntos: %d", playerPoints);
                const char *dealerPointPrint = TextFormat("Puntos: %d", dealerPoints);
                const char *betPrint = TextFormat("Apuesta: %d", playerBet);
                //Transforms variables in order to be shown on screen
                if (amountCardsPlayer <= 2) {
                    x_playerPosition = (CARD_WIDTH*3)+50;
                }   else {
                    x_playerPosition = (CARD_WIDTH + CARD_DISTANCE)*(amountCardsPlayer+1);
                }

                if (amountCardsDealer <= 2) {
                    x_dealerPosition = (CARD_WIDTH*3)+50;
                    DrawTexture(upsideCards[indexUpsideCards], CARD_WIDTH*(amountCardsDealer+1)+(CARD_DISTANCE*amountCardsDealer), VERTICAL_MARGIN*2, WHITE);
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
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.betBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !currentGame.roundEnd && mainCharacter.saldo >= 100) {
                        gameButtons.betButton = true;
                    }
                    if (gameButtons.betButton) {
                        DrawText("Cuanto quiere apostar?", gameBoxes.betBox.x+280, gameBoxes.betBox.y, 30, BLACK);
                        getBet(&playerBet, gameBoxes.betBox, &gameButtons.betButton, &alreadyBet);
                    }
                }
                //Button to let the player bet between 100, 200 and 300. If the player hasn't made a bet or their amount of cards is 2, they can bet

                DrawRectangle(gameBoxes.hitBox.x, gameBoxes.hitBox.y, gameBoxes.hitBox.width, gameBoxes.hitBox.height, WHITE);              //Everything about hit functions
                DrawText("Hit", gameBoxes.hitBox.x+10, gameBoxes.hitBox.y, 35, BLACK);
                if((CheckCollisionPointRec(mousePosition, gameBoxes.hitBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !currentGame.roundEnd && mainCharacter.saldo >= 100) {
                    gameButtons.hitButton = true;
                }
                if (gameButtons.hitButton) {   
                    /////////////////////////////////////////////😀😀😀😀😀😀😀
                    getCard(playerDeck, &amountCardsPlayer);
                    playerPoints = calculatePoints(playerDeck, &amountCardsPlayer);
                    if(playerAbove21(playerPoints)) {
                        currentGame.roundEnd = true;
                        currentGame.playerWin = false;
                        currentGame.allowMoneyUpdate = true;
                    }
                    /////////////////////////////////////////// FUNCTION TO GET CARDS, CALCULATE POINTS AND CHECK IF PLAYER WENT ABOVE 21 GO HERE😀😀😀😀😀😀😀
                    gameButtons.hitButton = false;
                }
                //Button to let the player get another card, calculates points right after the card


                DrawRectangle(gameBoxes.holdBox.x, gameBoxes.holdBox.y, gameBoxes.holdBox.width, gameBoxes.holdBox.height, WHITE);          //Everything about hold functions
                DrawText("Hold", gameBoxes.holdBox.x+10, gameBoxes.holdBox.y, 35, BLACK);
                if((CheckCollisionPointRec(mousePosition, gameBoxes.holdBox )) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !currentGame.roundEnd && mainCharacter.saldo >= 100) {
                    gameButtons.holdButton = true;
                }
                if (gameButtons.holdButton) {
////////////////////////////////////////////////////////😀😀😀😀😀😀😀
                    for (int i = 0; i < 2; i++) {
                        getCard(dealerDeck, &amountCardsDealer);
                    }

                    dealerPoints = calculatePoints(dealerDeck, &amountCardsDealer);

                    if(playerAbove21(dealerPoints)) {
////////////////////////////////////////////////////////HERE GO FUNCTIONS FOR DEALER TURN, CALCULATE POINTS AND STUFF😀😀😀😀😀😀😀
                        currentGame.playerWin = true;
                    }   else {
                        currentGame.playerWin = compareScores(playerPoints, dealerPoints);  //Compare function goes here
                    }
////////////////////////////////////////////////FUNCTION TO COMPARE SCORES GOES HERE😀😀😀😀😀😀😀
                        currentGame.allowMoneyUpdate = true;
                        currentGame.roundEnd = true;
                    gameButtons.holdButton = false;
                }
                //Button to let the player end their turn

                printCard(&amountCardsPlayer, playerDeck, PLAYER);
                printCard(&amountCardsDealer, dealerDeck, DEALER);
                //Both of this functions show the current cards of both parties

                if (mainCharacter.saldo < 100) {    //If the player can't make the minimal bet, they will be booted to the scoreboard
                    mainCharacter.saldo = 0;
                    DrawRectangle(0, buttonYPosition, SCREEN_WIDTH, 200, RED); 
                    DrawText("Se ha quedado sin dinero!\n Usted pierde", SCREEN_HEIGHT/2, buttonYPosition+40, 35, BLACK);
                    DrawRectangle(gameBoxes.gameEndBox.x, gameBoxes.gameEndBox.y, gameBoxes.gameEndBox.width, gameBoxes.gameEndBox.height, WHITE);
                    DrawText("Salir", gameBoxes.gameEndBox.x + 15, gameBoxes.gameEndBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameEndBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameEndButton = true;

                    }
                    if (gameButtons.gameEndButton) {   
                        screenState = 3;
                        gameButtons.gameEndButton = false;
                        break;
                    }
                }
                                    ///////////////////// Round End /////////////////////
                if (currentGame.roundEnd && mainCharacter.saldo >= 100) {
                    DrawRectangle(0, buttonYPosition, SCREEN_WIDTH, 200, RED);

                    if (playerPoints > 21) {
                        DrawText("Se paso de 21 puntos", SCREEN_HEIGHT/2-20, buttonYPosition, 35, BLACK);
                    }   else if (dealerPoints > 21) {
                        DrawText("Dealer se pasa de 21 puntos", SCREEN_HEIGHT/2-20, buttonYPosition, 35, BLACK);
                    }

                    if (currentGame.playerBlackjack) {
                        DrawText("Obtuvo un blackjack! Apuesta x2", SCREEN_HEIGHT/2, buttonYPosition+40, 35, BLACK);
                    }   else if (currentGame.playerWin) {
                        DrawText("Usted gana!", SCREEN_HEIGHT/2, buttonYPosition+40, 35, BLACK);
                    }   else {
                        DrawText("La casa gana!", SCREEN_HEIGHT/2, buttonYPosition+40, 35, BLACK);
                    }
//////////////////////////////////////////////////////HERE GOES FUNCTIONS TO UPDATE PLAYER MONEY😀😀😀😀😀😀😀
                    if (currentGame.allowMoneyUpdate && currentGame.playerBlackjack) {
                        mainCharacter.saldo = getPlayerMoney(mainCharacter.saldo, (playerBet*3), currentGame.playerBlackjack);
                        mainCharacter.blackjack++;
                    } else if (currentGame.allowMoneyUpdate && currentGame.playerWin) {
                        mainCharacter.saldo = getPlayerMoney(mainCharacter.saldo, playerBet, currentGame.playerWin);
                        mainCharacter.victorias++;
                    }  else if (currentGame.allowMoneyUpdate && !currentGame.playerWin) {
                        mainCharacter.saldo = getPlayerMoney(mainCharacter.saldo, playerBet, currentGame.playerWin);
                        mainCharacter.derrotas++;
                    }
                    currentGame.allowMoneyUpdate = false;
//////////////////////////////////////////////////////😀😀😀😀😀😀😀
                    DrawText("Quiere continuar el juego?", SCREEN_HEIGHT/2, buttonYPosition+75, 35, BLACK);
                    DrawRectangle(gameBoxes.gameContinueBox.x, gameBoxes.gameContinueBox.y, gameBoxes.gameContinueBox.width, gameBoxes.gameContinueBox.height, WHITE);
                    DrawText("Seguir", gameBoxes.gameContinueBox.x + 10, gameBoxes.gameContinueBox.y, 35, BLACK);
                    if((CheckCollisionPointRec(mousePosition, gameBoxes.gameContinueBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                        gameButtons.gameContinueButton = true;
                    }
                    if (gameButtons.gameContinueButton) {                               //If player continues playing, the variables are set back to their inital value
////////////////////////////////////////////////////HERE GO FUNCTION TO START ROUND, TO CHECK IF BLACKJACK AND WHETHER PLAYER IS ABOVE 21 POINTS 😀😀😀😀😀😀😀
                        startRound(&amountCardsPlayer, &amountCardsDealer, &playerPoints, &dealerPoints, &playerBet, playerDeck, dealerDeck, &currentGame);
                        allowBlackjackWin(playerPoints, amountCardsPlayer, &currentGame);
                        if (playerAbove21(playerPoints)) {
                            currentGame.roundEnd = true;
                            currentGame.allowMoneyUpdate = true;
                        }
////////////////////////////////////////////////////😀😀😀😀😀😀😀
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
                }
                EndDrawing();
                break;
///////////////////////////////////////////////////////////////////////// CASE 2: AFTER GAME ENDS /////////////////////////////////////////////////////////////////////////
            case 2:
            UnloadTexture(texture_table);
            texture_table.id = 0;
            tableUnloaded = true;

            rankingImport(scoreList, scoreFileName);    //Loads current scoreboard
            getUserName(playerName, &charCount); 
            strcpy(mainCharacter.nombre, playerName);
////////////////Put jugador struct in here to change player name
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
                    Jugador newGame;
                if (playerName[0] == '\0') {
                    newPlayer = crearScore("UNI", mainCharacter.saldo); // Player too shy to input their name will be called UNI instead (User Not Inserted)
                    newGame = crearHistorial("UNI", mainCharacter.saldo, mainCharacter.victorias, mainCharacter.derrotas, mainCharacter.blackjack);
                }   else {
                    newPlayer = crearScore(mainCharacter.nombre, mainCharacter.saldo); // Converts player's name and their money into newPlayer struct
                    newGame = crearHistorial(mainCharacter.nombre, mainCharacter.saldo, mainCharacter.victorias, mainCharacter.derrotas, mainCharacter.blackjack);
                    // Converts player's name and their money into newPlayer struct
                }

                checkScore(scoreList, newPlayer, scoreFileName); // Checks scoreboard and decides if player is able to get into the list
                rankingSave(scoreList, scoreFileName);           //Saves the scoreboard
                insertRecordEOF(&allGamesPlayed, newGame, amountRegisters);
                amountRegisters++;  // Increments the amount of games played
                recordSave(allGamesPlayed, recordFileName, amountRegisters);
                charCount = 0;
                screenState = 3;                                //Switches to scoreboard screen
            }
            break;

///////////////////////////////////////////////////////////////////////// CASE 3: SCOREBOARD /////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////// CASE 4: EXIT GAME //////////////////////////////////////////////////////////////////////////
            case 4:                         //Exit
                    unloadCardTextures();
                    CloseWindow();
                break;
///////////////////////////////////////////////////////////////////////// CASE 5: INSTRUCTIONS SCREEN /////////////////////////////////////////////////////////////////////////
            case 5:
                if (!showGameInstructions(texture_table)) { 
                    screenState = 0;            //Player forcibly gets moved to the main menu
                }
                break;
        }
    }

    ///////This is for testing purposes
    printf("\n\nB%d   D%d   V%d\n\n", mainCharacter.blackjack, mainCharacter.derrotas, mainCharacter.victorias);
    showRanking(scoreList, scoreFileName);
    showRecord(allGamesPlayed, amountRegisters);
    printf("\n\n%d\n\n", screenState);
    ///////This is for testing purposes


    // Frees dynamic memory if it needs to
    if (scoreList != NULL) free(scoreList);
    if (playerName != NULL) free(playerName);
    if (allGamesPlayed != NULL) free(allGamesPlayed);
    if (scoreFileName != NULL) free(scoreFileName);

    
    return 0;
}

/*
            const char *text = TextFormat("%d", plata);     // Function to write variables on screen

*/