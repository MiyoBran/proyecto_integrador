#ifndef SCOREBOARDV3_H
#define SCOREBOARDV3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_REGISTROS 10 //Tamaño del arreglo en ScoreboardV1 y tamaño Maximo del ScoreboardV2


typedef struct {
    int ranking;
    char name[50];
    float money;
} Score;

// Para obtener el arreglo o guardarlo si se hizo un cambio
void fileImport(Score **scoreList, const char *nombreArchivo);
void fileSave(Score *scoreList, const char *nombreArchivo);

// Funcion para imprimir el ranking
void showRanking(Score *scoreList,const char *nombreArchivo);
void sortRanking(Score *scoreList);


// Verifica y agrega un jugador, actualiza si es necesario
void checkScore(Score **scoreList, Score nuevoJugador, const char *nombreArchivo);
void insertPlayer(Score **scoreList, Score nuevoJugador);
void updateRanking(Score **scoreList, const char *nombreArchivo);




// Funciones de utilidades para tests y manejo de estructuras
char *generarNombreAleatorio();
Score crearScore(const char *nombre, float dinero);

#endif// SCOREBOARDV3_H
