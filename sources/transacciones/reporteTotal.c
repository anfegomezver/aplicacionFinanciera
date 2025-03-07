#include "../../headers/headersTransaciones/reporteTotal.h"
#include "../../headers/estructuras.h"
#include "../../headers/operaciones.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearReporteTotal() {
  Transacciones *transacciones = NULL;
  int numTransacciones;
  int contadorCompra = 0, contadorAnulacion = 0;
  float montoTotal = 0;

  leerArchivo(&transacciones, &numTransacciones);

  if (transacciones != NULL && numTransacciones > 0) {
    for (int i = 0; i < numTransacciones; i++) {
      if (strcmp(transacciones[i].estado, "Compra") == 0){
        contadorCompra++;
        montoTotal += transacciones[i].datos.monto;
      } else {
        contadorAnulacion++;
      }
      printf("Estado: '%s'\n", transacciones[i].estado);

    }
  }
  if (transacciones != NULL) {
    printf("La cantidad de transacciones guardadas son: %d\n", numTransacciones);
    printf("De esas transacciones hay %d compras.\n", contadorCompra);
    printf("El monto total de las compras es: %.2f\n", montoTotal);
    printf("Y de esas transacciones hay %d anulaciones.\n", contadorAnulacion);
    free(transacciones);
  }

  return;
}