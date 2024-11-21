-----------------------------------------------------------------------------------------------
/*Para compilar y probar solo 1 a la vez // Comentar el include raylib si esta, para probar solo esto

/*Para compilar JUEGO ACTUAL archivos propios:

gcc -o blackjack main.c config.c jugador.c logica.c mazo.c record.c scoreboard.c

/*Para compilar JUEGO ACTUAL archivos unificadosV3:

gcc -o blackjack main.c config.c jugador.c gamelogic.c graphics_storage.c record.c scoreboard.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src


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
gcc -o mainGrafico main.c  graphics_storage.c config.c scoreboardV2.c gamelogic.c $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm
-----------------------------------------------------------------------------------------------
Para Windows+cygwin
/////////////REVISAR CADA UNO 
/*Cada uno cambiar la carpeta /home/nombre y flags si hace falta*/

-lraylib -lgdi32 -lopengl32 -lwinmm -lglfw3
-I/home/NOMBREUSUARIO/raylib/src -I/home/NOMBREUSUARIO/glfw/include/GLFW -L/home/NOMBREUSUARIO/raylib/src -L/home/NOMBREUSUARIO/glfw/build/src

Example:
gcc -o mainGrafico main.c  graphics_storage.c config.c scoreboardV2.c gamelogic.c -I/home/NOMBREUSUARIO/raylib/src -I/home/NOMBREUSUARIO/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lgdi32 -lopengl32 -lwinmm -lglfw3
