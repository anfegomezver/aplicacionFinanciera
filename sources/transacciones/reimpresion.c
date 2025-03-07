#include "../../headers/headersTransaciones/reimpresion.h"
#include "../../headers/operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reimprimir(){

    Transacciones *transacciones = NULL;
    int numTransacciones;

    leerArchivo(&transacciones, &numTransacciones);
    printf("Numero total compras: %d\n", numTransacciones);

    if (transacciones != NULL && numTransacciones > 0) {
        for (int i = numTransacciones - 1; i >= 0; i--) {
            printf("%hd | %.2f | %s | %s | %02d/%02d/%04d %02d:%02d:%02d | %s\n",
                        transacciones[i].referencia,
                        transacciones[i].datos.monto,
                        transacciones[i].datos.pan,
                        transacciones[i].datos.cvv,
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
    }
}