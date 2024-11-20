#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> // Para calloc y realloc

////////////////////////Funciones propias////////////////////////

#include "record.h"     // donde esta la funcion para buscar configuracion en .env

/////////////////////////////////////////////////////////////////////////////////////

//--> Declaracion de funciones 

//Lee el historial de jugadores desde un archivo binario y lo guarda en memoria dinámica.
void recordImport(Jugador **historial, const char *nombreArchivo) {
    // Verificar si el archivo existe y abrirlo en modo binario
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo de historial no existe. No se encontraron registros previos.\n" );
        return;
    }

    // Obtener el número de registros del archivo usando recordSize
    int cantidadRegistros = recordSize(nombreArchivo);
    if (cantidadRegistros == 0) {
        printf("El archivo está vacío. No se encontraron registros.\n");
        fclose(archivo);  // Si no hay registros, cerrar archivo
        return;
    }

    printf("Se encontraron %d registros.\n", cantidadRegistros);

    // Asignar memoria dinámica para los registros
    if (*historial == NULL) {
        *historial = malloc(cantidadRegistros * sizeof(Jugador));
    } else {
        *historial = realloc(*historial, cantidadRegistros * sizeof(Jugador));
    }

    // Manejo de error al asignar memoria
    if (*historial == NULL) {
        printf("Error al asignar memoria para el historial. No se pudieron cargar los registros.\n");
        fclose(archivo);
        return;
    }

    // Leer los registros del archivo
    size_t leidos = fread(*historial, sizeof(Jugador), cantidadRegistros, archivo);
    if (leidos < (size_t)cantidadRegistros) {
        printf("Advertencia: Solo se pudieron leer %zu de registros del archivo %s.\n", leidos, cantidadRegistros);
    } else {
        printf("Los registros se cargaron exitosamente.\n");
    }
    fclose(archivo);
}

// Guarda un archivo con struct de tipo Jugador
void recordSave(Jugador *historial, const char *nombreArchivo, int cantidadRegistros) {
    // Abrir archivo para escritura en binario
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
      printf("Error: No se pudo abrir el archivo de historial para guardar los registros.\n");
        return;
    }

    // Escribir los registros al archivo
    size_t escritos = fwrite(historial, sizeof(Jugador), cantidadRegistros, archivo);
    fclose(archivo);
    
    // Verificar si la escritura fue completa : depuracion
    /*if (escritos < (size_t)cantidadRegistros) {
        printf("Advertencia: Solo se pudieron guardar %zu de %d registros en el archivo %s.\n", escritos, cantidadRegistros, nombreArchivo);
    } else {
        printf("Se guardaron exitosamente %d registros en el archivo %s.\n", cantidadRegistros, nombreArchivo);
    }
    */


}

//Escribe" un nuevo jugador al final del historial en memoria dinámica.
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





