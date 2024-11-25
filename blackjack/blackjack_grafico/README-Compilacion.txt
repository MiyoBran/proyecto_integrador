-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
importante --> archivo .env  con lo siguiente:

archivo_ranking=datos_ranking.dat
archivo_historial=datos_historial.dat

-----------------------------------------------------------------------------------------------
*/*/*/*/* Con instalacion correcta en ubuntu (lo importante es copiar los flags de compilacion despues de los archivos fuente)
$(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm

Flags adicionales
* -Iinclude src/*.c //  Si tenemos carpetas /include y /src
* -static           //  asegura que todas las bibliotecas se vinculen de manera estática
* -O2               //  Activa optimizaciones moderadas sin aumentar significativamente el tiempo de compilación 
* -03               //  Activa optimizaciones más agresivas que pueden aumentar el rendimiento pero a veces generan binarios más grandes o comportamientos inesperados
* -Iinclude -I.     //  donde buscar headers si hay carpetas
* -Wall -std=c11    //  para depurar y ver errores

Linux con estructura carpetas:
gcc -o blackjackFull main.c src/config.c src/gamelogic.c src/graphics_storage.c \
    src/jugador.c src/record.c src/scoreboard.c \
    -Iinclude -I. \
    $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) \
    -L/usr/local/lib \
    $(pkg-config --libs raylib) $(pkg-config --libs glfw3) \
    -lm

-----------------------------------------------------------------------------------------------
Para Windows+cygwin
/////////////REVISAR CADA UNO 
/*Cada uno cambiar la carpeta /home/nombre y flags si hace falta*/
gcc -o blackjackFull main.c config.c src/gamelogic.c graphics_storage.c src/jugador.c src/record.c src/scoreboard.c \
    -I/home/USUARIO/raylib/src \
    -I/home/USUARIO/glfw/include/GLFW \
    -I./include
    -I.
    -L/home/USUARIO/glfw/build/src \
    -L/home/USUARIO/raylib/src \
    -L/usr/local/lib \
    -lraylib \
    -lglfw3 \
    -lgdi32
    -static 
    -O2

Example:
gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -I./include -I. -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib -lraylib -lglfw3 -lgdi32 config.c src/gamelogic.c graphics_storage.c src/jugador.c src/record.c src/scoreboard.c -static -O2

-----------------------------------------------------------------------------------------------
/*Para compilar JUEGO ACTUAL archivos unificadosV3:

gcc -o blackjackFull main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -I./include -I. -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib -lraylib -lglfw3 -lgdi32 config.c src/gamelogic.c graphics_storage.c src/jugador.c src/record.c src/scoreboard.c -static -O2

OPCION con desglose
gcc -o blackjackFull main.c config.c src/gamelogic.c graphics_storage.c src/jugador.c src/record.c src/scoreboard.c \
    -I/home/Miyo/raylib/src \
    -I/home/Miyo/glfw/include/GLFW \
    -I./include
    -I.
    -L/home/Miyo/glfw/build/src \
    -L/home/Miyo/raylib/src \
    -L/usr/local/lib \
    -lraylib \
    -lglfw3 \
    -lgdi32
    -static 
    -O2
-----------------------------------------------------------------------------------------------
Linux
ULTIMO FUNCIONANDO:
gcc -o blackjackFull main.c config.c gamelogic.c graphics_storage.c jugador.c record.c scoreboard.c $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm
----
Las opciones de preprocesador (-I) van primero.
Luego las opciones de vinculación (-L).
Después las bibliotecas (-l).
Finalmente, las opciones generales (-static, -O2).

-- Posibles faltantes en linux
-lm -lpthread -lX11

---- PROBAR:
Hacer Cmakelists

rm -rf build


mkdir build
cd build
cmake ..

cmake --build .

Verificar si pkg-config encuentra raylib y glfw
pkg-config --cflags --libs raylib
pkg-config --cflags --libs glfw3

Si no:
find / -name "raylib.pc" 2>/dev/null

y aca mandar al path la ruta encontrada, por ej:

export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH

para no tener que repetir --> nano ~/.bashrc

--- TAMBIEN PUEDE GENERAR PROBLEMA LOS FLAGS -static y -02 / Sacarlos

