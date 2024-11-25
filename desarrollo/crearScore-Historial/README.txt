Crear una carpeta de compilación: Es buena práctica generar los archivos de compilación en una carpeta separada:

mkdir build
cd build
cmake ..
cmake --build .



Ejecutar el programa: Una vez compilado, puedes ejecutar el programa desde la carpeta build con:

cd ..
./crearScoreHistorial

--------------
Con Cpack
Desde la raiz
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .

--- crear el paquete
cpack
Resultado:


-----
rm -rf build             # Elimina la carpeta build anterior (si existe)
mkdir build              # Crea una nueva carpeta build
cd build                 # Entra en la carpeta build
cmake ..                 # Configura el proyecto
cmake --build . --target package  # Compila y empaqueta
cpack                    # Crea el paquete comprimido




Opcional:
cd ..
en la carpeta del build
find . -type f
find . -maxdepth 3

Mover a home
mv ./build/crearScoreHistorial-0.1.1-CYGWIN.tar.gz ~/

extraer contenido
tar -xvzf ~/crearScoreHistorial-0.1.1-CYGWIN.tar.gz -C ~/

Chequear
ls ~/
Si esta la carpeta
cd ~/blackjack
o sino
cd ~/crearScoreHistorial-0.1.1-CYGWIN/blackjack








ls -R ~/crearScoreHistorial




