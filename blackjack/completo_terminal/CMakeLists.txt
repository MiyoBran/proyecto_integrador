cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(blackjack_terminal VERSION 1.0 LANGUAGES C)

# Configuración general
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# Configurar la ubicación del ejecutable (fuera de la carpeta build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Incluir directorios
include_directories(include)

# Archivos fuente
set(SOURCES
    main.c
    src/config.c
    src/jugador.c
    src/logica.c
    src/mazo.c
    src/record.c
    src/scoreboard.c
)

# Agregar el ejecutable
add_executable(blackjack ${SOURCES})

# Configuración para Cygwin (opcional)
if(CYGWIN)
    message(STATUS "Configuración para Cygwin detectada")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -O2")
endif()
