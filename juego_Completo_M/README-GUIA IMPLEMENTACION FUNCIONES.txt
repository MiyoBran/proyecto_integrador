Como agregar juego/funcionalidad 
En main.c:
--> En linea a 15 a 17 hay espacio para los include de la funcionalidad
--> En linea 26 a 28 agregar "case #" y modificar los numeros de los existentes ->menu principal
--> En el while de la linea 107 agregar ["case #": /*codigo*/ break; ] y cambiar la condicion de Salida
--> La funcion "main" del juego/funcionalidad, ahora renombrada(no puede haber 2 main) y llamada en el main puede:
    *Solo llamarse -> es como usar directamente programa ese: cualquier variable que se declare no afecta, solo tiene que poder salir.
    *Llamar con parametro &jugador1 para poder cambiar lo que se guarda en nombre y puntaje en el archivo registro / ranking
    *Con todos los parametros que tiene jugarPartida en la linea 128 -> asi se usan las mismas variables declaradas
En la carpeta:
--> crear al menos 2 archivos, cambiar_nombre.c y cambiar_nombre.h que se tienen que agregar para compilar el juego
--> en cambiar_nombre.c la funcion main que se hace, despues se cambia de nombre y se llama elejirNombreFuncion(parametros).
--> en el archivo cambiar_nombre.h se declara al menos elejirNombreFuncion(parametros); , para que este disponible.
--> Verificar siempre incompatibilidad con alguna funcion ya hecha
-----------------------------------------------------------------------------------------------
importante --> archivo .env  con lo siguiente:

archivo_ranking=datos_ranking.dat
archivo_historial=datos_historial.dat


-----------------------------------------------------------------------------------------------

-----------------------------------------------------------------------

-->formato para CAMBIAR_NOMBRE.h:(se puede copiar y pegar esto, y cambiar el nombre XD);
#ifndef CAMBIAR_NOMBRE.h
#define CAMBIAR_NOMBRE.h

////////////////////////Funciones propias////////////////////////
// Alcanza con dejar lo que tengan funciones que usan , dejar todo para poder asegurarse que compila
#define SALDO_INICIAL 1000
#include "config.h"     // donde esta la funcion para buscar configuracion en .env
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego
#include "jugador.h"    // donde estan declaradas las funciones del JUGADOR durante la SESION
#include "scoreboard.h" // donde estan declaradas las estructuras y funciones para persistencia ranking
#include "record.h"     // donde estan declaradas las funciones para la persistencia del historial de partidas
/////////////////////////////////////////////////////////////////

/*Recordatorio de structs que se usan en main
// Estructura completa para un jugador
typedef struct {
    char nombre[MAX_NOMBRE];  // Nombre del jugador
    int saldo;                // Dinero del jugador
    int victorias;            // Número de partidas ganadas
    int derrotas;             // Número de partidas perdidas
    int blackjack;              // Número de partidas empatadas
} Jugador;
// Structs-Enums para manejo de Cartas y Barajas
typedef enum {
    TREBOL, DIAMANTE, CORAZON, PICA
} Palo;

typedef enum {
    A, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, DIEZ, J, Q, K
} Carta;

typedef struct {
    Palo cardType;     // Palo de la carta (TREBOL, DIAMANTE, etc.)
    Carta cardNumber;  // Valor de la carta (A, DOS, etc.)
    int puntaje;       // Puntaje asignado a la carta
} myCard;

typedef struct {
    myCard cartas[52]; // Mazo completo de 52 cartas
} myDeck;
*/

    // Una funcionalidad/juego diferente que se elije desde el menu principal-> todas las variables son internas
    void nuevaFuncionalidad();

    // Con esta opcion se modifican los datos del jugador, que afectan ranking e historial    
    void nuevoJuego(myDeck *mazo, Jugador *jugador1);

    // si hacemos un juego similar a blackjack , y las variables disponibles en main para futura implementacion grafica
    nuevoJuego(&mazo, &jugador1,&mazoJugador, &mazoCroupier, &indiceMazo, &indiceJ1, &indiceC, apuesta, &pasoDePuntajeJugador);

#endif // CAMBIAR_NOMBRE.h
-----------------------------------------------------------------------
Ejemplo de "main" que solo cambia al jugador:
/////////////////////////////////////////////////////////////////////////////////////
// La partida completa de Blackjack
void jugarPartida(myDeck *mazo, Jugador *jugador1) {
    myDeck mazoJugador, mazoCroupier;
    bool jugarOtra = true;

    while (jugarOtra) {
        // Inicializar mazos para el jugador y el croupier
        barajarMazo(mazo);
        inicializarMazoJugador(&mazoJugador);
        inicializarMazoJugador(&mazoCroupier);

        int indiceMazo = TAMANO_MAZO - 1; // Índice de la última carta en el mazo
        int indiceJ1 = 0, indiceC = 0;    // Índices para el jugador y el croupier

        // Repartir la mano inicial
        manoInicial(mazo, &mazoJugador, &mazoCroupier, &indiceMazo, &indiceJ1, &indiceC);
        int puntajeJugador = calcularPuntaje(&mazoJugador, indiceJ1);

        // Comprobar si el jugador tiene blackjack
        bool jugadorBlackjack = puntajeJugador == 21;
        if (jugadorBlackjack) {
            printf("¡FELICITACIONES! Obtuviste BLACKJACK.\n");
        } else {
            // Turno del jugador
            bool pasoDePuntajeJugador = false;
            turnoJugador(mazo, &mazoJugador, &indiceMazo, &indiceJ1, &pasoDePuntajeJugador);

            // Actualizar puntaje final del jugador
            puntajeJugador = calcularPuntaje(&mazoJugador, indiceJ1);
            printf("\n=== Tus cartas finales ===\n");
            imprimirCartasJugador(&mazoJugador, indiceJ1);
            printf("Tu puntaje final: %d\n", puntajeJugador);
        }

        // Turno del croupier
        turnoCroupier(mazo, &mazoCroupier, &indiceMazo, &indiceC);
        int puntajeCroupier = calcularPuntaje(&mazoCroupier, indiceC);

        // Mostrar las cartas del croupier
        printf("\n=== Cartas del Croupier ===\n");
        imprimirCartasJugador(&mazoCroupier, indiceC);
        printf("Puntaje del Croupier: %d\n", puntajeCroupier);

        // Evaluar el resultado
        bool jugadorGano = evaluarResultado(puntajeJugador, puntajeCroupier);

        // Actualizar estadísticas y saldo del jugador (PENDIENTE POSIBILITAR DOBLAR APUESTA)
        actualizarEstadisticas(jugador1, jugadorGano, jugadorBlackjack);
        int apuesta = 200; // Apuesta inicial
        if (jugadorBlackjack) {
            apuesta *= 1.5; // Bonus por blackjack
        }
        modificarSaldo(jugador1, jugadorGano ? apuesta : -apuesta);

        // Mostrar el resultado
        mostrarMensajeResultado(puntajeJugador, puntajeCroupier, jugadorGano);

        // Mostrar los datos actuales del jugador
        imprimirJugador(jugador1);

        // Preguntar si el jugador quiere otra partida
        jugarOtra = preguntarJugarOtra();
    }
}
-----------------------------------------------------------------------
Ejemplo de "main" que cambia todas las variables para que esten disponibles :
// Funcion que engloba la partida completa de Blackjack:
void jugarPartida(myDeck *mazo, Jugador *jugador1, myDeck *mazoJugador, myDeck *mazoCroupier,int *indiceMazo, int *indiceJ1, int *indiceC, int apuesta, bool *pasoDePuntajeJugador) {
    /* ACLARACIÓN SOBRE PUNTEROS:
    * Esta función trabaja exclusivamente con punteros. En las llamadas internas:
    * - Si se necesita el valor contenido, usar *variable.
    * - En las funciones que aceptan punteros, pasar la variable directamente.
    */
    bool jugarOtra = true;

    while (jugarOtra) {
        // Inicializar mazos para el jugador y el croupier
        barajarMazo(mazo); // ACLARACION PUNTEROS OJO!!
        inicializarMazoJugador(mazoJugador); // ACLARACION PUNTEROS OJO!!
        inicializarMazoJugador(mazoCroupier);// ACLARACION PUNTEROS OJO!!

        // Reiniciar indices en cada partida. // ACLARACION PUNTEROS!!
        *indiceMazo = TAMANO_MAZO - 1; // Índice de la última carta en el mazo
        *indiceJ1 = 0; 
        *indiceC = 0;    // Índices para el jugador y el croupier

        // Repartir la mano inicial
        // Ojo al llamar esta funcion desde otro lado aca son punteros ya, por eso no se usa &
        manoInicial(mazo, mazoJugador, mazoCroupier, indiceMazo, indiceJ1, indiceC); // ACLARACION PUNTEROS!!


        // ACLARACION PUNTEROS: el primer argumento es un puntero, el segundo un int
        int puntajeJugador = calcularPuntaje(mazoJugador, *indiceJ1);// ACLARACION PUNTEROS!!

        // Comprobar si el jugador tiene blackjack (21 en la ronda inicial)
        bool jugadorBlackjack = puntajeJugador == 21;
        if (jugadorBlackjack) {
            // Importante --> LO IMPORTANTE ES QUE NOS SALTAMOS EL TURNO DEL JUGADOR
            printf("¡FELICITACIONES! Obtuviste BLACKJACK.\n");
        } else {
            // Turno del jugador

            // Este booleando Nos indica si la partida termina de manera forzada
            *pasoDePuntajeJugador = false;
            turnoJugador(mazo, mazoJugador, indiceMazo, indiceJ1, pasoDePuntajeJugador);// ACLARACION PUNTEROS!!

            // Actualizar puntaje final del jugador
            puntajeJugador = calcularPuntaje(mazoJugador, *indiceJ1); // ACLARACION PUNTEROS!!
            printf("\n=== Tus cartas finales ===\n");
            imprimirCartasJugador(mazoJugador, *indiceJ1); // ACLARACION PUNTEROS: OJO !!
            printf("Tu puntaje final: %d\n", puntajeJugador);
        }

        // Turno del croupier - > ACLARACION PUNTEROS: OJO
        turnoCroupier(mazo, mazoCroupier, indiceMazo, indiceC);
        int puntajeCroupier = calcularPuntaje(mazoCroupier, *indiceC);

        // Mostrar las cartas del croupier
        printf("\n=== Cartas del Croupier ===\n");
        imprimirCartasJugador(mazoCroupier, *indiceC);
        printf("Puntaje del Croupier: %d\n", puntajeCroupier);

        // Evaluar el resultado
        bool jugadorGano = evaluarResultado(puntajeJugador, puntajeCroupier); // ACLARACION PUNTEROS: OJO !!

        // Actualizar estadísticas y saldo del jugador (PENDIENTE POSIBILITAR DOBLAR APUESTA)
        actualizarEstadisticas(jugador1, jugadorGano, jugadorBlackjack); // ACLARACION PUNTEROS: OJO !!

        int ganancia = apuesta;
        if (jugadorBlackjack) {
            ganancia *= 1.5;  // Bonus por blackjack
        }
        //Modifica jugador1->saldo: Si jugadorGano == true paga ganancia , sino - apuesta
        modificarSaldo(jugador1, jugadorGano ? ganancia : -apuesta); // ACLARACION PUNTEROS: OJO !!

        // Mostrar el resultado
        mostrarMensajeResultado(puntajeJugador, puntajeCroupier, jugadorGano); // ACLARACION PUNTEROS: OJO !!

        // Mostrar los datos actuales del jugador
        imprimirJugador(jugador1); // ACLARACION PUNTEROS: OJO !!

        // Preguntar si el jugador quiere otra partida (true -> puede)
        if (puedeSeguirJugando(jugador1, apuesta))
        {
            jugarOtra = preguntarJugarOtra();
        }
        else
        {
            jugarOtra = false;
        }

            
    }
}
-----------------------------------------------------------------------


*-* ALGUNAS FUNCIONES UTILES *-*
// Si quiero saber un puntaje:
int puntajeCroupier = calcularPuntaje(&mazoCroupier, indiceC);
---> Cuando las variables que estamos usando ya son punteros, es al revez
int puntajeJugador = calcularPuntaje(mazoJugador, *indiceJ1);

    
// Evaluar el resultado
bool jugadorGano = evaluarResultado(puntajeJugador, puntajeCroupier);

// Llamar la mano inicial desde la funcion donde se declaran las variables:
manoInicial(&mazo, &mazoJugador, &mazoCroupier, &indiceMazo, &indiceJ1, &indiceC); // ACLARACION PUNTEROS!!

--------- MAZO.H ->  CARTAS Y MAZOS
+++Importante+++ 
-> Recibe 4 punteros ,"copia" la carta del mazo al mazo del jugador, y cambia los indices
pedir1carta(&mazo, &jugador, &indiceMazo, &indiceJugador);
++++++++++++++++ 

// Inicializar MAZO y barajar --> inicializar mazo "llena" , la cantidad de cartas que tiene depende de cuantos enum hay en 
inicializarMazo(&mazo);
barajarMazo(&mazo);

// En cambio esta , inicializa un mazo con MAX_CARTAS_JUGADOR mycards ---> con 0,0,0 (ojo As de Trebol con puntaje 0 = error)
void inicializarMazoJugador(myDeck *jugador);


// inicializarJugadorGlobal --> Nos inicia un struct con nombre  y saldo inicial para usar durante toda la sesion

// imprimirCartasJugador(&mazo, indiceC); -> imprime el mazo hasta ese punto





