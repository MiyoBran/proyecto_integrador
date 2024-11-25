#ifndef gamelogic_h
#define gamelogic_h

#include <stdbool.h>

// Enumeraciones para los palos de las cartas
typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

// Enumeraciones para los valores de las cartas
typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;

//Estructura que define el estado del juego
typedef struct {
    bool playerWin;                        //Variable que revisa si el jugador gano
    bool allowMoneyUpdate;                 //Variable que previene la actualizacion constante de dinero
    bool playerBlackjack;                  //Variable que revisa si el jugador obtuvo un blackjack
    bool roundEnd;                         //Variable que revisa si la ronda termino
}  gameState;

// Estructura que define una carta en el juego
typedef struct  {
    Palo cardType;
    Carta cardNumber;
    int puntaje;            
}   myCard;

//Maxima cantidad de cartas que se pueden mostrar, valor buscado en archivo .env
extern int MAX_CARDS_DISPLAYED;

// Inicializa el mazo
void initDeck(myCard Deck[], int *remaining_cards);
// Mezcla un mazo con algorito fisher-yates
void shuffleDeck(myCard Deck[], int n);
//Calcula los puntos de un mazo
int calculatePoints(myCard Deck[], int amountCards);
//Toma un mazo y le introduce una carta al final desde una pila
void getCard(int countCard, int *dealtCardsDeck, int *dealtCardsTarget, myCard Deck[], myCard **target);
//Funcion encargada de decidir si el crupier toma cartas o no
void crupierLogic(myCard Deck[], int *dealtCards, myCard **Crupier, int *dealtCardsCrupier); 
//Actualiza la cantidad de dinero que le corresponde al jugador
int getPlayerMoney(int playerMoney, int bet, bool playerWin);
//Compara puntaje entre el jugador y el crupier
bool compareScores(int puntajeJugador, int puntajeCroupier);
//Verifica la condicion de BlackJack solo en la primera ronda
void allowBlackjackWin(int playerPoints, int amountCardsPlayer, gameState *currentGame);
//Verifica que el jugador/crupier no se pase de 21 puntos
bool playerAbove21(int points);
//Empieza una nueva ronda reiniciando los valores de las variables a su estado inicial
void startRound(int *amountCardsPlayer, int *amountCardsCrupier, int *remainingCards, int *dealtCards, int *playerPoints, int *crupierPoints, int *bet, myCard **playerDeck, myCard **crupierDeck, myCard Deck[], gameState *currentGame);

#endif // gamelogic_h
