gcc -o main main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lglfw -lgdi32 graphics_storage.c

/*Para miyo, solo lo de Miyo*/
gcc -o main main.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lglfw -lgdi32 graphics_storage.c

/// PARA COMPILAR TODOS LOS ARCHIVOS Y PROBAR / CAMBIAR EL Miyo ---> Tu nombre de carpeta
gcc -o juegocompleto main.c graphics_storage.c files2.c gamelogic.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW -L/home/Miyo/raylib/src -L/home/Miyo/glfw/build/src -lraylib -lglfw -lgdi32

/* para compilar solo gamelogic
gcc -o test_gamelogic test_gamelogic.c gamelogic.c -I/home/Miyo/raylib/src -I/home/Miyo/glfw/include/GLFW
