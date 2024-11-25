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


    //Si no se uso la struct Jugador1, estas 2 variables sacan la info de otro lado

    // Elejir como  hacer esto para pasar los datos de la partida
    char nombreFinal[MAX_NOMBRE];
    strcpy(nombreFinal, jugador1.nombre);  // Copiar el nombre del jugador
    int puntajeFInal = jugador1.saldo;
    int victoriasFinal = jugador1.victorias;
    int derrotasFinal = jugador1.derrotas;
    int blackjackFinal = jugador1.blackjack;


    // Crear structs para manejar el ranking e historial
    Score nuevoJugador = crearScore(nombreFinal, puntajeFInal); // Convierte nombre y dinero a tipo Score
    Jugador nuevoJuego = crearHistorial(nombreFinal, puntajeFInal, victoriasFinal, derrotasFinal, blackjackFinal); // Manejo del historial



    // Actualizacion del Ranking
    rankingImport(scoreList, nombreArchivoRanking);

    // Verificar y agregar el jugador al ranking
    checkScore(scoreList, nuevoJugador, nombreArchivoRanking); // Verifica y agrega el jugador


    // Mostrar el ranking actualizado
    printf("\n=================== 🏆RANKING ACTUALIZADO🏆 ===================\n");
    printf("----------------------------------------------------------\n");

    showRanking(scoreList, nombreArchivoRanking);

    // Línea decorativa final
    printf("==========================================================\n");

    // Mensaje de despedida
    printf("✨¡Hasta pronto!✨🃏Gracias por jugar🃏.  \n");
    printf("==========================================================\n");

        
    // Agregar el nuevo registro al historial --> importante tiene que haber 1 struct jugador creado
    insertRecordEOF(&historial, nuevoJuego, cantidadRegistros);

    // Guardar el historial actualizado
    cantidadRegistros++;  // Incrementar el número de registros
    recordSave(historial, recordFileName, cantidadRegistros);

    // Limpiar el buffer de entrada en caso de que haya más caracteres sobrantes
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Lee y descarta el resto de la línea
    printf("Presione una tecla cualquiera para salir...\n");
    getchar(); // Espera una tecla

    // Mostrar el Historial actualizado
    printf("\n=================== 🎮HISTORIAL ACTUALIZADO🎮 ===================\n");
    printf("----------------------------------------------------------\n");

    showRecord(historial, cantidadRegistros);  // Llamamos a showRecord para imprimir el historial

    // Línea decorativa final
    printf("==========================================================\n");

    // Mensaje de despedida
    printf("🎮✨🚀🏆🎲🥳🌟🔥💡🎵🎉🃏\n");
    printf("==========================================================\n");
 
 

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
// La partida completa de Blackjack (el que estaba antes - ahora en el otro git , creo)
void jugarPartida(myDeck *mazo, Jugador *jugador1) {
    myDeck mazoJugador, mazoCroupier;
    bool jugarOtra = true;

    while (jugarOtra) {
        /*CODIGO DEL JUEGO*/
        /*CODIGO DEL JUEGO*/
        /*CODIGO DEL JUEGO*/
        /*CODIGO DEL JUEGO*/
    }
}
-----------------------------------------------------------------------
Ejemplo de "main" que cambia todas las variables para que esten disponibles :
// Funcion que engloba la partida completa de Blackjack (el actual en juego_completo_m)
void jugarPartida(myDeck *mazo, Jugador *jugador1, myDeck *mazoJugador, myDeck *mazoCroupier,int *indiceMazo, int *indiceJ1, int *indiceC, int apuesta, bool *pasoDePuntajeJugador) {
    /* ACLARACIÓN SOBRE PUNTEROS:
    * Esta función trabaja exclusivamente con punteros. En las llamadas internas:
    * - Si se necesita el valor contenido, usar *variable.
    * - En las funciones que aceptan punteros, pasar la variable directamente.
    */
    bool jugarOtra = true;

    while (jugarOtra) {
        /*CODIGO DEL JUEGO*/
        /*CODIGO DEL JUEGO*/
        /*CODIGO DEL JUEGO*/
        /*CODIGO DEL JUEGO*/
    }
}
-----------------------------------------------------------------------


*-* ALGUNAS FUNCIONES UTILES *-*

