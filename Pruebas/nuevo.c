#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeraciones para los palos de las cartas
typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

// Enumeración para identificar cada carta
typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;

// Estructura que define una carta en el mazo
typedef struct {
    Palo cardType;
    Carta cardNumber;
    int puntaje; // Puntaje asociado a la carta (por ejemplo, valor de la carta)
} myDeck;

// Estructura para los jugadores
typedef struct {
    int continuar;
    int valor;
    int offset;
    myDeck mano[6];
} jugador;

myDeck *crear_baraja(int n);
void barajar(myDeck *baraja, int num_cartas);
int juego(myDeck *baraja, int *offset, int m);
void evaluar_jugador(jugador *j);
int evaluar_carta(myDeck c);
void debug(myDeck *p, int l);
void imprimir_carta(myDeck c);
void asignar_puntaje(myDeck *carta);

int main() {
    myDeck *baraja;
    int offset = 0;
    printf("Juego de BlackJack\n");
    printf("Creando baraja...\n");
    baraja = crear_baraja(2);
    printf("Baraja:\n");
    // Aquí se podría imprimir las cartas
    barajar(baraja, 52);  // Revolver la baraja
    juego(baraja, &offset, 6); // La casa juega contra 6 Jugadores Solo una ronda
    free(baraja);
}

myDeck *crear_baraja(int n) {
    int i = 0, j = 0, offset = 0;
    myDeck *cartas = malloc(sizeof(myDeck) * 52 * n); // Reserva memoria para n barajas
    while(i < n) {
        for(j = 0; j < 4; j++) {
            for(int k = 0; k < 13; k++) {
                cartas[offset].cardType = j;
                cartas[offset].cardNumber = k;
                asignar_puntaje(&cartas[offset]); // Asignar puntaje de la carta
                offset++;
            }
        }
        i++;
    }
    return cartas;
}

void asignar_puntaje(myDeck *carta) {
    switch(carta->cardNumber) {
        case A:
            carta->puntaje = 11;
            break;
        case J:
        case Q:
        case K:
        case DIEZ:
            carta->puntaje = 10;
            break;
        default:
            carta->puntaje = carta->cardNumber + 1;
            break;
    }
}

void barajar(myDeck *baraja, int num_cartas) {
    myDeck temp;
    int r, i = 0;
    while(i < num_cartas) {
        r = rand() % num_cartas;
        // Intercambia las cartas baraja[i] y baraja[r]
        temp = baraja[i];
        baraja[i] = baraja[r];
        baraja[r] = temp;
        i++;
    }
}

int juego(myDeck *baraja, int *offset, int m) {
    int len = 52 * 2, i = *offset, j = 0, k = 0, n = m + 1;    
    jugador **jugadores = malloc(sizeof(jugador *) * n);  // Reserva memoria para los jugadores

    // Inicialización de jugadores
    while(k < n) {
        jugadores[k] = malloc(sizeof(jugador));  // Reserva memoria para cada jugador
        k++;
    }

    // Asignar dos cartas iniciales a cada jugador
    while(j < 2) {
        k = 0;
        while(k < n) {
            jugadores[k]->mano[j] = baraja[i];
            jugadores[k]->offset++;
            i++;
            k++;
        }
        j++;
    }

    // Imprimir la mano de cada jugador
    j = 0;
    while(j < n) {
        printf("Jugador: %i\n", j);
        imprimir_carta(jugadores[j]->mano[0]);
        printf("Valor actual: %i\n", jugadores[j]->valor);
        j++;
    }

    // Liberar memoria de los jugadores
    for(k = 0; k < n; k++) {
        free(jugadores[k]);
    }
    free(jugadores);

    return 1;
}

void imprimir_carta(myDeck c) {
    char *palos[] = {"TREBOL", "DIAMANTE", "CORAZON", "PICA"};
    char *cartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    printf("Carta: %s de %s\n", cartas[c.cardNumber], palos[c.cardType]);
}

void evaluar_jugador(jugador *j) {
    int i = 0;
    j->valor = 0;
    while(i < j->offset) {
        j->valor += evaluar_carta(j->mano[i]);
        i++;
    }
}

int evaluar_carta(myDeck c) {
    return c.puntaje;
}

void debug(myDeck *p, int l) {
    int i = 0;
    while(i < l) {
        imprimir_carta(p[i]);
        i++;
    }
}
