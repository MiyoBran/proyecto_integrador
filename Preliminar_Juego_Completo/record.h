#ifndef RECORD_H
#define RECORD_h
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> // Para calloc y realloc

////////////////////////Funciones propias////////////////////////

#include "config.h"     // donde esta la funcion para buscar configuracion en .env
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego
#include "jugador.h"    // donde estan declaradas las funciones del JUGADOR durante la SESION
#include "scoreboard.h" // donde estan declaradas las estructuras y funciones para persistencia ranking

/////////////////////////////////////////////////////////////////////////////////////


//--> Declaracion de funciones PROTOTIPO -> Usando Realloc
//Lee el historial de jugadores desde un archivo binario y lo guarda en memoria dinámica.
void recordImport(Jugador **historial, const char *nombreArchivo);

// Guarda el historial de jugadores en un archivo binario.
void recordSave(Jugador *historial, const char *nombreArchivo, int cantidadRegistros);

//Inserta un nuevo jugador al final del historial en memoria dinámica.
void insertRecordEOF(Jugador **historial, Jugador nuevoJugador, int cantidadRegistros);

// Verifica la cantidad de registros de jugadores en el archivo binario.
int recordSize(const char *nombreArchivo);

// Funcion para imprimir el arreglo de Jugadores que estaba en el archivo
void showRecord(Jugador *historial, int cantidadRegistros);


#endif // RECORD_H