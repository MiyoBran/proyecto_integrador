gcc -o main main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lglfw -lgdi32 graphics_storage.c
<- Original de Miyo 

*/*/*/*/* COn instalacion correcta en ubuntu (lo importante es copiar los flags de compilacion despues de los archivos fuente)
$(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm

EJ en linux--->Main:
gcc -o mainGrafico main.c  graphics_storage.c config.c scoreboardV2.c gamelogic.c $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm


/* para compilar solo los de Archivos/SHOW ranking  y probar
// Tienen que estar en la misma carpeta *scoreboard_test.c config.c config.h scoreboard.h
gcc -o scoreEstaticotest scoreboard_test.c config.c scoreboardV1.c 
gcc -o dinamicoScoretest scoreboard_test.c config.c scoreboardV2.c 
-- Version completamente dinamica y en las carpetas
gcc -o v3scoreboard_test src/scoreboardV3_test.c src/scoreboardV3.c config.c -Iinclude -I.  -Wall -std=c11



---Para borrar todos los archivos compilados
rm -rf scoreEstaticotest dinamicoScoretest v3scoreboard_test mainGrafico 


/////////////REVISAR CADA UNO en windows
/*Para miyo, cada uno cambiar la carpeta /home/nombre y flags si hace falta*/
-lraylib -lgdi32 -lopengl32 -lwinmm -lglfw3
gcc -o mainGrafico main.c  graphics_storage.c config.c scoreboardV2.c gamelogic.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lgdi32 -lopengl32 -lwinmm -lglfw3


/* para compilar solo los de Archivos/SHOW ranking  y probar
// Tienen que estar en la misma carpeta *scoreboard_test.c config.c config.h scoreboard.h
// gcc scoreboard_test.c config.c scoreboardV1.c -o scoreEstaticotest
// gcc scoreboard_test.c config.c scoreboardV2.c -o dinamicoScoretest


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

