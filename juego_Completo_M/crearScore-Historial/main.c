#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// para compilar ggc
// gcc -o crearArchivos main.c jugador.c config.c record.c scoreboard.c
////////////////////////Funciones propias////////////////////////
#include "config.h"     // Configuración del sistema y lectura de .env
#include "jugador.h"    // Funciones y estructuras del jugador durante la sesión
#include "scoreboard.h" // Estructuras y funciones para el manejo del ranking
#include "record.h"     // Funciones para el manejo del historial de partidas
// (revisar los includes que tienen adentro, algunas cosas hay que borrar x redundantes o cambiar nombres)
/////////////////////////////////////////////////////////////////////////////////////

// Función para leer y validar un entero
int leerEntero(const char *mensaje) {
    char buffer[20];
    int valor;
    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error al leer la entrada. Intente nuevamente.\n");
            continue;
        }

        // Intentar convertir la entrada a entero
        if (sscanf(buffer, "%d", &valor) != 1) {
            printf("Entrada inválida. Por favor, ingrese un número válido.\n");
        } else {
            return valor;
        }
    }
}



int main() {
    // Variables necesarias
    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Inicialización del puntero historial a NULL; la memoria se asigna dentro de recordImport()
    Jugador *historial = NULL; // La memoria se asigna dentro de recordImport


    // Asignando memoria dinámica para el arreglo de lista Ranking
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }


    // Buscando Nombre del Archivo de Ranking
    char *nombreArchivoRanking = getconfig("archivo_ranking");
    if (nombreArchivoRanking == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }

    // Buscando Nombre del Archivo de Historial
    char *recordFileName = getconfig("archivo_historial");
    if (recordFileName == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(historial);
        return 1;
    }

    // Verificar cuántos registros existen en el archivo
    int cantidadRegistros = recordSize(recordFileName);  // Verificar cuántos registros existen en el archivo
    // Importar registros del archivo
    recordImport(&historial, recordFileName);

    // Opcionales , se puede no usar mi struct y comentar

    // Para poder agergar en struct Ranking/Historial 
    char nombreJugador[MAX_NOMBRE];
    Jugador jugador1; // Estructura con Nombre, Saldos, victorias y empates

    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    // Declaración de variables
    char nombreFinal[MAX_NOMBRE];
    int puntajeFinal, victoriasFinal, derrotasFinal, blackjackFinal;

    // Solicitar al usuario que ingrese los datos
    printf("Ingrese el nombre del jugador: ");
    if (fgets(nombreFinal, MAX_NOMBRE, stdin) != NULL) {
        // Eliminar el salto de línea si está presente
        size_t len = strlen(nombreFinal);
        if (len > 0 && nombreFinal[len - 1] == '\n') {
            nombreFinal[len - 1] = '\0';
        }
    } else {
        printf("Error al leer el nombre del jugador.\n");
        return 1;
    }

    // Leer y validar cada valor entero
    puntajeFinal = leerEntero("Ingrese el saldo del jugador: ");
    victoriasFinal = leerEntero("Ingrese el número de victorias: ");
    derrotasFinal = leerEntero("Ingrese el número de derrotas: ");
    blackjackFinal = leerEntero("Ingrese el número de blackjack: ");

    // Imprimir los datos ingresados
    printf("\nDatos ingresados:\n");
    printf("Nombre: %s\n", nombreFinal);
    printf("Saldo: %d\n", puntajeFinal);
    printf("Victorias: %d\n", victoriasFinal);
    printf("Derrotas: %d\n", derrotasFinal);
    printf("Blackjack (empates): %d\n", blackjackFinal);


    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/



    // Crear structs para manejar el ranking e historial
    Score nuevoScore = crearScore(nombreFinal, puntajeFinal); // Convierte nombre y dinero a tipo Score
    Jugador nuevoJuego = crearHistorial(nombreFinal, puntajeFinal, victoriasFinal, derrotasFinal, blackjackFinal); // Manejo del historial

    // Actualizacion del Ranking
    rankingImport(scoreList, nombreArchivoRanking);

    // Verificar y agregar el jugador al ranking
    checkScore(scoreList, nuevoScore, nombreArchivoRanking); // Verifica y agrega el jugador

    // Mostrar el ranking actualizado
    printf("\n=================== RANKING ACTUALIZADO ===================\n");
    printf("----------------------------------------------------------\n");

    showRanking(scoreList, nombreArchivoRanking);

    // Línea decorativa final
    printf("==========================================================\n");

    // Mensaje de despedida
    printf("Gracias por jugar. ¡Hasta pronto! 🎉\n");
    printf("==========================================================\n");

       
    // Agregar el nuevo registro al historial --> importante tiene que haber 1 struct jugador creado
    insertRecordEOF(&historial, nuevoJuego, cantidadRegistros);

    // Guardar el historial actualizado
    cantidadRegistros++;  // Incrementar el número de registros
    recordSave(historial, recordFileName, cantidadRegistros);

    // Mostrar el Historial actualizado
    printf("\n=================== HISTORIAL ACTUALIZADO ===================\n");
    printf("----------------------------------------------------------\n");

    showRecord(historial, cantidadRegistros);  // Llamamos a showRecord para imprimir el historial

    // Línea decorativa final
    printf("==========================================================\n");

    // Mensaje de despedida
    printf("Gracias por jugar. ¡Hasta pronto! 🎉\n");
    printf("==========================================================\n");

    
 

    // Liberar la memoria dinámica antes de salir
    if (scoreList != NULL) free(scoreList);
    if (historial != NULL) free(historial);

    // Revisar si es necesario liberar memoria para nombres de archivo si no son asignados dinámicamente
    if (nombreArchivoRanking != NULL) free(nombreArchivoRanking);
    if (recordFileName != NULL) free(recordFileName);


    return 0;
}