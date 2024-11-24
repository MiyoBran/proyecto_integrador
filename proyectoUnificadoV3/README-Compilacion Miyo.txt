-----------------------------------------------------------------------------------------------
/*Para compilar JUEGO ACTUAL archivos unificadosV3:

gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c -static -O2


OPCION con desglose
gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW \
    -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib \
    -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c
    -static -O2
--- OpcionB:
gcc -o blackjackFull main.c config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c \
    -I/home/Miyo/raylib/src \
    -I/home/Miyo/glfw/include/GLFW \
    -L/home/Miyo/glfw/build/src \
    -L/home/Miyo/raylib/src \
    -L/usr/local/lib \
    -lraylib \
    -lglfw3 \
    -lgdi32
    -static 
    -O2

---- PROBAR:
1. Compilación estática (si es posible)
Si las bibliotecas que estás usando (raylib, GLFW) tienen versiones estáticas (.a),
puedes generar un ejecutable independiente que no dependa de bibliotecas externas. 
Modifica tu comando de compilación para incluir -static:
gcc -o blackjackFull.exe main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW \
    -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib \
    -lraylib -lglfw3 -lgdi32 -static config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c
----
2. Compilación dinámica
En este caso, debes copiar las bibliotecas necesarias (como raylib.dll y glfw3.dll) junto con el ejecutable. 
El comando sigue siendo el mismo, pero el ejecutable dependerá de estas bibliotecas dinámicas. No uses -static.

gcc -o blackjackFull.exe main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW \
    -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib \
    -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c
Busca los archivos .dll necesarios:
raylib.dll: Normalmente está en el directorio bin de raylib.
glfw3.dll: Debe estar en tu instalación de GLFW.
Cualquier otra biblioteca adicional que use tu programa.
Copia estos archivos en la misma carpeta que blackjackFull.exe.
-----
3. Organizar la carpeta de distribución
Crea una carpeta (por ejemplo, Blackjack_Distribucion) y coloca en ella:

El ejecutable (blackjackFull.exe).
Las bibliotecas dinámicas necesarias (raylib.dll, glfw3.dll, etc.).
Cualquier otro recurso necesario para tu programa (imágenes, sonidos, archivos de configuración).
---
4. Crear el archivo .bat
Crea un archivo jugar_blackjack.bat dentro de esa carpeta con el siguiente contenido:

@echo off
title Blackjack - Tu Juego de Cartas Favorito
echo Iniciando Blackjack...
blackjackFull.exe
pause
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
importante --> archivo .env  con lo siguiente:

archivo_ranking=datos_ranking.dat
archivo_historial=datos_historial.dat


-----------------------------------------------------------------------------------------------
SI se usa raylib
*/*/*/*/* Con instalacion correcta en ubuntu (lo importante es copiar los flags de compilacion despues de los archivos fuente)
$(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm

Flags adicionales
* -Iinclude src/*.c //  Si tenemos carpetas /include y /src
* -static           //  asegura que todas las bibliotecas se vinculen de manera estática
* -O2               //  Activa optimizaciones moderadas sin aumentar significativamente el tiempo de compilación 
* -03               //  Activa optimizaciones más agresivas que pueden aumentar el rendimiento pero a veces generan binarios más grandes o comportamientos inesperados
* -Iinclude -I.     //  donde buscar headers si hay carpetas
* -Wall -std=c11    //  para depurar y ver errores

Linux--->Main EJ:
gcc -o blackjackFull main.c config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c \
    $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) \
    -L/usr/local/lib \
    $(pkg-config --libs raylib) $(pkg-config --libs glfw3) \
    -lm
Linux con estructura carpetas:
gcc -o blackjackFull main.c src/config.c src/gamelogic.c src/graphics_storage.c \
    src/jugador.c src/record.c src/scoreboard.c \
    -Iinclude \
    $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) \
    -L/usr/local/lib \
    $(pkg-config --libs raylib) $(pkg-config --libs glfw3) \
    -lm

ULTIMO FUNCIONANDO:
gcc -o blackjackFull main.c config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm
-----------------------------------------------------------------------------------------------
Para Windows+cygwin
/////////////REVISAR CADA UNO 
/*Cada uno cambiar la carpeta /home/nombre y flags si hace falta*/
gcc -o blackjackFull main.c config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c \
    -I/home/NOMBREUSUARIO/raylib/src \
    -I/home/NOMBREUSUARIO/glfw/include/GLFW \
    -L/home/NOMBREUSUARIO/glfw/build/src \
    -L/home/NOMBREUSUARIO/raylib/src \
    -L/usr/local/lib \
    -lraylib \
    -lglfw3 \
    -lgdi32
    -static
    -O2

Example:
gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c


----
Las opciones de preprocesador (-I) van primero.
Luego las opciones de vinculación (-L).
Después las bibliotecas (-l).
Finalmente, las opciones generales (-static, -O2).

-- Posibles faltantes en linux
-lm -lpthread -lX11
