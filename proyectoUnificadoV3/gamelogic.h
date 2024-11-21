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

typedef struct {
    bool playerWin;                                                      //Variable to check if player won
    bool allowMoneyUpdate;                                               //Variable that prevents constant money updates
    bool playerBlackjack;                                                //Variable that checks if player won by blackjack
    bool roundEnd;                                                       //Variable to check if round ended
}  gameState;


typedef struct  {
    Palo cardType;
    Carta cardNumber;
    int puntaje;            
}   myCard;
// Estructura que define una carta en el juego


// Prototipos de funciones
void initDeck(myCard Deck[], int *remaining_cards, myCard Crupier[], myCard Player[]); // Inicializa el mazo
myCard randomCard(myCard Deck[], int *remaining_cards); // Función para elegir cartas aleatorias



/*las de aca no se usan en el principal - las hace Miyo*/
//void imprimircarta(myCard Card); // Imprimir la carta
//void printDeck(myCard Deck[]); // Función para imprimir el mazo

                                                        //Ambas funciones movidas a test_gamelogic.c//


#endif // gamelogic_h

// Estructura que define una carta en el juego
/// ESTO LO NECESITA ASI Miyo
// typedef struct  {
//     int cardType;
//     int cardNumber;
// }   myCard;
//Protoype of a struct containing the specifics of a card.


/*Donde decia valor - debe decir carta y el AS -> A, para usar el mismo enum*/
// enum valor{
//     AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
// };

/*Donde decia figura - debe decir palo y arreglar nombres , para usar el mismo enum*/
// enum figura{
//     Pica,Corazon,Diamante,Trebol
// };


// ACA hay un cambio respecto de la original

// struct card{
//     int Palo;
//     int Carta;
//     int puntaje;
// };



/////////////////////////////////////////////////////////////////////////////////////
int getPlayerMoney(int playerMoney, int bet, bool playerWin);
void getCard(myCard *deck, int *amountCards);
int calculatePoints(myCard *deck, int *amountCards);
bool compareScores(int puntajeJugador, int puntajeCroupier);
void allowBlackjackWin(int playerPoints, int amountCardsPlayer, gameState *currentGame);
//Checks if player got a blackjack win
bool playerAbove21(int points, gameState *currentGame);
//Checks whether player or dealer went above 21
void startRound(int *amountCardsPlayer, int *amountCardsDealer, int *playerPoints, int *dealerPoints, int *bet, myCard playerDeck[MAX_CARDS_DISPLAYED], myCard dealerDeck[MAX_CARDS_DISPLAYED], gameState *currentGame);
//Starts a new round, might need to compress the parameters a bit
/////////////////////////////////////////////////////////////////////////////////////