#ifndef gamelogic_h
#define gamelogic_h
#include <stdbool.h>



// Enumeraciones para los palos de las cartas
typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

// Enum para Identificar cada carta 
typedef enum {
    A , DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;

#define decks 1

typedef struct  {
    Palo cardType;
    Carta cardNumber;
    int puntaje;            
}   myDeck;
// Estructura que define una carta en el juego


// Prototipos de funciones
void initDeck(myDeck Deck[], int *remaining_cards); // Inicializa el mazo
void shuffleDeck(myDeck Deck[], int n);
int calculatePoints(myDeck Deck[], int amountCards);
bool defineWinner(int playerPoints, int crupierPoints);
void getCard(int countCard, int *dealtCardsDeck, int *dealtCardsTarget, myDeck Deck[], myDeck target[]);
void crupierLogic(myDeck Deck[], int *dealtCards, myDeck Crupier[], int *dealtCardsCrupier);
bool blackJack(myDeck Player[]);

#endif // gamelogic_h

