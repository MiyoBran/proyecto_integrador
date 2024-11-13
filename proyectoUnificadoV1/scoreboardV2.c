/*
#include<stdio.h>
*/
#include<time.h>
#include<string.h>
#include<stdlib.h>

// Includes Propios del proyecto
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env

/// Implementacion usando memoria dinamica

void fileImport(Score *scoreList, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo no existe, se creará al guardar.\n");
        return;
    }
    fread(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

void fileSave(Score *scoreList, const char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}





// Implementación de agregarJugador, mostrarJugadores y ordenarJugadores similar a `files2.c`

// Función para agregar un jugador al ranking
void checkScore(Score *scoreList, Score nuevoJugador,const char *nombreArchivo) {
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        // Si el último jugador tiene dinero, reemplazarlo si el nuevo tiene más dinero
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;
            sortRanking(scoreList);
        } else {
            printf("El jugador no tiene suficiente dinero para entrar en el ranking.\n");
        }
    } else {
        // Insertar el nuevo jugador al primer lugar vacío
        insertPlayer(scoreList, nuevoJugador);
    }

    // Actualizar los rankings después de insertar
    updateRanking(scoreList,nombreArchivo);
}

// Función para insertar al jugador
void insertPlayer(Score *scoreList, Score nuevoJugador) {
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money == 0) {
            scoreList[i] = nuevoJugador;
            break;
        }
    }
    sortRanking(scoreList);
}

// Función para actualizar los rankings
void updateRanking(Score *scoreList,const char *nombreArchivo) {
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            scoreList[i].ranking = i + 1;
        }
    }
    fileSave(scoreList, nombreArchivo);  // Guardar cambios en el archivo
}

// Función para imprimir como tabla el ranking
void showRanking(Score scoreList[TOTAL_REGISTROS],const char *nombreArchivo) {

    fileImport(scoreList, nombreArchivo);
    printf("\nRanking\tNombre\tDinero\n");
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        }
    }
}

// Función para ordenar la lista de jugadores en función del dinero (descendente) - Bubble Sort porque son pocos
void sortRanking(Score scoreList[TOTAL_REGISTROS]) {
    for (int i = 0; i < TOTAL_REGISTROS - 1; i++) {
        for (int j = 0; j < TOTAL_REGISTROS - 1 - i; j++) {
            if (scoreList[j].money < scoreList[j + 1].money) {
                Score temp = scoreList[j];
                scoreList[j] = scoreList[j + 1];
                scoreList[j + 1] = temp;
            }
        }
    }
}

char *generarNombreAleatorio() {
    static char nombre[4];
    const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char vocales[] = "aeiou";

    nombre[0] = letras[rand() % 26];    // Letra mayúscula aleatoria
    nombre[1] = vocales[rand() % 5];    // Vocal minúscula aleatoria
    nombre[2] = '0' + (rand() % 10);    // Número del 0 al 9
    nombre[3] = '\0';                   // Fin de cadena

    return nombre;
}


/// funcion para transformar el nombre y monto en un score, despues hay que llamar a checkscore
Score crearScore(const char *nombre, float dinero) {
    Score nuevoJugador;
    nuevoJugador.ranking = 0; // Se actualizará en `updateRanking`
    strncpy(nuevoJugador.name, nombre, sizeof(nuevoJugador.name) - 1);
    nuevoJugador.name[sizeof(nuevoJugador.name) - 1] = '\0'; // Asegurarse que el nombre termine en nulo
    nuevoJugador.money = dinero;
    return nuevoJugador;
}
