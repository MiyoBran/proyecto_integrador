#include<time.h>
#include<string.h>
#include<stdlib.h>

// Includes Propios del proyecto
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env

/// Implementacion usando arreglo declarado con MALLOC

//Abre archivo con arreglos tipo Score y actualiza el array
void rankingImport(Score *scoreList, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("El archivo de Ranking no existe, se creará al guardar.\n");
        return;
    }
    fread(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}

//Guarda archivo con un arreglo tipo Score
void rankingSave(Score *scoreList, const char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(scoreList, sizeof(Score), TOTAL_REGISTROS, archivo);
    fclose(archivo);
}


// Agregar un jugador al ranking si hay lugar vacio o si es mayor al ultimo
void checkScore(Score *scoreList, Score nuevoJugador,const char *nombreArchivo) {
    // Si el último jugador tiene dinero, reemplazarlo si el nuevo tiene más dinero
    if (scoreList[TOTAL_REGISTROS - 1].money > 0) {
        // Si el último jugador tiene dinero, reemplazarlo si el nuevo tiene más dinero
        if (nuevoJugador.money > scoreList[TOTAL_REGISTROS - 1].money) {
            printf("🎉 ¡Felicidades! 🎉\n");
            printf("Has logrado ingresar al ranking con un saldo impresionante: $%.1f.\n", nuevoJugador.money);
            printf("💪 ¡Sigue así y trata de mantener tu lugar entre los mejores!\n");
            scoreList[TOTAL_REGISTROS - 1] = nuevoJugador;
            sortRanking(scoreList);
        } else {
            printf("🚫 ¡Lo sentimos! No alcanzaste el saldo necesario para entrar al ranking.\n");
            printf("🎯 El saldo más bajo en el ranking actual es: $%.1f.\n", scoreList[TOTAL_REGISTROS - 1].money);
            printf("💡 ¡Sigue jugando! Con un poco más de esfuerzo, seguro lo lograrás.\n");
        }
    } else {
        // Insertar el nuevo jugador al primer lugar vacío
        printf("🎉 ¡Felicidades! 🎉\n");
        printf("Tu puntaje ha sido registrado exitosamente en el ranking.\n");
        insertPlayer(scoreList, nuevoJugador);
    }

    // Actualizar los rankings después de insertar
    updateRanking(scoreList, nombreArchivo);

}

// Función para insertar al jugador en el ultimo lugar
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
    rankingSave(scoreList, nombreArchivo);  // Guardar cambios en el archivo
}

// Función para imprimir como tabla el ranking --> rankingDisplay?
void showRanking(Score scoreList[TOTAL_REGISTROS], const char *nombreArchivo) {
    // Importar datos del archivo
    rankingImport(scoreList, nombreArchivo);

    // Encabezado de la tabla
    printf("\n===================== RANKING =====================\n");
    printf("%-8s %-20s %-10s\n", "Ranking", "Nombre", "Dinero");
    printf("--------------------------------------------------\n");

    // Imprimir cada entrada del ranking
    for (int i = 0; i < TOTAL_REGISTROS; i++) {
        // Solo mostrar entradas válidas
        if (scoreList[i].money > 0 && strlen(scoreList[i].name) > 0) {
            printf("%-8d %-20s $%-10.2f\n", 
                   scoreList[i].ranking, 
                   scoreList[i].name, 
                   scoreList[i].money);
        }
    }

    // Cierre decorativo
    printf("==================================================\n");
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

// Funcion de Prueba / Tests
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


// Funcion para convertir datos de la en arreglo tipo Score
Score crearScore(const char *nombre, float dinero) {
    Score nuevoJugador;
    nuevoJugador.ranking = 0; // Se actualizará en `updateRanking`
    strncpy(nuevoJugador.name, nombre, sizeof(nuevoJugador.name) - 1);
    nuevoJugador.name[sizeof(nuevoJugador.name) - 1] = '\0'; // Asegurarse que el nombre termine en nulo
    nuevoJugador.money = dinero;
    return nuevoJugador;
}
