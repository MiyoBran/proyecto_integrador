Las dos carpetas, raylib y glfw, adentro de home/NOMBREDEUSUARIO
, son necesarias para compilar la parte grafica

************************************************** Raylib --> para graficos 
https://github.com/raysan5/raylib --> Code ---> Download zip

Extrae el archivo ZIP descargado a una ubicación de tu preferencia, como ~/raylib (en Home)
y usar (hay unos comandos = off que quiza no necesiten -> son para cygwin):
cd ~/raylib
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DPLATFORM=PLATFORM_DESKTOP


---> despues make y make install


tambien se puede:
cd ~
rm -rf raylib # Elimina la carpeta glfw actual


git clone https://github.com/raysan5/raylib.git ~/raylib

cd ~/raylib
mkdir build
cd build

cmake .. -G "Unix Makefiles" -DPLATFORM=PLATFORM_DESKTOP

******************
Usar Raylib en tu proyecto
Después de compilar o instalar Raylib, puedes usarlo en tu proyecto. Asegúrate de incluir los archivos de encabezado y enlazar las bibliotecas correctamente:

gcc -o main main.c -I/home/Miyo/raylib/src -L/home/Miyo/raylib/build -lraylib -lgdi32 -lopengl32 -lwinmm



************************************************** GLFW --> para opengl
https://github.com/glfw/glfw ---> code --> download zip
copiar el contenido de glfw-master en una carpeta /glfw en el home
y usar lo siguiente: (hay unos comandos = off que quiza no necesiten):
mkdir glfw
cd glfw
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=OFF


----------- make y despues makeInstall

importante para compilar:
usar el comando
ls ~/glfw/build/src
y ver como se llama el archivo libglfw.a o libglfw3.a
segun eso cambiar el comando de compilacion -lglfw3 en lugar de -lglfw , o renombrar los archivos


tambien se puede:
cd ~
rm -rf glfw  # Elimina la carpeta glfw actual
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=OFF
