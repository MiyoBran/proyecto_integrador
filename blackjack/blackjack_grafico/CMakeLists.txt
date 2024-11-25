cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(blackjack_grafico VERSION 1.0 LANGUAGES C)

# Configuración general
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# Configurar la ubicación del ejecutable (fuera de la carpeta build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Incluir directorios comunes (para los encabezados)
include_directories(
    /home/Miyo/raylib/src
    /home/Miyo/glfw/include/GLFW
    ${CMAKE_SOURCE_DIR}/include  # Incluye tu carpeta "include"
    .  # Incluir el directorio actual (por si hay otros encabezados en el mismo directorio)
)

# Archivos fuente
set(SOURCES
    main.c
    config.c
    src/gamelogic.c
    graphics_storage.c
    src/jugador.c
    src/record.c
    src/scoreboard.c
)

# Agregar el ejecutable
add_executable(blackjackFull ${SOURCES})

# Incluir las rutas de las bibliotecas para el enlazado
link_directories(
    /home/Miyo/glfw/build/src  # Donde se encuentran las bibliotecas de glfw
    /home/Miyo/raylib/src  # Donde se encuentran las bibliotecas de raylib
    /usr/local/lib  # Ruta común para las bibliotecas del sistema
)

# Agregar las bibliotecas necesarias
target_link_libraries(blackjackFull
    raylib
    glfw3
    gdi32  # Solo para Cygwin
)

# Opciones adicionales del compilador (deberías usar CMAKE_C_FLAGS para agregar flags)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -O2")
