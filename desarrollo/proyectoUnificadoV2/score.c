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


int main(void) {
    ///////////************////////////// Bloques importantes en main para funcionamiento de los scoreboard

    srand(time(NULL)); // Inicializar la semilla aleatoria
    
    // Asigna memoria dinámica para el arreglo de jugadores
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }
    ////++++++ TIENE QUE ESTAR EN EL MAIN, nombrearchivo es un parametro que todos usan
    //// importante Obtener aca el valor del archivo de datos???? , sino cambio las funciones
    char *nombreArchivo = getconfig("archivo_datos");
    if (nombreArchivo == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }
    ///////////************//////////////

    initializeGraphicsConfig();                                             //Busca los valores de configuracion

    fileImport(scoreList, nombreArchivo);
    char allRankings[100] = "";
    char allNames[300] = "";
    char allScores[300] = "";

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
    const char *playerRankings = TextFormat("%s", allRankings);  
    const char *playerNames = TextFormat("%s", allNames);  
    const char *playerScores = TextFormat("%s", allScores);  
 
    showRanking(scoreList, nombreArchivo);

    char *userName;
    int playerMoney = 5000;
    Vector2 mousePosition = { 0.0f, 0.0f };                             //Initialize variable that tracks mouse position.



    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blackjack");               //Initialize Window parameters.
    SetTargetFPS(60); 

    while (!WindowShouldClose())                                //Loop to maintain window working
    {

        mousePosition = GetMousePosition();                             //Update mouse position
        BeginDrawing();
            ClearBackground(BLACK);  

            DrawText("HIGHSCORE", SCREEN_WIDTH/2-150, 100, 40, RED);                      //Relative coordinates of total money coordinates
            DrawText(playerRankings, 430, 200, 40, BLUE);
            DrawText(playerNames, 500, 200, 40, DARKBLUE);
            DrawText(playerScores, 600, 200, 40, BLUE);

        EndDrawing();
        
    }
    

    CloseWindow();

    //userName = askUserName(userName);                                     //Function that asks user to input their name after game ends
    // Scoreboard functions go here?
    
    free(nombreArchivo);
    free(userName);
    return 0;
}


/*
            DrawText(" 1\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n10", 430, 200, 40, BLUE);
            DrawText("DAR\nBLU\nRED\nYAY\nGRY\nPOO\nZK1\nLIN\nMIK\nDRE", 500, 200, 40, DARKBLUE);
            DrawText("\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n\t\t5000\n", 600, 200, 40, BLUE);
*/