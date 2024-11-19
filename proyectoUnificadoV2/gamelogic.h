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
    bool roundEnd;                                                       //Variable to check if round ended
}  gameState;


typedef struct  {
    Palo cardType;
    Carta cardNumber;
    int puntaje;            
}   myDeck;
// Estructura que define una carta en el juego


// Prototipos de funciones
void initDeck(myDeck Deck[], int *remaining_cards, myDeck Crupier[], myDeck Player[]); // Inicializa el mazo
myDeck randomCard(myDeck Deck[], int *remaining_cards); // Función para elegir cartas aleatorias



/*las de aca no se usan en el principal - las hace Miyo*/
//void imprimircarta(myDeck Card); // Imprimir la carta
//void printDeck(myDeck Deck[]); // Función para imprimir el mazo

                                                        //Ambas funciones movidas a test_gamelogic.c//


#endif // gamelogic_h

// Estructura que define una carta en el juego
/// ESTO LO NECESITA ASI Miyo
// typedef struct  {
//     int cardType;
//     int cardNumber;
// }   myDeck;
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
int getPlayerMoney(int bet, bool *playerWin);
void getCard(myDeck *deck, int *amountCards);
int calculatePoints(myDeck *deck, int *amountCards);
bool compareScores(int puntajeJugador, int puntajeCroupier);
/////////////////////////////////////////////////////////////////////////////////////