#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_REGISTROS 10


typedef struct {
    int ranking;
    char name[50];
    float money;
} Score;

// Para obtener el arreglo o guardarlo si se hizo un cambio
void fileImport(Score *scoreList, const char *nombreArchivo);
void fileSave(Score *scoreList, const char *nombreArchivo);

// Funcion para imprimir el ranking
void showRanking(Score *scoreList,const char *nombreArchivo);
void sortRanking(Score *scoreList);


void checkScore(Score *scoreList, Score nuevoJugador,const char *nombreArchivo);
// Para el agregar jugador "desarmado"
void insertPlayer(Score *scoreList, Score nuevoJugador);
void updateRanking(Score *scoreList,const char *nombreArchivo);

// Para manejo de strucs correctas y test
char *generarNombreAleatorio();
Score crearScore(const char *nombre, float dinero);

#endif// SCOREBOARD_H
