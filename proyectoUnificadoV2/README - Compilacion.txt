gcc -o main main.c -I/home/Lizandro/raylib/src -I/home/Lizandro/glfw/include/GLFW -L/home/Lizandro/raylib/src -L/home/Lizandro/glfw/build/src -lraylib -lglfw -lgdi32 graphics_storage.c
<- Original de Lizandro 


/////////////REVISAR CADA UNO
/*Para miyo, solo lo de Lizandro*/
gcc -o main main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lglfw -lgdi32 graphics_storage.c

/// PARA COMPILAR TODOS LOS ARCHIVOS Y PROBAR / CAMBIAR EL *usuario / Miyo ---> Tu nombre de carpeta
gcc -o BlackjackV2 main.c graphics_storage.c config.c scoreboardV2.c gamelogic.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lglfw -lgdi32

/* para compilar solo gamelogic (cambiar lo que haga falta aca para que funcione, en teoria solo el /*Usuario -->Miyo)
Chequear -> gcc -o test_gamelogic test_gamelogic.c gamelogic.c -I/home/*usuario/raylib/src -I/home/*usuario/glfw/include/GLFW


/* para compilar solo los de Archivos/SHOW ranking  y probar
// Tienen que estar en la misma carpeta *scoreboard_test.c config.c config.h scoreboard.h
// gcc scoreboard_test.c config.c scoreboardV1.c -o blackjackV1
// gcc scoreboard_test.c config.c scoreboardV2.c -o blackjackV2


COMANDOS PARA GIT

# Para navegar a la carpeta del proyecto
cd ~/proyectos/tpIntegrador/proyecto_integrador

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

