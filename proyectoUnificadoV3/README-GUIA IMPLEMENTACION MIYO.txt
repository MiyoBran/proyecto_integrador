Como Incluir archivos Miyo en Main.c:
/*Todo lo que sigue hasta la linea 105 , debe ir, aunque se podrian cambiar nombres de variables y
para achicar tambien algunas verificaciones de error, corroborar liberacion final de memoria*/

////////////////////////Funciones propias////////////////////////
#include "config.h"     // Configuración del sistema y lectura de .env
#include "jugador.h"    // Funciones y estructuras del jugador durante la sesión
#include "scoreboard.h" // Estructuras y funciones para el manejo del ranking
#include "record.h"     // Funciones para el manejo del historial de partidas
(revisar los includes que tienen adentro, algunas cosas hay que borrar x redundantes o cambiar nombres)
/////////////////////////////////////////////////////////////////////////////////////

int main() {
    // Variables necesarias
    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Inicialización del puntero historial a NULL; la memoria se asigna dentro de recordImport()
    Jugador *historial = NULL; // La memoria se asigna dentro de recordImport


    // Asignando memoria dinámica para el arreglo de lista Ranking
    Score *scoreList = calloc(TOTAL_REGISTROS, sizeof(Score)); // Asigna memoria y la inicializa en cero
    if (scoreList == NULL) { // Verifica si la asignación fue exitosa
        printf("Error al asignar memoria para scoreList.\n");
        return 1;
    }


    // Buscando Nombre del Archivo de Ranking
    char *nombreArchivoRanking = getconfig("archivo_ranking");
    if (nombreArchivoRanking == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(scoreList); // Liberar memoria antes de salir
        return 1;
    }

    // Buscando Nombre del Archivo de Historial
    char *recordFileName = getconfig("archivo_historial");
    if (recordFileName == NULL) {
        printf("No se pudo obtener el nombre del archivo de configuración.\n");
        free(historial);
        return 1;
    }

    // Verificar cuántos registros existen en el archivo
    int cantidadRegistros = recordSize(recordFileName);  // Verificar cuántos registros existen en el archivo
    // Importar registros del archivo
    recordImport(&historial, recordFileName);

    // Opcionales , se puede no usar mi struct y comentar

    // Para poder agergar en struct Ranking/Historial 
    char nombreJugador[MAX_NOMBRE];
    Jugador jugador1; // Estructura con Nombre, Saldos, victorias y empates

    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/
    /*CODIGO QUE QUIERAN*/


    //Si no se uso la struct Jugador1, estas variables sacan la info de otro lado

    // Elejir como  hacer esto para pasar los datos de la partida
    char nombreFinal[MAX_NOMBRE];
    strcpy(nombreFinal, jugador1.nombre);  // Copiar el nombre del jugador
    int puntajeFinal = jugador1.saldo;
    int victoriasFinal = jugador1.victorias;
    int derrotasFinal = jugador1.derrotas;
    int blackjackFinal = jugador1.blackjack;

    // Crear structs para manejar el ranking e historial
    Score nuevoScore = crearScore(nombreFinal, puntajeFinal); // Convierte nombre y dinero a tipo Score
    Jugador nuevoJuego = crearHistorial(nombreFinal, puntajeFinal, victoriasFinal, derrotasFinal, blackjackFinal); // Manejo del historial

    // Actualizacion del Ranking
    rankingImport(scoreList, nombreArchivoRanking);

    // Verificar y agregar el jugador al ranking
    checkScore(scoreList, nuevoScore, nombreArchivoRanking); // Verifica y agrega el jugador

       
    // Agregar el nuevo registro al historial --> importante tiene que haber 1 struct jugador creado
    insertRecordEOF(&historial, nuevoJuego, cantidadRegistros);

    // Guardar el historial actualizado
    cantidadRegistros++;  // Incrementar el número de registros
    recordSave(historial, recordFileName, cantidadRegistros);
 

    // Liberar la memoria dinámica antes de salir
    if (scoreList != NULL) free(scoreList);
    if (historial != NULL) free(historial);

    // Revisar si es necesario liberar memoria para nombres de archivo si no son asignados dinámicamente
    if (nombreArchivoRanking != NULL) free(nombreArchivoRanking);
    if (recordFileName != NULL) free(recordFileName);


    return 0;
}


-----------------------------------------------------------------------------------------------
importante --> archivo .env  con lo siguiente:

archivo_ranking=datos_ranking.dat
archivo_historial=datos_historial.dat


-----------------------------------------------------------------------------------------------
En la carpeta:
--> crear al menos 2 archivos, cambiar_nombre.c y cambiar_nombre.h que se tienen que agregar para compilar el juego
--> en cambiar_nombre.c la funcion main que se hace, despues se cambia de nombre y se llama elejirNombreFuncion(parametros).
--> en el archivo cambiar_nombre.h se declara al menos elejirNombreFuncion(parametros); , para que este disponible.
--> Verificar siempre incompatibilidad con alguna funcion ya hecha
-----------------------------------------------------------------------

-->formato para CAMBIAR_NOMBRE.h:(se puede copiar y pegar esto, y cambiar el nombre XD);
#ifndef CAMBIAR_NOMBRE.h
#define CAMBIAR_NOMBRE.h

////////////////////////Funciones propias////////////////////////
// Alcanza con dejar lo que tengan funciones que usan , dejar todo para poder asegurarse que compila
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





