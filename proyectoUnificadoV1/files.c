#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "files.h"
// #include "gamelogic.h" // para usar el testfiles, comentar este
// #include "graphics_storage.h" /// para usar el testfiles comentar esto




// Función para importar datos de jugadores desde un archivo
void importarDesdeArchivo(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo no existe, se creará al guardar.\n");
        return;
    }

    fread(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

// Función para guardar datos de jugadores en un archivo
void guardarEnArchivo(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

// Función para agregar un jugador al ranking
void agregarJugador(Score scoreList[TOTAL_REGISTROS], Score nuevoJugador) {
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        // Reemplazar al último si el nuevo jugador tiene más dinero
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;
            ordenarJugadores(scoreList);
        } else {
            printf("El jugador no tiene suficiente dinero para entrar en el ranking.\n");
        }
    } else {
        // Agregar el nuevo jugador al primer lugar vacío
        for (int i = 0; i < TOTAL_REGISTROS; i++) {
            if (scoreList[i].money == 0) {
                scoreList[i] = nuevoJugador;
                break;
            }
        }
        ordenarJugadores(scoreList);
    }

    // Actualizar los rankings
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            scoreList[i].ranking = i + 1;
        }
    }
}

// Función para mostrar los jugadores en el ranking
void mostrarJugadores(Score scoreList[TOTAL_REGISTROS]) {
    printf("\nRanking\tNombre\tDinero\n");
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        }
    }
}

// Función para ordenar la lista de jugadores en función del dinero (descendente) - Bubble Sort porque son pocos
void ordenarJugadores(Score scoreList[TOTAL_REGISTROS]) {
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

/*De semana 11 git materia lo que esta en el .env, se saca con esta funcion */
char* obtenerValorConfiguracion(const char *clave) {
    
    FILE *archivo = fopen(".env", "r"); //<- si hago un archivo txt tengo que cambiar aca el nombre
    if (archivo == NULL) {
        printf("Error al abrir el archivo de configuración.\n");
        return NULL;
    }

    char linea[MAX_LINEA];
    char *valor = NULL;

    while (fgets(linea, sizeof(linea), archivo) && valor == NULL) {
        // Verifica si la línea contiene la clave buscada
        if (strncmp(linea, clave, strlen(clave)) == 0) {
            // Busca el caracter '=' en la línea
            char *igual = strchr(linea, '=');
            if (igual != NULL) {
                // El valor está después del símbolo '='
                valor = strdup(igual + 1);
                
                // Eliminar salto de línea si lo hay
                valor[strcspn(valor, "\n")] = '\0';
            }
        }
    }

    fclose(archivo);
    return valor;
}
