#include "../../headers/headersTransaciones/anulacion.h"
#include "../../headers/operaciones.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void anularCompra() {

  Transacciones *transacciones = NULL;
  int numTransacciones;

  leerArchivo(&transacciones, &numTransacciones);

  if (transacciones == NULL || numTransacciones == 0) {
    printf("No hay transacciones registradas.\n");
    return;
  }

  char ultimosDigitos[5], cvv[4], referenciaStr[3];

  printf("Ingrese el número de referencia de la compra a anular: ");
  scanf("%2s", referenciaStr);
  fflush(stdin);
  if (validarTamano(referenciaStr, 2) || validarCaracteres(referenciaStr)) {
    printf("Referencia inválida.\n");
    return;
  }
  int referencia = atoi(referenciaStr);
  if (referencia > numTransacciones) {
    printf("Referencia no encontrada.\n");
    return;
  }

  printf("Ingrese los últimos 4 dígitos de la tarjeta: ");
  scanf("%4s", ultimosDigitos);
  fflush(stdin);
  if (validarTamano(ultimosDigitos, 4) || validarCaracteres(ultimosDigitos)) {
    printf("Dígitos de tarjeta inválidos.\n");
    return;
  }

  printf("Ingrese el CVV: ");
  scanf("%3s", cvv);
  fflush(stdin);
  if (validarTamano(cvv, 3) || validarCaracteres(cvv)) {
    printf("CVV inválido.\n");
    return;
  }


}
