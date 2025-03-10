#include "../../headers/headersTransaciones/anulacion.h"
#include "../../headers/operaciones.h"
#include "../../headers/validaciones.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void anularCompra()
{
  Transacciones* transacciones = NULL;
  int numTransacciones;


  system("cls");
  printf("*********** ANULACION ************\n\n");

  leerArchivo(&transacciones, &numTransacciones);

  char ultimosDigitos[5], cvv[4], referenciaStr[3];


  printf("Ingrese el numero de referencia de la compra a anular: ");
  scanf("%2s", referenciaStr);
  fflush(stdin);
  if (validarCaracteres(referenciaStr))
  {
    system("cls");
    printf("*********** ANULACION ************\n\n");
    printf("Referencia invalida.\n");
    return;
  }
  int referencia = atoi(referenciaStr);
  if (referencia > numTransacciones)
  {
    system("cls");
    printf("*********** ANULACION ************\n\n");
    printf("Referencia no encontrada.\n");
    return;
  }
  system("cls");
  printf("*********** ANULACION ************\n\n");
  printf("Ingrese los ultimos 4 digitos de la tarjeta: ");
  scanf("%4s", ultimosDigitos);
  fflush(stdin);
  if (validarTamano(ultimosDigitos, 4) || validarCaracteres(ultimosDigitos))
  {
    system("cls");
    printf("*********** ANULACION ************\n\n");
    printf("Digitos de tarjeta invalidos.\n");
    return;
  }
  char digitosTrajeta[5];
  for (int i = 0; i < 4; i++)
  {
    digitosTrajeta[i] = transacciones[referencia - 1].datos.pan[12 + i];
  }

  if (!(strcmp(digitosTrajeta, ultimosDigitos) == 0))
  {
    system("cls");
    printf("*********** ANULACION ************\n\n");
    printf("No hay coincidencias.\n");
    return;
  }
  system("cls");
  printf("*********** ANULACION ************\n\n");

  printf("Ingrese el CVV: ");
  scanf("%3s", cvv);
  fflush(stdin);
  if (validarTamano(cvv, 3) || validarCaracteres(cvv))
  {
    system("cls");
    printf("*********** ANULACION ************\n\n");
    printf("CVV inválido.\n");
    return;
  }
  if (!(strcmp(cvv, transacciones[referencia - 1].datos.cvv) == 0))
  {
    system("cls");
    printf("*********** ANULACION ************\n\n");
    printf("No hay coincidencias.\n");
    return;
  }

  strcpy(transacciones[referencia - 1].estado, "Anulado");

  limpiarArchivo();
  for (int i = 0; i < numTransacciones; i++)
  {
    escribirCompraEnArchivo(&transacciones[i]);
  }
  system("cls");
  printf("*********** ANULACION ************\n\n");
  printf("COMPRA ANULADA EXITOSAMENTE\n");
}
