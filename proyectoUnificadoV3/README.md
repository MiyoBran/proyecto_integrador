### **README.md**

```markdown
# Blackjack - Juego en C

Este proyecto implementa un juego de Blackjack desarrollado en lenguaje C, utilizando bibliotecas gráficas como **raylib** y **glfw3**. A continuación, se explican los requisitos y los pasos necesarios para compilar y ejecutar el proyecto en un sistema operativo Linux.

---

## **Requisitos**

### **Dependencias**
Antes de compilar, asegúrate de tener instaladas las siguientes herramientas y bibliotecas:
- **Compilador GCC**
- **pkg-config** (para gestionar las rutas de las bibliotecas)
- **raylib** (biblioteca gráfica)
- **glfw3** (biblioteca para manejar ventanas y entradas)

### **Instalación de Dependencias**

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
├── Blackjack cards/
│   ├── Recursos Graficos
├── Tools/
│   ├── Programa Compilado para crear archivos.dat
├── Para Graficos/
│   ├── Instalacion glfw.txt
│   ├── Instalacion raylib.txt
│   ├── glfw-master.zip
│   ├── raylib-master.zip
├── DOCUMENTACION/
│   ├── Changelog - Miyo.txt
│   ├── Changelog - Lizandro.txt
│   ├── Changelog - Manu y Benja.txt
│   ├── Bibliotecas Graficas.txt
├── include/
│   ├── config.h
│   ├── jugador.h
│   ├── gamelogic.h
│   ├── graphics_storage.h
│   ├── record.h
│   ├── scoreboard.h
├── src/
│   ├── config.c
│   ├── jugador.c
│   ├── gamelogic.c
│   ├── graphics_storage.c
│   ├── record.c
│   ├── scoreboard.c
├── main.c
├── reglas.txt
├── datos_historial.dat
├── datos_ranking.dat
├── Makefile
└── BlackJackFinal.exe (si se compila en Windows)
```

---

## **Compilación**

### **Pasos para Compilar**

1. Navega al directorio del proyecto:
   ```bash
   cd blackjack/
   ```
2. Ejecuta el siguiente comando para compilar el proyecto:
   ```bash
   make
   ```
   Esto generará un archivo ejecutable llamado `blackjackFull`.

3. Para limpiar los archivos binarios generados durante la compilación, usa:
   ```bash
   make clean
   ```

4. Si deseas recompilar desde cero, usa:
   ```bash
   make rebuild
   ```

---

## **Ejecución**

Una vez compilado, puedes ejecutar el programa con el siguiente comando:
```bash
./blackjackFull
```

---

## **Detalles Adicionales**

- **Archivos necesarios en tiempo de ejecución**:
  Asegúrate de que los archivos `reglas.txt`, `datos_historial.dat` y `datos_ranking.dat` estén en el mismo directorio que el ejecutable `blackjackFull`.

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

---