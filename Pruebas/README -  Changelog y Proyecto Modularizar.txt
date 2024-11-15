
*Proyecto en GitHub.com/MiyoBran/proyecto_integrador.git 
*Proyecto en Drive https://drive.google.com/drive/folders/1eUS_w_vo_eg3GkFpGmb9hGzu-Kx6sQyM?usp=drive_link

+++++++++++++***************+++++++++++++++**************++++++++++++*************
Verificar si tienen o no que estar en cada archivo.c que tengan
// Includes Propios del proyecto
#include "config.h" // para la funcion independiente que busca valor de configuracion en el .env
#include "scoreboard.h" // donde estan declaradas las funciones comunes a los scoreboards
#include "gamelogic.h" // las funciones declaradas en la logica
#include "graphics_storage.h" // las funciones declaradas para la parte grafica - UI



+++++++++++++***************+++++++++++++++**************++++++++++++*************

si hacemos un struct - enum - typedef ---> en el correspondiente archivo.h asi todos lo tienen 
(verificar que nadie mas haga uno parecido para lo mismo)

toda funcion que hagamos en nuestro archivo.c , debemos "declararla" en el archivo.h , para que los demas puedan acceder si necesitan

config.c y config.h se usan solo apra obtener un valor que se encuentre en el archivo.env
gamelogic.c y gamelogic.h se usan para structs y funciones que calculan manu y benja
graphics_storage.h/c se usan para funciones exclusivamente graficas
los 3 scoreboard, son para las funciones de manejo del ranking y los archivos
el archivo .env y el dll son necesarios para que tanto la parte grafica como la de archivos funione correctamente

*-*
en main manejamos el loop principal, y llamamos a las funciones cuando sea necesario
*-*

PD: si usamos scoreboardV2, recordar llamar apropiadamente (usar scoreboar_test de guia) y liberar memoria


+++++++++++++***************+++++++++++++++**************++++++++++++*************

----------------------------Proyecto modularizado MIYO-----------------------------------------
TAMAÑO PANTALLA 1280 * 720
-----------------------------------------------------------------------------------------------

Horas Programacion
//IntegratorMiyoV1 -> Prototipo de funciones y main inicial 
*3hs iniciales
//Modificacion para coordenadas relativas en funciones graficas
*8hs con parte grafica Domingo
// IntegradorMiyoV2 -> memoria dinamica y primer intento de integracion de todos los codigos de cada uno
*7hs nueva estructura archivos, memoria dinamica y lograr compilar todo junto
12/11 -> 5 horas, de nuevo cambio la estructura de archivos // ahora config.c scoreboardV1 y scoreboardV2 junto a scoreboard_test
12/11 -> 4 horas , revision de funciones memoria dinamica, proyecto en git y config.
12-11 -> 4 horas , correcta instalacion de las bibliotecas graficas , en vez de copiarlas y qeu funcione a veces
13-11 -> 6 horas , scoreboard_v3 , uso de diferentes carpetas , instalacion e instructivos linux
14-11 -> 2 horas , Edicion de READMES , creacion de carpeta Pruebas con menos archivos, para hacer un gamelogic+main de prueba
15-11 -> 2 Horas , division de vector de cada mazo en cartas individuales .png


------------------------------------------------------------------------------------------------
Evolucion Archivos Files/scoreboard
*Proyecto en Drive https://drive.google.com/drive/folders/1eUS_w_vo_eg3GkFpGmb9hGzu-Kx6sQyM?usp=drive_link
-main.c archivo_configuracion.c archivo_configuracion.h
-sinjuego.c archivo_configuracion.c archivo_configuracion.h
---Carpeta nueva
-files.c files.h // tiene todo andando, agregado borrar archivo
-files2.c files2.h // con memoria dinamica , revision de liberar memoria.
Pendiente:
* definir parametros que recibo en mi funcion"main"
*scoreboard_v1.c y scoreboard_v2.c. Esto ayudará a clarificar su propósito.
Si contienen funciones similares pero con diferentes implementaciones, podría 
ser útil crear un archivo de cabecera (scoreboard.h) que contenga las definiciones 
de las funciones que ambos archivos implementan. Esto permite que otros módulos 
incluyan esta cabecera para acceder a las funciones del scoreboard, independientemente 
de la implementación que elijas.
 --> realizado 12/11
*Proyecto en GitHub.com/MiyoBran/proyecto_integrador.git 

* ahora config.c scoreboardV1 y scoreboardV2(con memoria dinamica) junto a scoreboard_test.c
se cambio las funciones definitivas a nombre en ingles, falta hacer lo mismo con las variables
-->13/11
PENDIENTE:
//Falta ver las funciones repetidas en los demas, y tratar de integrar lo que esta.
//Armar un Prototipo de gamelogic para simular las interacciones necesarias
//Terminar de hacer los cambios de variables de funciones provisorias o de testeo en español, a las definitivas en ingles.




Reglas:
https://www.casino.es/blackjack/reglas-blackjack-europeo/

blackjack/
├── include/
│   ├── carta.h
│   ├── jugador.h
│   ├── juego.h
│   └── ui.h
├── src/
│   ├── carta.c
│   ├── jugador.c
│   ├── juego.c
│   └── ui.c
	
└── main.c

Estructura Propuesta para un Proyecto de Blackjack en C
1. Archivo principal (main.c):

Propósito: Punto de entrada del programa.
Contenido: Inicialización, bucle principal del juego, llamada a funciones de otros módulos.
Nombre sugerido: main.c
2. Módulo de cartas:

Propósito: Manejo de las cartas (crear mazo, barajar, repartir, etc.).
Archivos:
carta.h: Declaración de la estructura Carta, funciones para crear, comparar cartas, etc.
carta.c: Implementación de las funciones declaradas en carta.h.
Nombres sugeridos: carta.h y carta.c
3. Módulo de jugador:

Propósito: Representación de los jugadores (mano, puntaje, acciones).
Archivos:
jugador.h: Declaración de la estructura Jugador, funciones para agregar cartas, calcular puntaje, etc.
jugador.c: Implementación de las funciones declaradas en jugador.h.
Nombres sugeridos: jugador.h y jugador.c
4. Módulo de juego:

Propósito: Lógica principal del juego (repartir cartas iniciales, turnos, condiciones de victoria, etc.).
Archivos:
juego.h: Prototipos de funciones relacionadas con el juego (iniciar juego, jugar ronda, etc.).
juego.c: Implementación de las funciones declaradas en juego.h.
Nombres sugeridos: juego.h y juego.c
5. Módulo de interfaz de usuario:

Propósito: Interacción con el usuario (mostrar mensajes, pedir entradas).
Archivos:
ui.h: Prototipos de funciones para mostrar el estado del juego, pedir acciones al jugador, etc.
ui.c: Implementación de las funciones declaradas en ui.h.
Nombres sugeridos: ui.h y ui.c
6. Módulo de configuración (opcional):

Propósito: Almacenar constantes, configuraciones personalizables del juego.
Archivos:
config.h: Definición de constantes (número de barajas, valor de las cartas, etc.).
Nombre sugerido: config.h



