#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "../headers/estructuras.h"

void obtenerFechaActual(FechaCreacion* fechaActual);
void escribirCompraEnArchivo(Transacciones* transaccion);
void leerArchivo(Transacciones**, int*);
void guardarCompra(Datos datosCompra);
void limpiarArchivo();
void obtenerTamArchivo(const char*, int*);

#endif
