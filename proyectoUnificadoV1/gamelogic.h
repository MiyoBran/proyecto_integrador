#ifndef gamelogic_h
#define gamelogic_h

// Enumeraciones para los palos de las cartas
typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

// Enumeraciones para los valores de las cartas
typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;


// Estructura que define una carta en el juego
struct card {
    Palo palo;      // Cambia el nombre de 'Palo' a 'palo' para evitar confusión con el tipo enum
    Carta carta;    // Cambia el nombre de 'Carta' a 'carta' para evitar confusión con el tipo enum
    int puntaje;    // Mantener este campo como un entero está bien
};


// Prototipos de funciones
void initDeck(struct card Deck[], int *remaining_cards, struct card Crupier[], struct card Player[]); // Inicializa el mazo
struct card randomCard(struct card Deck[], int *remaining_cards); // Función para elegir cartas aleatorias



/*las de aca no se usan en el principal - las hace lizandro*/
void imprimircarta(struct card Card); // Imprimir la carta
void printDeck(struct card Deck[]); // Función para imprimir el mazo

#endif // gamelogic_h

// Estructura que define una carta en el juego
/// ESTO LO NECESITA ASI LIZANDRO
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
