#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Para manejar valores booleanos

////////////////////////Funciones propias////////////////////////
#include "jugador.h"    // donde estan declaradas las funciones del JUGADOR durante la SESION
#include "mazo.h"       // donde estan declaradas las funciones y structs del mazo y las cartas
#include "logica.h"     // donde estan declaradas las funciones de los turnos de juego

/////////////////////////////////////////////////////////////////////////////////////
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

// Calcula puntaje con un myDeck y un indice que le indica hasta que carta contabilizar - ajusta valor del as
int calcularPuntaje(const myDeck *jugador, int numCartas) {
    int puntaje = 0, ases = 0;

    // Recorrer todas las cartas del jugador para calcular el puntaje inicial
    for (int i = 0; i < numCartas; i++) {
        int valor = jugador->cartas[i].puntaje;

        if (valor == 1) {
            ases++;  // Contar cuántos ases hay en la mano
            puntaje += 11;  // Asume inicialmente que el As vale 11 puntos
        } else if (valor >= 10) {
            puntaje += 10;  // Las cartas J, Q, K y 10 valen 10 puntos cada una
        } else {
            puntaje += valor;  // Para las cartas de valor entre 2 y 9, sumar su valor directamente
        }
    }

    // Si el puntaje total excede 21, ajustar los ases de 11 a 1 según sea necesario
    while (puntaje > 21 && ases > 0) {
        puntaje -= 10;  // Restar 10 puntos por cada As ajustado
        ases--;  // Reducir el conteo de ases pendientes de ajuste
    }

    // Retornar el puntaje final después de los ajustes
    return puntaje;
}
// Función para comparar los puntajes del jugador y el croupier
// Devuelve 'true' si el jugador gana, 'false' en caso contrario (cuando el jugador pierde o empata)
bool evaluarResultado(int puntajeJugador, int puntajeCroupier) {
    
    // Si el puntaje del jugador excede 21, el jugador ha perdido
    if (puntajeJugador > 21) {
        return false; // El jugador se pasa de 21
    }
    
    // Si el croupier se pasa de 21, o el puntaje del jugador es mayor que el del croupier, el jugador gana
    else if (puntajeCroupier > 21 || puntajeJugador > puntajeCroupier) {
        return true;  // El jugador gana
    }
    
    // Si el puntaje del jugador es igual o menor que el del croupier, el jugador pierde o empata
    else {
        return false; // Empate o el croupier gana
    }
}

// Muestra mensaje segun "como" gano o perdio
void mostrarMensajeResultado(int puntajeJugador, int puntajeCroupier, bool jugadorGano) {
printf("\n=================== RESULTADOS DE LA PARTIDA ===================\n");
printf("Puntaje del Jugador: %d\n", puntajeJugador);
printf("Puntaje del Croupier: %d\n", puntajeCroupier);
printf("---------------------------------------------------------------\n");

if (puntajeJugador > 21) {
    printf("Resultado: Jugador se pasa. Pierde.\n");
} else if (puntajeCroupier > 21) {
    printf("Resultado: Croupier se pasa. ¡Jugador gana!\n");
} else if (jugadorGano) {
    printf("Resultado: ¡Jugador gana!\n");
} else if (puntajeJugador == puntajeCroupier) {
    printf("Resultado: Empate. Pierde por ventaja del Croupier.\n");
} else {
    printf("Resultado: Croupier gana.\n");
}

printf("===============================================================\n");
}

// Turno Jugador
// Turno Jugador: Lógica sin impresión
// Pregunta si desea otra carta
bool preguntarAccionJugador(int puntaje) {
    printf("\n=== ¿Deseas otra carta? ===\n");
    printf("Tu puntaje actual es: %d\n", puntaje);
    printf("1. Sí\n");
    printf("0. No\n");
    printf("Selecciona una opción: ");

    int respuesta;

    // Validar entrada del usuario
    while (scanf("%d", &respuesta) != 1 || (respuesta != 0 && respuesta != 1)) {
        // Limpiar el buffer de entrada en caso de error
        while (getchar() != '\n'); // Limpiar el buffer
        printf("Entrada no válida. Por favor, selecciona 1 para Sí o 0 para No: ");
    }

    return respuesta == 1; // Devuelve true si la respuesta es 1, de lo contrario false
}

// Función que verifica si el jugador se pasa de 21 puntos
// Retorna 'true' si el puntaje del jugador excede 21, 'false' en caso contrario
bool verificarPasoDePuntaje(myDeck *jugador, int numCartas) {
    // Calcular el puntaje total del jugador con las cartas actuales
    int puntaje = calcularPuntaje(jugador, numCartas);
    
    // Si el puntaje es mayor que 21, el jugador se pasa de puntaje
    return (puntaje > 21); // Retorna true si se pasa de 21, de lo contrario false
}

// Función que realiza la acción del jugador (pedir otra carta o no) y decide si continuar o terminar el turno
// Retorna 'true' si el turno debe continuar (si el jugador pide otra carta y hay cartas disponibles),
// y 'false' si el turno termina (por falta de cartas o si el jugador decide no pedir más cartas)
bool realizarAccionJugador(bool deseaOtraCarta, myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador) {
    // Si el jugador desea otra carta
    if (deseaOtraCarta) {
        // Intenta pedir una carta del mazo. Si no hay cartas disponibles, termina el turno
        if (!pedir1carta(mazo, jugador, indiceMazo, indiceJugador)) {
            return false; // Fin del turno por falta de cartas
        }
    } else {  // Si el jugador no quiere más cartas
        return false; // Fin del turno por decisión del jugador
    }
    
    // Si el jugador desea continuar (es decir, pidió una carta y la obtuvo)
    return true; // Continuar el turno
}

// Esta función orquesta el turno del jugador, manejando las acciones durante su turno (pedir carta, plantarse, etc.)
// Utiliza varias funciones auxiliares para calcular el puntaje, mostrar cartas, y tomar decisiones del jugador.
// El turno termina cuando el jugador se pasa de 21, alcanza 21 puntos, o decide plantarse.
void turnoJugador(myDeck *mazo, myDeck *jugador, int *indiceMazo, int *indiceJugador, bool *pasoDePuntaje) {
    // printf("****** INICIO DEL TURNO DEL JUGADOR ******\n"); // Depuración: Inicio del turno

    *pasoDePuntaje = false;  // Inicializar el indicador de si el jugador se pasa de 21
    int puntaje;  // Variable para almacenar el puntaje actual del jugador

    while (true) {  // El ciclo continuará hasta que el turno termine (por cualquier condición de término)
        puntaje = calcularPuntaje(jugador, *indiceJugador);  // Calcular el puntaje actual del jugador

        // Mostrar las cartas del jugador si ya tiene al menos 2 cartas
        if (*indiceJugador > 2) {
            printf("\n---- TURNO DEL JUGADOR ----\n"); // Depuracion
            printf("Tus cartas:\n");
            imprimirCartasJugador(jugador, *indiceJugador);  // Mostrar las cartas del jugador
            printf("--------------------------\n");
        }
        
        // Verificar si el jugador ha excedido los 21 puntos
        if (puntaje > 21) {
            *pasoDePuntaje = true;  // Marcar que el jugador se pasó de 21
            printf("Te pasaste de 21. Fin de la partida.\n");
            break;  // Terminar el turno si el jugador se pasa de 21
        }

        // Verificar si el jugador ha alcanzado exactamente 21 puntos
        if (puntaje == 21) {
            printf("¡Felicidades! Alcanzaste 21. Fin del turno.\n");
            break;  // Terminar el turno si el jugador alcanza 21 puntos
        }

        // Preguntar al jugador si desea otra carta
        bool deseaOtraCarta = preguntarAccionJugador(puntaje);  // Solicitar decisión del jugador

        // Realizar la acción según la respuesta del jugador
        if (!realizarAccionJugador(deseaOtraCarta, mazo, jugador, indiceMazo, indiceJugador)) {
            // El jugador decide plantarse o no hay más cartas disponibles
            printf("Te has plantado con un puntaje de %d.\n", puntaje);
            break;  // Terminar el turno si el jugador se planta o no hay cartas
        }
    }
    printf("=== FIN DE LA RONDA ===\n");  // Indicar el fin de la ronda // Depuracion

}

// Esta funcion se llama antes de Turno jugador y Turno Croupier
// Esta función maneja el reparto inicial de cartas tanto al jugador como al croupier
// Se llama antes de los turnos del jugador y del croupier para establecer el estado inicial de la ronda.
void manoInicial(myDeck *mazo, myDeck *jugador, myDeck *croupier, int *indiceMazo, int *indiceJugador, int *indiceCroupier) {
    printf("=== INICIO DE LA RONDA ===\n");  // Indicar el inicio de la ronda

    // Repartir una carta al croupier
    if (pedir1carta(mazo, croupier, indiceMazo, indiceCroupier)) {
        printf("\nCarta del croupier:\n");
        imprimirCartasJugador(croupier, *indiceCroupier);  // Mostrar la carta del croupier
        int puntajeCroupier = calcularPuntaje(croupier, *indiceCroupier);  // Calcular puntaje del croupier
        printf("Puntaje del croupier: %d\n", puntajeCroupier);  // Mostrar puntaje del croupier
    } else {
        printf("No hay suficientes cartas para repartir al croupier.\n");  // Verificar si hay cartas disponibles para el croupier
        return;  // Salir de la función si no hay suficientes cartas
    }

    // Repartir dos cartas al jugador
    // Primero se reparte una carta al jugador
    if (!pedir1carta(mazo, jugador, indiceMazo, indiceJugador)) {
        printf("No hay suficientes cartas para repartir al jugador.\n");  // Verificar si hay cartas suficientes
        return;  // Salir de la función si no hay suficientes cartas
    }
    
    // Repartir la segunda carta al jugador
    if (!pedir1carta(mazo, jugador, indiceMazo, indiceJugador)) {
        printf("No hay suficientes cartas para repartir al jugador.\n");  // Verificar nuevamente si hay cartas suficientes
        return;  // Salir de la función si no hay suficientes cartas
    }

    // Mostrar las cartas iniciales del jugador
    printf("\nTus cartas iniciales:\n");
    imprimirCartasJugador(jugador, *indiceJugador);  // Mostrar cartas del jugador
    int puntajeJugador = calcularPuntaje(jugador, *indiceJugador);  // Calcular puntaje del jugador
    printf("Tu puntaje actual es: %d\n", puntajeJugador);  // Mostrar puntaje del jugador

    // printf("\n=== FIN DE LA RONDA INICIAL ===\n");  // DEPURACION: Indicar el fin de la ronda inicial
}


// Turno Croupier -> inicio
// Determina si el croupier debe pedir otra carta basado en su puntaje actual
// La regla estándar del Blackjack establece que el croupier debe pedir otra carta si su puntaje es menor a 17.
bool debePedirCarta(int puntajeCroupier) {
    return puntajeCroupier < 17;  // Si el puntaje del croupier es menor a 17, debe pedir una carta
}
// Gestiona el turno del Croupier, determinando si debe pedir una carta o plantarse automáticamente según las reglas del Blackjack.
void turnoCroupier(myDeck *mazo, myDeck *croupier, int *indiceMazo, int *indiceCroupier) {

    while (true) {
        // Calcular el puntaje actual del Croupier
        int puntajeCroupier = calcularPuntaje(croupier, *indiceCroupier);

        // Si el puntaje del Croupier es 17 o más, se planta y termina su turno
        if (!debePedirCarta(puntajeCroupier)) {
            // El Croupier se planta si su puntaje es 17 o más
            break;
        }

        // Pedir una nueva carta para el Croupier
        if (!pedir1carta(mazo, croupier, indiceMazo, indiceCroupier)) {
            // Si no hay más cartas en el mazo, el turno del Croupier termina
            printf("No quedan cartas en el mazo. Fin del turno del Croupier.\n");
            break;
        }

        // Recalcular el puntaje del Croupier después de añadir la nueva carta
        puntajeCroupier = calcularPuntaje(croupier, *indiceCroupier);

        // Si el Croupier se pasa de 21, termina su turno
        if (puntajeCroupier > 21) {
            // El Croupier se pasa de 21 y termina el turno
            break;
        }
    }
}

//Funcion alternativa a los if para validar si se puede seguir o no
bool puedeSeguirJugando(Jugador *jugador, int apuesta)
{
    if (jugador->saldo >= apuesta)
    {
        return true;
    }
    printf("Lo siento, no tienes suficiente saldo para jugar otra partida :(\n");
    return false;
}