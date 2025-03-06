#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "../headers/estructuras.h"

extern void obtenerFechaActual(FechaCreacion *fechaActual);
extern void escribirCompraEnArchivo(Transacciones *transaccion);
extern void leerArchivo();
extern void guardarCompra(Datos datosCompra);

#endif
