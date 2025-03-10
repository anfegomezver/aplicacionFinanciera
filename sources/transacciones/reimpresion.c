#include "../../headers/headersTransaciones/reimpresion.h"
#include "../../headers/operaciones.h"
#include <stdio.h>
#include <stdlib.h>

void reimprimir()
{
    Transacciones* transacciones = NULL;
    int numTransacciones;

    system("cls");
    printf("********** REIMPRESION **********\n\n");
    leerArchivo(&transacciones, &numTransacciones);

    printf("Cantidad de transacciones: %d", numTransacciones);
    char digitosTrajeta[5];
    if (transacciones != NULL && numTransacciones > 0)
    {
        for (int i = numTransacciones - 1; i >= 0; i--)
        {
            for (int j = 0; j < 4; j++)
            {
                digitosTrajeta[j] = transacciones[i].datos.pan[12 + j];
            }

            printf("\n\n-------------------------------------------------------\n\n");
            printf(
                "Referencia: %hd\nMonto: $%.2f\nPAN: **** **** **** %s\nCCV: %s\nFecha tarjeta: %s/%s\nFecha y hora de la transaccion: %02d/%02d/%04d %02d:%02d:%02d\nEstado: %s",
                transacciones[i].referencia,
                transacciones[i].datos.monto,
                digitosTrajeta,
                transacciones[i].datos.cvv,
                transacciones[i].datos.fecha.mes,
                transacciones[i].datos.fecha.anio,
                transacciones[i].creacion.dia,
                transacciones[i].creacion.mes,
                transacciones[i].creacion.anio,
                transacciones[i].creacion.hora,
                transacciones[i].creacion.minuto,
                transacciones[i].creacion.segundo,
                transacciones[i].estado
            );
        }
        free(transacciones);
        printf("\n\n-------------------------------------------------------\n\n");
    }
}
