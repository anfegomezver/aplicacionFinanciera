#include "../../headers/headersTransaciones/reporteTotal.h"
#include "../../headers/estructuras.h"
#include "../../headers/operaciones.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearReporteTotal()
{

  Transacciones* transacciones = NULL;
  int numTransacciones;
  int contadorCompra = 0, contadorAnulacion = 0;
  float montoTotal = 0;

  leerArchivo(&transacciones, &numTransacciones);

  if (transacciones != NULL && numTransacciones > 0)
  {
    for (int i = 0; i < numTransacciones; i++)
    {
      if (strcmp(transacciones[i].estado, "Compra") == 0)
      {
        contadorCompra++;
        montoTotal += transacciones[i].datos.monto;
      }
      else
      {
        contadorAnulacion++;
      }
    }
  }else
  {
    return;
  }
  if (transacciones != NULL)
  {
    printf("Cantidad de transacciones: %d\n\n", numTransacciones);
    printf("Cantidad de compras: %d\n\n", contadorCompra);
    printf("Monto total de compras: $%.2f\n\n", montoTotal);
    printf("Cantidad de anulaciones: %d \n", contadorAnulacion);
    free(transacciones);
  }
}
