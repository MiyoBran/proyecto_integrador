Base
*Proyecto en GitHub.com/MiyoBran/proyecto_integrador.git 
*Proyecto en Drive : con todas las "copias de seguridad" enviadas
https://youtu.be/0w-_GU6QhZ4


----------------------------Proyecto modularizado MIYO-----------------------------------------
TAMAÑO PANTALLA 1280 * 720
-----------------------------------------------------------------------------------------------

Horas Programacion:
//IntegratorMiyoV1 -> Prototipo de funciones y main inicial 
-> 3 horas iniciales
//Modificacion para coordenadas relativas en funciones graficas
-> 8 horas con parte grafica Domingo
// IntegradorMiyoV2 -> memoria dinamica y primer intento de integracion de todos los codigos de cada uno
-> 7 horas nueva estructura archivos, memoria dinamica y lograr compilar todo junto
12/11 -> 5 horas, de nuevo cambio la estructura de archivos // ahora config.c scoreboardV1 y scoreboardV2 junto a scoreboard_test
12/11 -> 4 horas , revision de funciones memoria dinamica, proyecto en git y config.
12-11 -> 4 horas , correcta instalacion de las bibliotecas graficas , en vez de copiarlas y qeu funcione a veces
13-11 -> 6 horas , scoreboard_v3 , uso de diferentes carpetas , instalacion e instructivos linux
14-11 -> 2 horas , Edicion de READMES , creacion de carpeta Pruebas con menos archivos, para hacer un gamelogic+main de prueba
15-11 -> 2 Horas , division de vector de cada mazo en cartas individuales .png
-------->Implementacion de lo anterior en el juego actual.
15-11 / 16-11 / 17-11 / 18-11 -> 20/22 horas aprox , Nuevo JUGADOR/scoreboard/RECORD+ juego completo sin graficos
19/11 2HS   -> TXT y PDF GuiA Implementacion,  -> Juego_Completo_M1.0
20/11 1H    -> Creacion proyectoUnificadoV3 incluye propio:
    *config.c/h
    *jugador.c/h
    *record.c/h
    *scoreboard.c/h 
    *datos_historial.dat y datos_ranking.dat
    *.env con los nombres de esos 2 archivos.
    *Carpeta Para Graficos y guia instalacion bibliotecas
    *Archivos README : Changelog - compilacion - guia implementacion funciones proyecto
21/11 4HS   -> Funcion para crear struct jugador, a partir de nombre y puntaje, asi usar historial
            -> Modificacion guia de implementacion.
            -> Main para crear archivo historial o archivo ranking con datos ingresados por teclado
23/11 4HS   -> Cmakelist + Cpack + compilacion en carpetas ---> Portables andando en Windows
24/11 4HS   -> Carpeta Para Entrega + Cmakelists + Readme.MD + PRUEBAS de Compilación

------------------------------------------------------------------------------------------------
PENDIENTES / funcionalidades posibles para los archivos actuales al 19-11:
//  Falta logica para opcion Doblar apuesta 
//  Falta logica para recuperar apuesta si perdemos pero teniamos blackjack
//  Falta logica para dividir cartas (lista enlazada/doblemente o Jump_table)
//  Multiplayer vs banca (Jump_table?)
//  Falta solucionar/revisar problema con indice en manoInicial usando formato
//  Exportar registro a txt/csv.
//  Validar archivo para poder importar (hashing?)
//  Importar archivo de registro de alguien mas para merge
//  Funciones de busqueda y ordenamiento para un registro mas grande
//  Compilar todo Usando SHA 256 y Certificado de seguridad


Listo:
// Imprimir reglas (europeo) , leer desde archivo txt?
// Verificar compilacion con archivos en diferentes carpetas
// Crear cmakelist
// Empaquetar y crear paquete de instalacion
// Version otro SO -> con -static y/o +dll
// configuracion con .env o .txt?

---> Entrega 25/11


Otros Caminos posibles:
Opcion A:
//  Implementación de graficos con alguna biblioteca para el juego actual sin mas modificacion
//  Esta alternativa implica hacer un archivomain.c , que reemplaza a main.c al compilar
//  Implementacion de mejoras graficas por terminal usando otros archivos .c .h
    ->Imprimir cartas o cosas asi (esto hace compatible agregar juegos, en otro case, sin reescribir el main )
    ->Se deberian revisar todas las funciones que tienen un printF.
    ->Copiarlas,pegarlas,renombrarlas y cambiar las funicones que las utilizan?


Opcion B:
//  Agregar un blackjack con reglas europeas e implementacion diferente.
//  Agregar un blackjack con reglas americanas.
//  Agregar otros juegos completos con baraja Francesa (poker?) como opcion en el menu
//  Agregar opcion para juegos que usan mas mazos
//  IMPORTANTE:-> (usando las structs de cartas y jugador actuales, sin repetir nombre de funcion para manejo de archivos)
//  Implementar sistema de id de usuario para retomar partida
//  login para validar?
//  Cambiar funciones actuales para implementar conceptos de la teoria que hayan faltado:
    1-paridad
    2-humming
    3-luhn
    4-modulo11
    5-Hashing
    6-regresion_lineal
    7-Jump_table
    8-Lista enlazada y doblemente enlazada


Reglas:
https://www.casino.es/blackjack/reglas-blackjack-europeo/

El proyecto tiene la siguiente estructura de directorios:
```
blackjack/
├── Blackjack cards/
│   ├── Recursos Graficos
├── Tools/
│   ├── Programa Compilado para crear archivos.dat
├── Para Graficos/
│   ├── Instalacion glfw.txt
│   ├── Instalacion raylib.txt
│   ├── glfw-master.zip
│   ├── raylib-master.zip
├── DOCUMENTACION/
│   ├── Changelog - Miyo.txt
│   ├── Changelog - Lizandro.txt
│   ├── Changelog - Manu y Benja.txt
│   ├── Bibliotecas Graficas.txt
├── include/
│   ├── config.h
│   ├── jugador.h
│   ├── gamelogic.h
│   ├── graphics_storage.h
│   ├── record.h
│   ├── scoreboard.h
├── src/
│   ├── config.c
│   ├── jugador.c
│   ├── gamelogic.c
│   ├── graphics_storage.c
│   ├── record.c
│   ├── scoreboard.c
├── main.c
├── reglas.txt
├── datos_historial.dat
├── datos_ranking.dat
├── Makefile
└── BlackJackFinal.exe (si se compila en Windows)
