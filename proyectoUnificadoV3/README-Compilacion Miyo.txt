-----------------------------------------------------------------------------------------------
/*Para compilar JUEGO ACTUAL archivos unificadosV3:

gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c


OPCION con desglose
gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW \
    -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib \
    -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c
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
* -Iinclude -I. // donde buscar headers si hay carpetas
* -Wall -std=c11 // para depurar y ver errores

Linux--->Main EJ:
gcc -o blackjackFull main.c config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c \
    $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) \
    -L/usr/local/lib \
    $(pkg-config --libs raylib) $(pkg-config --libs glfw3) \
    -lm


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

Example:
gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib -lraylib -lglfw3 -lgdi32 config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c
