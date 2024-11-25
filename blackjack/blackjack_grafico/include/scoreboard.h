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

//Abre archivo con arreglos tipo Score y actualiza el array
void rankingImport(Score *scoreList, const char *nombreArchivo);

//Guarda archivo con un arreglo tipo Score
void rankingSave(Score *scoreList, const char *nombreArchivo);

// Función para imprimir como tabla el ranking
void showRanking(Score *scoreList,const char *nombreArchivo);

// Función para ordenar la lista de jugadores en función del dinero (descendente) - Bubble Sort porque son pocos
void sortRanking(Score *scoreList);

// Agregar un jugador al ranking si hay lugar vacio o si es mayor al ultimo
void checkScore(Score *scoreList, Score nuevoJugador,const char *nombreArchivo);

// Función para insertar al jugador en el ultimo lugar
void insertPlayer(Score *scoreList, Score nuevoJugador);

// Función para actualizar los rankings
void updateRanking(Score *scoreList,const char *nombreArchivo);

// Funcion de Prueba / Tests
char *generarNombreAleatorio();

// Funcion para convertir datos de la en arreglo tipo Score
Score crearScore(const char *nombre, float dinero);

#endif// SCOREBOARD_H
