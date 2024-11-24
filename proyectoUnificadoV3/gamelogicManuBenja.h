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

extern int MAX_CARDS_DISPLAYED;
//Some value searched in .env

// Prototipos de funciones
void initDeck(myCard Deck[], int *remaining_cards); // Inicializa el mazo
myCard randomCard(myCard Deck[], int *remaining_cards); // Función para elegir cartas aleatorias
void shuffleDeck(myCard Deck[], int n);     // Mezcla un mazo con algorito fisher-yates
int calculatePoints(myCard Deck[], int amountCards);    //Calcula los puntos de un mazo
bool defineWinner(int playerPoints, int crupierPoints); //Tomando dos mazo define quien gana
void getCard(int countCard, int *dealtCardsDeck, int *dealtCardsTarget, myCard Deck[], myCard **target);    //Toma un mazo y le introduce una carta al final desde una pila
void crupierLogic(myCard Deck[], int *dealtCards, myCard **Crupier, int *dealtCardsCrupier);    //Funcion encargada de decidir si el crupier toma cartas o no
bool blackJack(myCard Player[]);        //Verifica la condicion de BlackJack solo en la primera ronda



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
//void getCard(myCard *deck, int *amountCards);
//int calculatePoints(myCard *deck, int *amountCards);
bool compareScores(int puntajeJugador, int puntajeCroupier);
//Checks if player got a blackjack win
void allowBlackjackWin(int playerPoints, int amountCardsPlayer, gameState *currentGame);
//Checks whether player or crupier went above 21
bool playerAbove21(int points);
//Starts a new round, might need to compress the parameters a bit
void startRound(int *amountCardsPlayer, int *amountCardsCrupier, int *remainingCards, int *dealtCards, int *playerPoints, int *crupierPoints, int *bet, myCard **playerDeck, myCard **crupierDeck, myCard Deck[], gameState *currentGame);

/////////////////////////////////////////////////////////////////////////////////////