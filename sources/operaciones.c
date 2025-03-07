#include "../headers/operaciones.h"
#include "../headers/estructuras.h"
#include "../headers/headersTransaciones/compra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "conio.h"

#include "../headers/menu.h"

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

void escribirCompraEnArchivo(Transacciones* transaccion)
{
  FILE* archivoTransacciones = fopen("../output/Transacciones.txt", "a");

  if (!archivoTransacciones)
  {
    printf("No se pudo abrir el archivo de compras para escritura\n");
    return;
  }

  fprintf(archivoTransacciones,
          "%hd | %.2f | %s | %s | %02d/%02d/%04d %02d:%02d:%02d | %s @\n",
          transaccion->referencia, transaccion->datos.monto,
          transaccion->datos.pan, transaccion->datos.cvv,
          transaccion->creacion.dia, transaccion->creacion.mes,
          transaccion->creacion.anio, transaccion->creacion.hora,
          transaccion->creacion.minuto, transaccion->creacion.segundo,
          transaccion->estado);

  fclose(archivoTransacciones);
}

void limpiarArchivo()
{
  FILE* file = fopen("../output/Transacciones.txt", "w");

  if (file == NULL)
  {
    printf("Error al abrir el archivo para limpiar\n");
    return;
  }

  fclose(file);
}

void obtenerTamArchivo(const char* ruta, int* contador)
{
  FILE* file = fopen(ruta, "r");
  if (!file)
  {
    printf("Error al abrir el archivo\n");
    *contador = 0;
    return;
  }

  *contador = 0;
  char c;
  while ((c = fgetc(file)) != EOF)
  {
    if (c == '@')
    {
      (*contador)++;
    }
  }
  fclose(file);
}

void leerArchivo(Transacciones** transacciones, int* cont)
{
  const char* ruta = "../output/Transacciones.txt";

  obtenerTamArchivo(ruta, cont);

  if (*cont == 0)
  {
    printf("No hay transacciones realizadas.\n");
  }

  FILE* file = fopen(ruta, "r");
  if (!file)
  {
    printf("Error al abrir el archivo.\n");
    return;
  }

  *transacciones = malloc(*cont * sizeof(Transacciones));
  if (!*transacciones)
  {
    printf("Error al asignar memoria\n");
    fclose(file);
    return;
  }

  char linea[80];
  for (int i = 0; i < *cont; i++)
  {
    if (fgets(linea, sizeof(linea), file) != NULL)
    {
      sscanf(linea, "%hd | %f | %s | %s | %d/%d/%d %d:%d:%d | %s @",
             &(*transacciones)[i].referencia, &(*transacciones)[i].datos.monto,
             (*transacciones)[i].datos.pan, (*transacciones)[i].datos.cvv,
             &(*transacciones)[i].creacion.dia,
             &(*transacciones)[i].creacion.mes,
             &(*transacciones)[i].creacion.anio,
             &(*transacciones)[i].creacion.hora,
             &(*transacciones)[i].creacion.minuto,
             &(*transacciones)[i].creacion.segundo, (*transacciones)[i].estado);
    }
  }
  fclose(file);
}

void guardarCompra(Datos datosCompra)
{
  int contador;
  obtenerTamArchivo("../output/Transacciones.txt", &contador);
  contador += 1;

  Transacciones* nuevaTransaccion = malloc(sizeof(Transacciones));
  if (!nuevaTransaccion)
  {
    printf("Error al asignar memoria\n");
    return;
  }

  nuevaTransaccion->referencia = contador;
  strcpy(nuevaTransaccion->estado, "Compra");
  nuevaTransaccion->datos = datosCompra;
  obtenerFechaActual(&nuevaTransaccion->creacion);

  escribirCompraEnArchivo(nuevaTransaccion);

  free(nuevaTransaccion);
}
