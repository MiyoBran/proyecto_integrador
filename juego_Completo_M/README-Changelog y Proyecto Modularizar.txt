Base
*Proyecto en GitHub.com/MiyoBran/proyecto_integrador.git 
*Proyecto en Drive https://drive.google.com/drive/folders/1eUS_w_vo_eg3GkFpGmb9hGzu-Kx6sQyM?usp=drive_link


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
-------->Implementacion de lo anterior en el juego actual.
15-11 / 16-11 / 17-11 / 18-11 -> 20/22 horas aprox , nuevo juego completo sin graficos

------------------------------------------------------------------------------------------------
PENDIENTES MIYO al 18-11:
// Imprimir reglas
// Verificar compilacion con archivos en diferentes carpetas
// Crear cmakelist
// Empaquetar y crear paquete de instalacion
// Version otro SO ?
// configuracion con .env o .txt?

---> Entrega 25/11
Mejoras posibles:
Opcion A:
//Implementación de graficos con alguna biblioteca para el juego actual sin mas modificacion
//Implementacion de mejoras graficas por terminal


Opcion B:
//Falta logica para Doblar apuesta
//Agregar otros juegos completos con baraja Francesa como opcion en el menu
//IMPORTANTE:-> (usando las structs de cartas y jugador actuales, sin repetir nombre de funcion para manejo de archivos)
//Implementar sistema de id de usuario para retomar partida
//Login para validar?
//Cambiar funciones actuales para implementar conceptos de la teoria que hayan faltado


Reglas:
https://www.casino.es/blackjack/reglas-blackjack-europeo/
Posible Estructura

blackjack/
├── include/
│   ├── config.h
│   ├── jugador.h
│   ├── logica.h
│   ├── mazo.h
│   ├── record.h
│   ├── scoreboard.h
├── src/
│   ├── config.c
│   ├── jugador.c
│   ├── logica.c
│   ├── mazo.c
│   ├── record.c
│   ├── scoreboard.c
├── .env
├── main.c
├── README/
│   ├── Changelog.txt
│   ├── Modularizar.txt
│   ├── Compilacion.txt
│   └── Implementacion_Funciones.txt
└── Makefile

