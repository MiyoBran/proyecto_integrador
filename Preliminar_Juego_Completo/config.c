#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 256


/*De semana 11 git materia lo que esta en el .env, se saca con esta funcion */
char* getconfig(const char *clave) {
    FILE *archivo = fopen(".env", "r"); //<- si hago un archivo txt tengo que cambiar aca el nombre
    if (archivo == NULL) {
        printf("Error al abrir el archivo de configuración.\n");
        return NULL;
    }

    char linea[MAX_LINEA];
    char *valor = NULL;

    while (fgets(linea, sizeof(linea), archivo) && valor == NULL) {
        // Verifica si la línea contiene la clave buscada
        if (strncmp(linea, clave, strlen(clave)) == 0) {
            // Busca el caracter '=' en la línea
            char *igual = strchr(linea, '=');
            if (igual != NULL) {
                // El valor está después del símbolo '='
                valor = strdup(igual + 1);
                
                // Eliminar salto de línea si lo hay
                valor[strcspn(valor, "\n")] = '\0';
            }
        }
    }

    fclose(archivo);
    return valor;
}
