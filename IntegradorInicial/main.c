#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "archivo_configuracion.h"

#define TOTAL_REGISTROS 10 // cantidad de jugadores maximo en el ranking

typedef struct
{
    int ranking;
    char name[50];
    float money;
} Jugador;

void importarDesdeArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void guardarEnArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo);
void agregarJugador(Jugador scoreList[TOTAL_REGISTROS], Jugador nuevoJugador);
void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]);
Jugador crearJugador();
void ordenarJugadores(Jugador scoreList[TOTAL_REGISTROS]);

int main()
{
    srand(time(NULL)); // Inicializa el generador de números aleatorios
    Jugador scoreList[TOTAL_REGISTROS] = {0};
    int opcion;
    /*En archivo_configuracion.c tenemos la funcion que busca en el archivo .env el nombre del archivo*/ 
    char *nombreArchivo = obtenerValorConfiguracion("archivo_datos"); 

    importarDesdeArchivo(scoreList, nombreArchivo);

    do
    {
        printf("\nMenú:\n");
        printf("1. Crear un jugador\n");
        printf("2. Mostrar lista de jugadores\n");
        printf("3. Terminar el programa\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarJugador(scoreList, crearJugador());
            guardarEnArchivo(scoreList, nombreArchivo);
            break;
        case 2:
            mostrarJugadores(scoreList);
            break;
        case 3:
            printf("Terminando el programa.\n");
            break;
        default:
            printf("Opción inválida. Inténtalo nuevamente.\n");
        }
    } while (opcion != 3);

    free(nombreArchivo);
    return 0;
}

void importarDesdeArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fread(scoreList, sizeof(Jugador), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

void guardarEnArchivo(Jugador scoreList[TOTAL_REGISTROS], const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "wb"); // WB si el archivo no existe, lo crea, si existe elimina su contenido
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n"); // cuando hay error al abrirlo(permisos x ej), pero quiza si se creo
        return;
    }

    fwrite(scoreList, sizeof(Jugador), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

void agregarJugador(Jugador scoreList[TOTAL_REGISTROS], Jugador nuevoJugador) {
    // Comprobar si hay espacio para un nuevo jugador
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        // Verificar si el nuevo jugador debe reemplazar al de menor dinero
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            // Eliminar el último registro
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;

            // Ordenar la lista después de agregar el nuevo jugador
            ordenarJugadores(scoreList);
        } else {
            printf("El nuevo jugador no tiene suficiente dinero para entrar en el ranking.\n");
        }
    } else {
        // Si hay espacio, agregar el nuevo jugador al primer lugar vacío
        for (int i = 0; i < TOTAL_REGISTROS; i++) {
            if (scoreList[i].money == 0) { // Encuentra el primer registro vacío
                scoreList[i] = nuevoJugador; // Agregar el nuevo jugador aquí
                break;
            }
        }

        // Ordenar la lista después de agregar el nuevo jugador
        ordenarJugadores(scoreList);
    }

    // Actualizar los rankings
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        if (scoreList[i].money > 0) {
            scoreList[i].ranking = i + 1; // Actualiza el ranking
        }
    }
}

Jugador crearJugador()
{
    Jugador nuevoJugador;
    char vocales[] = {'a', 'e', 'i', 'o', 'u'};

    // Generar el nombre
    nuevoJugador.name[0] = 'A' + (rand() % 26); // Letra mayúscula
    nuevoJugador.name[1] = vocales[rand() % 5]; // Vocal minúscula
    nuevoJugador.name[2] = '0' + (rand() % 10 + 1); // Número del 1 al 10
    nuevoJugador.name[3] = '\0'; // Terminar el string

    // Generar el dinero aleatorio entre 0 y 10,000
    nuevoJugador.money = (float)(rand() % 10001); // 0 a 10000
    return nuevoJugador;
}

void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]) {
    printf("\nRanking\tNombre\tDinero\n");
    for (int i = 0; i < TOTAL_REGISTROS; i++) { // Iterar hasta TOTAL_REGISTROS
        if (scoreList[i].money > 0) { // Solo mostrar los que tienen dinero
            printf("%d\t%s\t%.2f\n", scoreList[i].ranking, scoreList[i].name, scoreList[i].money);
        }
    }
}

void ordenarJugadores(Jugador scoreList[TOTAL_REGISTROS]) {
    for (int i = 0; i < TOTAL_REGISTROS - 1; i++) {
        for (int j = 0; j < TOTAL_REGISTROS - 1 - i; j++) {
            // Ordenar por dinero de mayor a menor
            if (scoreList[j].money < scoreList[j + 1].money) {
                Jugador temp = scoreList[j];
                scoreList[j] = scoreList[j + 1];
                scoreList[j + 1] = temp;
            }
        }
    }
}
