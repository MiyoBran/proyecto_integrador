/* ScoreboardV3.c
#include<stdio.h>
*/
#include<time.h>
#include<string.h>
#include<stdlib.h>

// Includes Propios del proyecto
#include "scoreboardV3.h" // funciones para uso de memoria dinamica en scoreboardV3.c
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env



/// Implementacion usando memoria dinamica --> **scorelist en las funciones que pueden cambiar el puntero para poder usar realloc


// Carga los puntajes desde el archivo a una lista dinámica
// ahora lee del archivo y aumenta dinámicamente el tamaño de scoreList
void fileImport(Score **scoreList, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo no existe, se creará al guardar.\n");
        return;
    }
    int count = 0;
    while (fread(&(*scoreList)[count], sizeof(Score), 1, archivo) == 1) {
        count++;
        *scoreList = realloc(*scoreList, (count + 1) * sizeof(Score));  // Aumenta el tamaño dinámico para almacenar nuevos registros
        if (*scoreList == NULL) {  // Verificación de error en realloc
            printf("Error al asignar memoria.\n");
            fclose(archivo);
            return;
        }
    }
    fclose(archivo);
}

// Guarda los puntajes en el archivo ---> Solo los registros validos
void fileSave(Score *scoreList, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    int i = 0;
    while (scoreList[i].money > 0) { // Guardar solo puntajes válidos
        fwrite(&scoreList[i], sizeof(Score), 1, archivo);
        i++;
    }
    fclose(archivo);
    printf("Archivo guardado exitosamente en '%s'.\n", nombreArchivo);  // Mensaje de éxito
}


// Verifica si el nuevo jugador tiene un puntaje suficiente para entrar al ranking y lo inserta si es necesario
void checkScore(Score **scoreList, Score nuevoJugador, const char *nombreArchivo) {
    int i = 0;
    // Incrementa el i hasta encontrar el ultimo lugar vacio
    while ((*scoreList)[i].money > 0 && i < TOTAL_REGISTROS) i++;

 
    if (i >= TOTAL_REGISTROS) { // Lista llena, verifica si el nuevo jugador califica
        if (nuevoJugador.money > (*scoreList)[TOTAL_REGISTROS - 1].money) {
            (*scoreList)[TOTAL_REGISTROS - 1] = nuevoJugador;
            sortRanking(*scoreList);
        } else {
            printf("El jugador no tiene suficiente dinero para entrar en el ranking.\n");
        }
    } else {
        insertPlayer(scoreList, nuevoJugador);
    }

    updateRanking(scoreList, nombreArchivo);
}

    

// Inserta un nuevo jugador en el ranking, expandiendo la lista si es necesario
void insertPlayer(Score **scoreList, Score nuevoJugador) {
    int i = 0;
    // Incrementa el i hasta encontrar el ultimo lugar vacio
    while ((*scoreList)[i].money > 0 && i < TOTAL_REGISTROS) i++;
    
    // Aumentamos el tamaño del arreglo si corresponde
    if (i < TOTAL_REGISTROS) {
        (*scoreList)[i] = nuevoJugador;
    } else {
        Score *temp = realloc(*scoreList, (i + 1) * sizeof(Score));
        if (temp == NULL) {  // Verificación de error en realloc
            printf("Error al asignar memoria.\n");
            return;
        }
        *scoreList = temp;
        (*scoreList)[i] = nuevoJugador;
    }

    sortRanking(*scoreList);
}

// Actualiza el ranking, asigna las posiciones y guarda en el archivo
void updateRanking(Score **scoreList, const char *nombreArchivo) {
    int i = 0;
    while ((*scoreList)[i].money > 0) {
        (*scoreList)[i].ranking = i + 1;
        i++;
    }
    fileSave(*scoreList, nombreArchivo);
}

// Muestra el ranking en formato de tabla y actualiza desde el archivo
// recordar llamar a fileImport con & , para mantener el doble puntero si cambia el tamaño
void showRanking(Score *scoreList, const char *nombreArchivo) {
    fileImport(&scoreList, nombreArchivo);
    printf("\nRanking\tNombre\tDinero\n");

    int i = 0;
    while (scoreList[i].money > 0) {
        printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        i++;
    }
}

// Ordena la lista de jugadores en función del dinero en forma descendente
void sortRanking(Score *scoreList) {
    int count = 0;
    // Busco el primer lugar vacio sin pasarme del total
    while (scoreList[count].money > 0 && count < TOTAL_REGISTROS) {
        count++;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (scoreList[j].money < scoreList[j + 1].money) {
                Score temp = scoreList[j];
                scoreList[j] = scoreList[j + 1];
                scoreList[j + 1] = temp;
            }
        }
    }
}
// Utilidades
// Genera un nombre aleatorio con una letra, una vocal y un número
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


// Crea un nuevo jugador con el nombre y dinero especificado
Score crearScore(const char *nombre, float dinero) {
    Score nuevoJugador;
    nuevoJugador.ranking = 0; // Se actualizará en `updateRanking`
    strncpy(nuevoJugador.name, nombre, sizeof(nuevoJugador.name) - 1);
    nuevoJugador.name[sizeof(nuevoJugador.name) - 1] = '\0'; // Asegurarse que el nombre termine en nulo
    nuevoJugador.money = dinero;
    return nuevoJugador;
}
