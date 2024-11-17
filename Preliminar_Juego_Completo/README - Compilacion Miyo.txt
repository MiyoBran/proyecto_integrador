-----------------------------------------------------------------------------------------------
*/*/*/*/* Con instalacion correcta en ubuntu (lo importante es copiar los flags de compilacion despues de los archivos fuente)
$(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm

Flags adicionales
* -Iinclude -I. // donde buscar headers si hay carpetas
* -Wall -std=c11 // para depurar y ver errores

Linux--->Main:
gcc -o mainGrafico main.c  graphics_storage.c config.c scoreboardV2.c gamelogic.c $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm
-----------------------------------------------------------------------------------------------
Para Windows+cygwin
/////////////REVISAR CADA UNO 
/*Cada uno cambiar la carpeta /home/nombre y flags si hace falta*/
Lizandro:
-I/home/Lizandro/raylib/src -I/home/Lizandro/glfw/include/GLFW -L/home/Lizandro/raylib/src -L/home/Lizandro/glfw/build/src 
-lraylib -lglfw -lgdi32

Miyo:
-lraylib -lgdi32 -lopengl32 -lwinmm -lglfw3
-I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src


Example:
gcc -o mainGrafico main.c  graphics_storage.c config.c scoreboardV2.c gamelogic.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lgdi32 -lopengl32 -lwinmm -lglfw3
-----------------------------------------------------------------------------------------------
/*Para compilar y probar solo 1 a la vez // Comentar el include raylib si se puede

--- Ultima compilacion completa juego Blackjack
$ gcc -o blackjack config.c  jugador.c  logica.c  mazo.c scoreboardV2.c mainV4.c






-- Version completamente dinamica y en las carpetas
gcc -o v3scoreboard_test src/scoreboardV3_test.c src/scoreboardV3.c config.c -Iinclude -I.  -Wall -std=c11



->Para borrar todos los archivos compilados
rm -rf scoreEstaticotest dinamicoScoretest v3scoreboard_test mainGrafico 

-----------------------------------------------------------------------------------------------
COMANDOS PARA GIT


# Verificar el estado del repositorio
git status

# Agregar todos los cambios al área de preparación
git add .

# Realizar el commit
git commit -m "Aca va el mensaje del commit, sino abre nano"

# Mandar tus cambios al repositorio remoto
git push origin main

---- Para ver cambios

# Verificar si hay actualizaciones en el repositorio remoto
git fetch origin

# Verificar direccion del escritorio remoto
git remote -v

# Comparar tu rama local con la rama remota
git diff origin/main

# Actualizar tu proyecto local si es necesario
git pull origin main

