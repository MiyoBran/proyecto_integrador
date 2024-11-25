Aquí tienes el archivo `README.md` correctamente formateado y ajustado:

```markdown
# Blackjack - Juego en C

Este proyecto implementa un juego de Blackjack desarrollado en lenguaje C, utilizando bibliotecas gráficas **raylib** y **glfw3**. 
- Git del proyecto: https://github.com/MiyoBran/proyecto_integrador
- Drive del proyecto: https://drive.google.com/drive/folders/1eUS_w_vo_eg3GkFpGmb9hGzu-Kx6sQyM?usp=drive_link
- A continuación, se explican los requisitos y los pasos necesarios para compilar y ejecutar el proyecto en un sistema operativo Linux o Windows usando Cygwin.

---

## **Requisitos**

### **Dependencias**
Antes de compilar, asegúrate de tener instaladas las siguientes herramientas y bibliotecas:
- **Compilador GCC**
- **pkg-config** (para gestionar las rutas de las bibliotecas)
- **raylib** (biblioteca gráfica)
- **glfw3** (biblioteca para manejar ventanas y entradas)

### **Instalación de Dependencias**
Consulta las instrucciones de instalación para Windows y Linux en la carpeta **Para Graficos/**.

#### En distribuciones basadas en Debian/Ubuntu:
```bash
sudo apt update
sudo apt install libglfw3-dev libraylib-dev pkg-config build-essential
```

#### En distribuciones basadas en Fedora:
```bash
sudo dnf install glfw-devel raylib-devel pkg-config gcc
```

---

## **Estructura del Proyecto**

El proyecto tiene la siguiente estructura de directorios:

```
blackjack/
├── blackjack_grafico
│   ├── .env
│   ├── Blackjack cards/
│   │   └── Recursos Graficos
│   ├── blackjackFull.exe
│   ├── config.c
│   ├── config.h
│   ├── cygglfw-3.dll      // Necesario para compilar en algunos entornos
│   ├── graphics_storage.c
│   ├── graphics_storage.h
│   ├── include/
│   │   ├── gamelogic.h
│   │   ├── jugador.h
│   │   ├── record.h
│   │   └── scoreboard.h
│   ├── main.c
│   ├── README.md          // Compilación juego completo con gráficos
│   ├── reglas.txt
│   └── src/
│       ├── gamelogic.c
│       ├── jugador.c
│       ├── record.c
│       └── scoreboard.c
├── completo_terminal
│   ├── .env
│   ├── include/
│   │   ├── config.h
│   │   ├── jugador.h
│   │   ├── logica.h
│   │   ├── mazo.h
│   │   ├── record.h
│   │   └── scoreboard.h
│   ├── main.c
│   ├── Readme.MD          // Compilación juego completo por terminal
│   ├── reglas.txt         // Diferentes a las de la otra carpeta
│   └── src/
│       ├── config.c
│       ├── jugador.c
│       ├── logica.c
│       ├── mazo.c
│       ├── record.c
│       └── scoreboard.c
├── DOCUMENTACION
│   ├── Changelog Manu_Benja.txt
│   ├── Lizandro, Work log and to do list.txt
│   └── README-Changelog MIYO.txt
├── Para Graficos
│   ├── 1 - Instalacion glfw.txt
│   ├── 2 - Instalacion raylib.txt
│   ├── glfw-master.zip
│   ├── raylib-master.zip
│   └── README-Bilbiotecas graficas.txt
└── README.md              // Árbol de proyecto - Compilación - Recursos
```

---

## **Compilación**

### **Pasos para Compilar**

1. Navega al directorio del proyecto que desees compilar:
   ```bash
   cd blackjack_grafico/
   cd completo_terminal/
   cd completo_terminal/Tools/
   ```
2. Ejecuta el siguiente comando para compilar el proyecto:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
   Esto generará un archivo ejecutable llamado `blackjackFull`, `blackjack` o `crearScoreHistorial`.

3. Para compilar desde cero en entorno Cygwin (reemplaza `USUARIO` por tu nombre de usuario):
   ```bash
   gcc -o blackjackFull main.c config.c src/gamelogic.c graphics_storage.c src/jugador.c src/record.c src/scoreboard.c \
      -I/home/USUARIO/raylib/src \
      -I/home/USUARIO/glfw/include/GLFW \
      -I./include \
      -L/home/USUARIO/glfw/build/src \
      -L/home/USUARIO/raylib/src \
      -L/usr/local/lib \
      -lraylib \
      -lglfw3 \
      -lgdi32 \
   ```

4. Si deseas recompilar desde cero en Linux:
   ```bash
   gcc -o blackjackFull main.c config.c src/gamelogic.c graphics_storage.c \
      src/jugador.c src/record.c src/scoreboard.c \
      -Iinclude \
      $(pkg-config --cflags raylib) $(pkg-config --cflags glfw3) \
      -L/usr/local/lib \
      $(pkg-config --libs raylib) $(pkg-config --libs glfw3) \
      -lm
   ```

---

## **Ejecución**

Una vez compilado, puedes ejecutar el programa con los siguientes comandos según el ejecutable generado:
```bash
./blackjackFull
```
```bash
./blackjack
```
```bash
./crearScoreHistorial
```

---

## **Detalles Adicionales**

- **Archivos necesarios en tiempo de ejecución**:
  Asegúrate de que los archivos `reglas.txt`, `.env` y `Blackjack cards/` estén en el mismo directorio que el ejecutable `blackjackFull`.

- **Funciones Principales del Programa**:
  - Implementación de las reglas del Blackjack.
  - Registro y manejo del historial de puntuaciones (`datos_historial.dat`).
  - Generación y visualización del ranking (`datos_ranking.dat`).

---

## **Contribuidores**

- **Miyo** - *Desarrollo de módulos y gestión de archivos.*
- **Lizandro** - *Implementación y soporte de gráficos.*
- **Manu y Benja** - *Diseño e implementación de la lógica desde cero para integración gráfica.*

---

## **Notas**

Si encuentras problemas durante la compilación o ejecución, verifica:
1. Que las bibliotecas estén correctamente instaladas.
2. Que las versiones de `raylib` y `glfw3` sean compatibles.

En caso de dudas o sugerencias, no dudes en contactar con el equipo de desarrollo.
```
