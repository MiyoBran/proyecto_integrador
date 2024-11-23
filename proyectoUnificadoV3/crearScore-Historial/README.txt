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

Esto generará archivos como CrearScoreHistorial-1.0.0-Linux.tar.gz o 
CrearScoreHistorial-1.0.0.zip en la carpeta build. Estos paquetes contendrán:
El ejecutable en la carpeta bin/.
Los archivos de datos y el README.txt en share/crearScoreHistorial/.

*-*
luego en el otro sistema
Descomprimir el paquete:
tar -xvf CrearScoreHistorial-1.0.0-Linux.tar.gz
Ejecutar el programa:
cd bin
./crearScoreHistorial


-----
rm -rf build             # Elimina la carpeta build anterior (si existe)
mkdir build              # Crea una nueva carpeta build
cd build                 # Entra en la carpeta build
cmake ..                 # Configura el proyecto
cmake --build . --target package  # Compila y empaqueta
cpack                    # Crea el paquete comprimido





tar -tjf ./_CPack_Packages/CYGWIN/CygwinBinary/crearScoreHistorial-0.1.1-CYGWIN-1.tar.bz2
C:\cygwin64\home\Miyo\proyectos\tpIntegrador\proyecto_integrador\crearScore-Historial
mover a home
mv /home/Miyo/proyectos/tpIntegrador/proyecto_integrador/crearScore-Historial/build/crearScoreHistorial-0.1.1-CYGWIN-1.tar.bz2 ~/


Opcional:
cd ..
en la carpeta del build
find . -type f
find . -maxdepth 3

Mover a home
mv ./build/crearScoreHistorial-0.1.1-CYGWIN.tar.gz ~/

extraer contenido
tar -xvzf ~/crearScoreHistorial-0.1.1-CYGWIN.tar.gz -C ~/




ls -R ~/crearScoreHistorial




