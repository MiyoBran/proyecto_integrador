#ifndef ARCHIVO_CONFIGURACION_H
#define ARCHIVO_CONFIGURACION_H

typedef struct
{
    int ranking;
    char name[50];
    float money;
} Jugador;



char* obtenerValorConfiguracion(const char *clave);
void mostrarJugadores(Jugador scoreList[TOTAL_REGISTROS]);

#endif // ARCHIVO_CONFIGURACION_H
