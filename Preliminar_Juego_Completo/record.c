#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> // Para calloc y realloc

////////////////////////Funciones propias////////////////////////

#include "record.h"     // donde esta la funcion para buscar configuracion en .env

/////////////////////////////////////////////////////////////////////////////////////

// Recordatorio funcion impresion jugador actual para hacerla similar ?
/* // Imprime la información relevante de un jugador, como su nombre, saldo y estadísticas.
void imprimirJugador(const Jugador *jugador) {
    if (jugador == NULL) {
        printf("Jugador no válido.\n");
        return;  // Si el puntero del jugador es nulo, se imprime un mensaje y se retorna.
    }

    // Imprimir el nombre del jugador y sus estadísticas
    printf("Jugador: %s\n", jugador->nombre);
    printf("Saldo: $%d\n", jugador->saldo);
    printf("Victorias: %d | Derrotas: %d | BlackJacks: %d\n",
           jugador->victorias, jugador->derrotas, jugador->blackjack);
}
*/

/* //Recordatorio struct:
// // Estructura completa para un jugador
// typedef struct {
//     char nombre[MAX_NOMBRE];  // Nombre del jugador
//     int saldo;                // Dinero del jugador
//     int victorias;            // Número de partidas ganadas
//     int derrotas;             // Número de partidas perdidas
//     int blackjack;              // Número de partidas empatadas
// } Jugador;
*/

//--> Declaracion de funciones PROTOTIPO -> Usando Realloc

//Lee el historial de jugadores desde un archivo binario y lo guarda en memoria dinámica.
void recordImport(Jugador **historial, const char *nombreArchivo) {
    // Verificar si el archivo existe y abrirlo en modo binario
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo no existe, se creará al guardar.\n");
        return;
    }

    // Obtener el número de registros del archivo usando recordSize
    int cantidadRegistros = recordSize(nombreArchivo);
    if (cantidadRegistros == 0) {
        fclose(archivo);  // Si no hay registros, cerrar archivo
        return;
    }

    // Asignar memoria dinámica para los registros
    if (*historial == NULL) {
        *historial = malloc(cantidadRegistros * sizeof(Jugador));
    } else {
        *historial = realloc(*historial, cantidadRegistros * sizeof(Jugador));
    }
    //Manejo del error
    if (*historial == NULL) {
        printf("Error al asignar memoria para el historial.\n");
        fclose(archivo);
        return;
    }

    // Leer los registros del archivo
    fread(*historial, sizeof(Jugador), cantidadRegistros, archivo);
    fclose(archivo);
}

// Guarda el historial de jugadores en un archivo binario.
void recordSave(Jugador *historial, const char *nombreArchivo, int cantidadRegistros) {
    // Abrir archivo para escritura en binario
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Escribir los registros al archivo
    fwrite(historial, sizeof(Jugador), cantidadRegistros, archivo);
    fclose(archivo);
}

//Inserta un nuevo jugador al final del historial en memoria dinámica.
void insertRecordEOF(Jugador **historial, Jugador nuevoJugador, int cantidadRegistros) {
    // Redimensionar el arreglo para agregar un nuevo jugador
    if (*historial == NULL) {
        *historial = malloc((cantidadRegistros + 1) * sizeof(Jugador));
    } else {
        *historial = realloc(*historial, (cantidadRegistros + 1) * sizeof(Jugador));
    }
    //Manejo del error
    if (*historial == NULL) {
        printf("Error al redimensionar la memoria.\n");
        return;
    }

    // Insertar el nuevo jugador al final del arreglo
    (*historial)[cantidadRegistros] = nuevoJugador;
}

// Verifica la cantidad de registros de jugadores en el archivo binario.
int recordSize(const char *nombreArchivo) {
    // Intentar abrir el archivo para lectura en binario
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        return 0;  // El archivo no existe, no hay registros
    }

    // Determinar el tamaño del archivo
    fseek(archivo, 0, SEEK_END);  // Ir al final del archivo
    long tamañoArchivo = ftell(archivo);  // Obtener el tamaño en bytes
    fseek(archivo, 0, SEEK_SET);  // Volver al inicio del archivo

    // Calcular la cantidad de registros
    int cantidadRegistros = tamañoArchivo / sizeof(Jugador);
    fclose(archivo);

    return cantidadRegistros;
}

// Muestra el historial de jugadores almacenados en memoria.
// Esta función imprime los detalles de cada jugador desde el arreglo de historial.
void showRecord(Jugador *historial, int cantidadRegistros) {
    if (historial == NULL || cantidadRegistros == 0) {
        printf("No hay registros para mostrar.\n");
        return;
    }

    printf("Historial de Jugadores:\n");
    for (int i = 0; i < cantidadRegistros; i++) {
        printf("Jugador %d: %s | Saldo: %d | Victorias: %d | Derrotas: %d | BlackJacks: %d\n",
               i + 1, historial[i].nombre, historial[i].saldo,
               historial[i].victorias, historial[i].derrotas, historial[i].blackjack);
    }
}





