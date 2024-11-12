#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h> /// para caracteres anchos / emoticones?
#include "files2.h"
#include "gamelogic.h"
#include "graphics_storage.h"


#define decks 1


void initDeck(struct card Deck[],int *remaining_cards, struct card Crupier[], struct card Player[]){
    int index = 0;
    for (int i = 0; i < (4*decks); i++)
    {
        for (int j = 0; j < (13*decks); j++)
        {
            Deck[index].palo = i;
            Deck[index].carta = j;
            index++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        Crupier[i].palo = -1;
        Player[i].palo = -1;
    }
    (*remaining_cards) = 52*decks;
}

/*EN VERDAD ESTO ES PARA PRUEBAS???*/
void imprimircarta(struct card Card) {
    setlocale(LC_CTYPE, "en_US.UTF-8");
    wchar_t *CORAZON = L"\u2665";  
    wchar_t *PICA = L"\u2660";     
    wchar_t *TREBOL = L"\u2663";   
    wchar_t *DIAMANTE = L"\u2666"; 

    // Imprimir el valor de la carta
    switch (Card.carta) {
        case A:
            printf("A");
            break;
        case J:
            printf("J");
            break;
        case Q:
            printf("Q");
            break;
        case K:
            printf("K");
            break;
        default:
            printf("%d", Card.carta + 1); // Imprime el valor de cartas numéricas
            break;
    }

    // Imprimir el palo de la carta // cambie el switch por el if porque habia problemas con el enum nuevo
    if (Card.palo == TREBOL) {
        printf("%ls\n", TREBOL);
    } else if (Card.palo == DIAMANTE) {
        printf("%ls\n", DIAMANTE);
    } else if (Card.palo == CORAZON) {
        printf("%ls\n", CORAZON);
    } else if (Card.palo == PICA) {
        printf("%ls\n", PICA);
    }
}

/*PARA ELEGIR UNA CARTA ALEATORIA DEL MAZO - funcion de tipo card*/
struct card randomCard(struct card Deck[], int *remaining_cards){
    struct card Card;
    int randomIndex = rand() % *remaining_cards;
    Card = Deck[randomIndex];
    Deck[randomIndex] = Deck[(*remaining_cards)-1];
    (*remaining_cards)--;
    return Card;
};

/*FUNCION DE PRUEBA PARA VER EL MAZO*/
void printDeck(struct card Deck[]){
    for (int i = 0; i < (52*decks); i++)
    {
        imprimircarta(Deck[i]);
    }
}

/*VER SI HAY QUE CAMBIARLE EL NOMBRE A LA FUNCION ESTA*/
int gamelogic(){
    srand(time(NULL));
    struct card Deck[52*decks], Crupier[5], Player[5];
    int remaining_cards;
    initDeck(Deck,&remaining_cards,Crupier,Player);
}