cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(crearScoreHistorial)

# Establecer el estándar de C
set(CMAKE_C_STANDARD 99)

# Incluir los directorios de encabezados
include_directories(include)

# Archivos fuente
set(SOURCES
    main.c
    src/config.c
    src/jugador.c
    src/record.c
    src/scoreboard.c
)

# Establecer la carpeta de salida del ejecutable como la raíz del proyecto
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Generar el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Incluir el módulo de CPack
include(CPack)

# Configurar el paquete instalable
set(CPACK_PACKAGE_NAME "CrearScoreHistorial")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Un programa para gestionar historial y puntuaciones")
set(CPACK_PACKAGE_VENDOR "Miyo")
set(CPACK_PACKAGE_CONTACT "miyenbrandolino@gmail.com")

# Configurar archivos que serán incluidos en el paquete
install(TARGETS crearScoreHistorial DESTINATION bin)
install(FILES datos_historial.dat datos_ranking.dat README.txt DESTINATION bin)
install(FILES .env DESTINATION bin)


# Generar un instalador para múltiples sistemas
set(CPACK_GENERATOR "ZIP;TGZ")
