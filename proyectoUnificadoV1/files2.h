#ifndef FILES2_H
#define FILES2_H

#include <stdio.h>

// Definición de la estructura Score
typedef struct {
    char name[50]; // Nombre del jugador
    float money;   // Dinero del jugador
    int ranking;   // Ranking del jugador
} Score;

// Definición de la constante para el número total de registros
#define TOTAL_REGISTROS 10 // Cantidad de jugadores que guardamos en el archivo
#define MAX_LINEA 256      // Definir el tamaño máximo de una línea


// Declaración de funciones quiza alguna es de gamelogic
char* obtenerValorConfiguracion(const char *clave);
void importarDesdeArchivo(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void guardarEnArchivo(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo);

void mostrarJugadores(Score scoreList[TOTAL_REGISTROS]);
void ordenarJugadores(Score scoreList[TOTAL_REGISTROS]);

/*ESTA LA LLAMO DESDE MI MAIN DE PRUEBA, seguramente no hace falta*/
void agregarJugador(Score scoreList[TOTAL_REGISTROS], Score nuevoJugador);


#endif // files_h