LINUX ---> a partir de linea 80 estan los comandos
**************************************************
                    WINDOWS
**************************************************
Las dos carpetas, raylib y glfw, adentro de home/NOMBREDEUSUARIO
, son necesarias para compilar la parte grafica

-----------------------------------------------------------------------------------------------
******************
      GLFW
******************
 --> para opengl
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


-----------------------------------------------------------------------------------------------
******************
      Raylib
******************
https://github.com/raysan5/raylib --> Code ---> Download zip

Extrae el archivo ZIP descargado a una ubicación de tu preferencia, como ~/raylib (en Home)
cd ~/raylib
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DPLATFORM=PLATFORM_DESKTOP


---> despues make y make install

*-* Si hay error de wayland, agregar paquetes a la instalacion de cygwin
wayland-scanner no está incluido en el paquete wayland-protocols, sino en wayland-devel o libwayland-dev
*-* Tambien puede faltar agregar alguna de las siguientes:
libx11-dev libxrandr-dev libxinerama-dev libxi-dev libxcursor-dev libxfixes-dev libxext-dev libxcomposite-dev libglu1-mesa-dev

******************
Usar Raylib en el proyecto
Después de compilar o instalar Raylib. Incluir los archivos de encabezado y enlazar las bibliotecas correctamente:
-I/home/Miyo/raylib/src -L/home/Miyo/raylib/build 
-lraylib -lgdi32 -lopengl32 -lwinmm


gcc -o main main.c -I/home/Miyo/raylib/src -L/home/Miyo/raylib/build -lraylib -lgdi32 -lopengl32 -lwinmm

-----------------------------------------------------------------------------------------------


**************************************************
                    Linux - Ubuntu 
**************************************************
----------------------------
->primero glfw
----------------------------


PASOS:

--- TESTEADO EN instalacion nueva de LINUXMINT
*Opcional pero yo lo hice
sudo apt update
sudo apt upgrade
*Desde aca empiezan las indicaciones
sudo apt install make
sudo apt install cmake

*Quiza algunos de los siguientes no sean necesarios
sudo apt install libglfw3 libglfw3-dev libraylib-dev
sudo apt-get install libx11-dev libxrandr-dev libxinerama-dev libxi-dev libxcursor-dev libxfixes-dev libxext-dev libxcomposite-dev libglu1-mesa-dev
sudo apt-get install wayland-protocols
sudo apt-get install libwayland-dev
//Depende la distribucion podria ser -->wayland-devel en vez de libwayland-dev
which wayland-scanner
sudo apt-get install libxkbcommon-dev

---** ahora si nos tenemos que posicionar en la carpeta extraida 

cd ~/glfw
rm -rf build
mkdir build
cd build
cmake ..
cuando todo sea correcto
make
sudo make install

Ahora Raylib, tambien en home
cd ~/raylib
rm -rf build
mkdir build
cd build
cmake ..
// cuando todo sea correcto
make
sudo make install

*** Por ultimo verificar si esta en el usr :
pkg-config --cflags --libs raylib
Deberia decir --> -I/usr/local/include -L/usr/local/lib -lraylib 
ahora se pueden usar los comandos de compilacion para linux en vez de los especificos

*/*/*/*/* COn instalacion correcta en ubuntu (lo importante es copiar los flags de compilacion despues de los archivos fuente)
$(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) -L/usr/local/lib $(pkg-config --libs raylib) $(pkg-config --libs glfw3) -lm

-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------



OPCION B
cd ~
rm -rf glfw  # Elimina la carpeta glfw actual
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=OFF
make
make install


DESPUES
cd ~
rm -rf raylib # Elimina la carpeta glfw actual


git clone https://github.com/raysan5/raylib.git ~/raylib

cd ~/raylib
mkdir build
cd build

cmake .. -G "Unix Makefiles" -DPLATFORM=PLATFORM_DESKTOP

make
make install
