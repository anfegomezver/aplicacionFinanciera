#include "../headers/operaciones.h"
#include "../headers/estructuras.h"
#include "../headers/headersTransaciones/compra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "conio.h"

void obtenerFechaActual(FechaCreacion* fechaActual)
{
  time_t tiempoActual = time(NULL);

  struct tm* infoTiempo = localtime(&tiempoActual);

  fechaActual->dia = infoTiempo->tm_mday;
  fechaActual->mes = infoTiempo->tm_mon + 1;
  fechaActual->anio = infoTiempo->tm_year + 1900;
  fechaActual->hora = infoTiempo->tm_hour;
  fechaActual->minuto = infoTiempo->tm_min;
  fechaActual->segundo = infoTiempo->tm_sec;
}

void cantidadLineasArchivo(int* lineas)
{
  FILE* file = fopen("../output/Transacciones.txt", "r");
  if (!file)
  {
    printf("\nError al abrir el archivo.\n");
    *lineas = 0;
    return;
  }

  *lineas = 0;

  int c;

  while ((c = fgetc(file)) != EOF)
  {
    if (c == '\n')
    {
      (*lineas)++;
    }
  }

  fclose(file);
}


void escribirCompraEnArchivo(Transacciones* transaccion)
{
  FILE* archivoTransacciones = fopen("../output/Transacciones.txt", "a");

  if (!archivoTransacciones)
  {
    printf("\nNo se pudo abrir el archivo de compras para escritura\n");
    return;
  }

  fprintf(archivoTransacciones,
          "%-4hd | %-13.2f | %-25s | %-16s | %-4s | %s/%s | %02d/%02d/%04d %02d:%02d:%02d | %s \n",
          transaccion->referencia, transaccion->datos.monto, transaccion->datos.tipoT,
          transaccion->datos.pan, transaccion->datos.cvv, transaccion->datos.fecha.mes, transaccion->datos.fecha.anio,
          transaccion->creacion.dia, transaccion->creacion.mes,
          transaccion->creacion.anio, transaccion->creacion.hora,
          transaccion->creacion.minuto, transaccion->creacion.segundo,
          transaccion->estado);

  fclose(archivoTransacciones);
}

void guardarCompra(Datos datosCompra)
{
  int cantidadLineas;
  cantidadLineasArchivo(&cantidadLineas);

  Transacciones* nuevaTransaccion = malloc(sizeof(Transacciones));
  if (!nuevaTransaccion)
  {
    printf("\nError al asignar memoria\n");
    return;
  }

  nuevaTransaccion->referencia = cantidadLineas + 1;
  strcpy(nuevaTransaccion->estado, "Compra");
  nuevaTransaccion->datos = datosCompra;
  obtenerFechaActual(&nuevaTransaccion->creacion);

  escribirCompraEnArchivo(nuevaTransaccion);

  free(nuevaTransaccion);
}
