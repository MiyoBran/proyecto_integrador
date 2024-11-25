#include "graphics_storage.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "files2.h"
#include "gamelogic.h"



int main(void) {
    extern myDeck playerDeck[MAX_CARDS_DISPLAYED];
    extern myDeck dealerDeck[MAX_CARDS_DISPLAYED];                                               //Search for myDeck variable for the player and croupier deck
    int playerPoints = 0;
    int dealerPoints = 0;

    char *userName;
    int buttonXPosition = 100;                                              //Difference between window wall and buttons
    int buttonYPosition = 290;                                              //Difference between window roof and buttons
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
    int amountCardsPlayer = 0;                                                //This variable is important. Logic part shouldn't need it, just keep it here.
    int amountCardsDealer = 1;

    bool endRound = false;
    bool gameEnd = false;
    bool alreadyBet = false;                                            //Variable that checks if user has set a bet
    int userPoints = 0;                                                //This variable is for the amount of point the player has
    int bet = 0;                                                        //This variable is for the amount the player wants to bet, has to go in struct
    int playerMoney = getPlayerMoney();


    //All of the variables above should go at the start of main function. 
    //Everything below here has to go inside case 1

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blackjack");               //Initialize Window parameters.
    SetTargetFPS(60); 
    loadCardTextures();
    Texture2D texture_table = LoadTexture("Blackjack cards/Table blank.png");

    while (!WindowShouldClose() && !gameEnd)                                //Loop to maintain window working
    {

        mousePosition = GetMousePosition();                             //Update mouse position
        BeginDrawing();
            DrawTexture(texture_table, 0, 0, WHITE);                    //Loads table texture into the screen

            
            const char *moneyPrint = TextFormat("Dinero: %d", playerMoney);     
            const char *playerPointPrint = TextFormat("Puntos: %d", playerPoints);
            const char *dealerPointPrint = TextFormat("Puntos: %d", dealerPoints);
            const char *betPrint = TextFormat("Apuesta: %d", bet);

            int x_position = 0;
            int y_position = 520;
            if (amountCardsPlayer <= 2) {
                x_position = (CARD_WIDTH*3)+50;
            }   else {
                x_position = (CARD_WIDTH + CARD_DISTANCE)*(amountCardsPlayer+1);
            }

            DrawText(moneyPrint, x_position, y_position, 40, BLACK);                      //Relative coordinates of total money coordinates
            DrawText(betPrint, x_position, y_position+60, 40, BLACK);                     //Relative coordinates of bet coordinates
            DrawText(playerPointPrint, x_position, y_position+120, 40, BLACK);                 //Relative coordinates of points coordinates
            DrawText(dealerPointPrint, x_position, y_position-400, 40, BLACK);


            DrawRectangle(gameBoxes.betBox.x , gameBoxes.betBox.y, gameBoxes.betBox.width, gameBoxes.betBox.height, WHITE);             //Everything about bet functions
            DrawText ("Apostar", gameBoxes.betBox.x+5, gameBoxes.betBox.y, 35, BLACK);
            if (!alreadyBet || amountCardsPlayer == 2) {
                if((CheckCollisionPointRec(mousePosition, gameBoxes.betBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
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
                if((CheckCollisionPointRec(mousePosition, gameBoxes.hitBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    gameButtons.hitButton = true;
                    amountCardsPlayer++;
                    if (amountCardsPlayer > MAX_CARDS_DISPLAYED) {
                        amountCardsPlayer = MAX_CARDS_DISPLAYED;
                    }
                }
                if (gameButtons.hitButton) {   
                    playerPoints = playerHit(&amountCardsPlayer);
                                                    //Function related to draw card go here.
                    gameButtons.hitButton = false;
                }

                printCard(&amountCardsPlayer, playerDeck, PLAYER);                       //This prints the cards that correspond to the user, variable to decide


                DrawRectangle(gameBoxes.holdBox.x, gameBoxes.holdBox.y, gameBoxes.holdBox.width, gameBoxes.holdBox.height, WHITE);          //Everything about hold functions
                DrawText("Hold", gameBoxes.holdBox.x+10, gameBoxes.holdBox.y, 35, BLACK);
                if((CheckCollisionPointRec(mousePosition, gameBoxes.holdBox )) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    gameButtons.holdButton = true;
                }
                if (gameButtons.holdButton) {
                    endRound = true;

                    amountCardsDealer = dealerCards();
                    //int dealerPoint = dealerPoints();   //To change name */
                                                        //Functions related to logic with croupier go here. Only works after user clicked on hold
                    gameButtons.holdButton = false;
/*                      if (gameWinner()) {
                        print("you win");
                    }   else {
                        printf("you lose");
                    }  */
                }
                if (playerPoints > 21) {                            //PLAYER LOSES
                                                                    //HAVE TO PRINT PLAYER LOSES                      
                    endRound = true;
                }
                printCard(&amountCardsDealer, dealerDeck, CROUPIER);                     //This prints the cards that correspond to the dealer, variable to decide.
                
            }
            
            if (endRound) {                                               //End Round is a variable that I'm still thinking about, will probably need to wait for logical part
/*                 if (winCondition) {
                    Imprimir que el usuario gano;
                }   else {
                    Imprimir que el usuario perdio;
                } */
                playerMoney = getPlayerMoney();
                DrawRectangle(0, buttonYPosition, SCREEN_WIDTH, 200, RED);
                DrawText("Quiere continuar el juego?", SCREEN_HEIGHT/2, buttonYPosition+50, 35, BLACK);
                DrawRectangle(gameBoxes.gameContinueBox.x, gameBoxes.gameContinueBox.y, gameBoxes.gameContinueBox.width, gameBoxes.gameContinueBox.height, WHITE);
                DrawText("Seguir", gameBoxes.gameContinueBox.x + 10, gameBoxes.gameContinueBox.y, 35, BLACK);
                if((CheckCollisionPointRec(mousePosition, gameBoxes.gameContinueBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    gameButtons.gameContinueButton = true;
                }
                if (gameButtons.gameContinueButton) {   
                    amountCardsPlayer = 2;
                    amountCardsDealer = 1;
                    bet = 100;
                    //LLAMAR FUNCION PARA MAZOS NUEVO
                    //LLAMAR FUNCION PARA PUNTAJE EN BASE A MAZOS NUEVOS
                    endRound = false;
                    gameButtons.gameContinueButton = false;
                }

                DrawRectangle(gameBoxes.gameEndBox.x, gameBoxes.gameEndBox.y, gameBoxes.gameEndBox.width, gameBoxes.gameEndBox.height, WHITE);
                DrawText("Salir", gameBoxes.gameEndBox.x + 15, gameBoxes.gameEndBox.y, 35, BLACK);
                if((CheckCollisionPointRec(mousePosition, gameBoxes.gameEndBox)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    gameButtons.gameEndButton = true;
                    gameEnd = true;
                }
                if (gameButtons.gameEndButton) {   
                    gameButtons.gameEndButton = false;
                }

            }

        EndDrawing();
    }
    




    unloadCardTextures();
    UnloadTexture(texture_table);
    CloseWindow();

    //userName = askUserName(userName);                                     //Function that asks user to input their name after game ends
    // Scoreboard functions go here?
    
    
    //
    printf("\nBets: ");
    printf("%d ", bet);
    printf("\n%s\n", userName);
    printf("\n%d\n", amountCardsPlayer);
    //All of this printf functions are to test, can be deleted later

    
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