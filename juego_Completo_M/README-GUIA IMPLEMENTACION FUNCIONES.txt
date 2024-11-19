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





