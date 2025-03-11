#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "../headers/estructuras.h"

void obtenerFechaActual(FechaCreacion* fechaActual);
void escribirCompraEnArchivo(Transacciones*);
void guardarCompra(Datos datosCompra);
void cantidadLineasArchivo(int*);

#endif
