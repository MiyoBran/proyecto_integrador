#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Para manejar valores booleanos
#include <string.h>
#include <unistd.h>  // Para la función usleep (para control de velocidad)

////////////////////////Funciones propias////////////////////////

#include "jugador.h"     // donde estan declaradas las funciones del JUGADOR durante la SESION

/////////////////////////////////////////////////////////////////////////////////////



// Declaracion de funciones -> Jugador
// Configura los valores iniciales de un jugador al inicio de la sesión de juego.
void inicializarJugadorGlobal(Jugador *jugador, const char *nombre, int saldoInicial) {
    // Asegurarse de que el nombre esté dentro del límite y terminado en '\0'
    // Limita la longitud del nombre al máximo permitido (MAX_NOMBRE) y asegura que esté bien terminado
    strncpy(jugador->nombre, nombre, MAX_NOMBRE - 1);
    jugador->nombre[MAX_NOMBRE - 1] = '\0';  // Garantiza que el nombre esté siempre correctamente terminado

    // Verificar que el saldo inicial no sea negativo
    if (saldoInicial < 0) {
        // Si el saldo inicial es negativo, asigna un saldo por defecto de 0
        printf("Saldo inicial no válido. Se asigna saldo 0 por defecto.\n");
        saldoInicial = 0; 
    }

    // Asignar el saldo inicial al jugador
    jugador->saldo = saldoInicial;

    // Inicializar estadísticas del jugador (victorias, derrotas y blackjack)
    jugador->victorias = 0;      // Iniciar las victorias en 0
    jugador->derrotas = 0;       // Iniciar las derrotas en 0
    jugador->blackjack = 0;      // Iniciar los blackjack en 0
}

// Esta función actualiza las estadísticas del jugador según el resultado de la partida.
void actualizarEstadisticas(Jugador *jugador, bool gano, bool blackjack) {
    // Si el jugador ha obtenido un blackjack, se incrementa su contador de blackjack
    if (blackjack) {
        jugador->blackjack++;  // Aumenta la cantidad de blackjack ganados
    } 
    // Si el jugador ha ganado la partida (pero no hizo un blackjack), se incrementa su contador de victorias
    else if (gano) {
        jugador->victorias++;  // Aumenta la cantidad de victorias
    } 
    // Si el jugador ha perdido la partida, se incrementa su contador de derrotas
    else {
        jugador->derrotas++;  // Aumenta la cantidad de derrotas
    }
}

// Esta función permite sumar o restar una cantidad al saldo del jugador.
void modificarSaldo(Jugador *jugador, int cantidad) {
    jugador->saldo += cantidad;  // Modifica el saldo del jugador sumando (o restando) la cantidad especificada
}

// Imprime la información relevante de un jugador, como su nombre, saldo y estadísticas.// Función para imprimir la información de un jugador
void imprimirJugador(const Jugador *jugador) {
    if (jugador == NULL) {
        printf("===============================================\n");
        printf("❌ Jugador no válido. Por favor verifica los datos.\n");
        printf("===============================================\n\n");
        return; // Si el puntero del jugador es nulo, se imprime un mensaje y se retorna.
    }

    printf("\n===============================================\n");
    printf(" 📋 Información del Jugador\n");
    printf("===============================================\n");
    printf(" 🧑 Nombre: %-30s\n", jugador->nombre);
    printf(" 💰 Saldo: $%-29d\n", jugador->saldo);
    printf(" 🏆 Estadísticas:\n");
    printf("    - Victorias: %-22d\n", jugador->victorias);
    printf("    - Derrotas: %-23d\n", jugador->derrotas);
    printf("    - BlackJacks: %-20d\n", jugador->blackjack);
    printf("===============================================\n\n");
}
// Pregunta al jugador si desea jugar otra partida y valida la entrada.
bool preguntarJugarOtra() {
    int respuesta;
    printf("\n¿Desea jugar otra partida? (1 para Sí, 0 para No): ");

    // Asegurarse de que la entrada sea válida
    while (scanf("%d", &respuesta) != 1 || (respuesta != 0 && respuesta != 1)) {
        // Limpiar el buffer de entrada en caso de error
        while(getchar() != '\n'); // Limpiar el buffer para evitar lecturas incorrectas
        printf("Entrada no válida. Por favor ingrese 1 para Sí o 0 para No: ");
    }

    // Retorna true si la respuesta es 1, indicando que el jugador desea continuar.
    return respuesta == 1; // Si respuesta es 1, se retorna true, de lo contrario false.
}

// Mensaje inicial al iniciar la ejecución del programa
void mensajeBienvenida() {
    printf("\n");
    printf("===============================================\n");
    printf(" 🃏 ¡Bienvenid@ al emocionante juego de Blackjack! 🎉\n");
    printf("===============================================\n");

}

// Mensaje donde nos pide ingresar un nombre usando MAX_NOMBRE de límite
void preguntarNombre(char *nombreJugador) {
    printf("Por favor, introduce tu nombre (máximo %d caracteres): ", MAX_NOMBRE - 1);
    if (fgets(nombreJugador, MAX_NOMBRE, stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        nombreJugador[0] = '\0';  // Asigna una cadena vacía en caso de error
        return;
    }

    // Eliminar el salto de línea si está presente
    size_t longitud = strlen(nombreJugador);
    if (longitud > 0 && nombreJugador[longitud - 1] == '\n') {
        nombreJugador[longitud - 1] = '\0';
    } else {
        // Si fgets no leyó el salto de línea, limpiar el buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

// Saludar al jugador con un mensaje personalizado
void saludarJugador(const char *nombreJugador) {
    printf("\n");
    printf("=======================================\n");
    printf(" 🌟 ¡Hola, %s! 🌟\n", nombreJugador);
    printf("=======================================\n");
    printf(" 🎲 Pon a prueba tu estrategia y desafía al croupier.\n");
    printf(" 💰 ¡Apuesta, diviértete y demuestra tu habilidad! ✨\n");
    printf("=======================================\n\n");
}

// Función para crear un nuevo historial de jugador
Jugador crearHistorial(char nombre[], int saldo, int victorias, int derrotas, int blackjack) {
    Jugador nuevoJugador;

    // Copiar el nombre del jugador al nuevo historial
    strcpy(nuevoJugador.nombre, nombre);
    
    // Asignar los otros datos al historial
    nuevoJugador.saldo = saldo;
    nuevoJugador.victorias = victorias;
    nuevoJugador.derrotas = derrotas;
    nuevoJugador.blackjack = blackjack;

    // Devolver el historial del jugador
    return nuevoJugador;
}
// Función para mostrar el contenido de un archivo con diferentes velocidades de presentación
// según el parámetro 'velocidadDisplay'. La velocidad de presentación afecta cómo se 
// muestra el contenido: letra por letra, palabra por palabra, o línea por línea. Si el valor 
// de 'velocidadDisplay' es 0 o cualquier otro número, se muestra todo el contenido de una vez.
void mostrarContenidoArchivo(const char *nombreArchivo, int velocidadDisplay) {
    // Abre el archivo para lectura
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) { // Si el archivo no se puede abrir, muestra un mensaje de error y termina
        perror("No se puede abrir el archivo");
        return;
    }

    // Variables para almacenar los caracteres y las palabras leídas
    char c; // Variable para leer un carácter a la vez
    char palabra[1024]; // Buffer para leer palabras
    int i = 0; // Contador que no se utiliza en esta versión, se podría eliminar

    // Dependiendo del valor de 'velocidadDisplay', se toma una de las siguientes opciones:
    switch (velocidadDisplay) {
        case 1: // Mostrar letra por letra (más lento)
            // Lee el archivo carácter por carácter
            while ((c = fgetc(f)) != EOF) {
                putchar(c); // Imprime el carácter leído
                fflush(stdout);  // Asegura que el carácter se imprima inmediatamente
                usleep(500000);  // Pausa de 0.5 segundos entre caracteres
            }
            break;

        case 2: // Mostrar palabra por palabra (más rápido)
            // Lee el archivo palabra por palabra
            while (fscanf(f, "%1023s", palabra) != EOF) {
                printf("%s ", palabra); // Imprime la palabra leída
                fflush(stdout);  // Asegura que la palabra se imprima inmediatamente
                usleep(300000);  // Pausa de 0.3 segundos entre palabras
            }
            break;

        case 3: // Mostrar línea por línea (más rápido y respeta saltos de línea)
            // Lee el archivo línea por línea
            while (fgets(palabra, sizeof(palabra), f) != NULL) {
                printf("%s", palabra); // Imprime la línea leída
                fflush(stdout);  // Asegura que la línea se imprima inmediatamente
                usleep(500000);  // Pausa de 0.5 segundos entre líneas
            }
            break;

        default: // Mostrar todo el contenido de una vez (sin pausas)
            // Lee el archivo carácter por carácter hasta el final
            while ((c = fgetc(f)) != EOF) {
                putchar(c); // Imprime cada carácter directamente
            }
            break;
    }

    // Cierra el archivo una vez que se ha terminado de leer
    fclose(f);
}

