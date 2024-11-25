# Variables
CC = gcc
CFLAGS = -Wall -std=c11 -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -I./include -I. -static -O2
LDFLAGS = -L/home/Miyo/glfw/build/src -L/home/Miyo/raylib/src -L/usr/local/lib
LIBS = -lraylib -lglfw3 -lgdi32

# Archivos fuente
SRCS = main.c config.c src/gamelogic.c graphics_storage.c src/jugador.c src/record.c src/scoreboard.c

# Nombre del archivo ejecutable
TARGET = blackjackFull

# Reglas principales
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $@ $(SRCS) $(CFLAGS) $(LDFLAGS) $(LIBS)

# Limpia los archivos generados
clean:
	rm -f $(TARGET)

# Recompila todo desde cero
rebuild: clean all
