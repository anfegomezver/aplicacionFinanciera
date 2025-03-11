#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "headersTransaciones/compra.h"

typedef struct
{
    short dia;
    short mes;
    short anio;
    short hora;
    short minuto;
    short segundo;
} FechaCreacion;

typedef struct Transacciones
{
    int referencia;
    char estado[8];
    Datos datos;
    FechaCreacion creacion;
} Transacciones;

#endif
