#include "../../headers/headersTransaciones/anulacion.h"
#include "../../headers/operaciones.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void anularCompra()
{
    {
        printf("********************** ANULACION **********************\n\n");
        int cantidadLineas;
        cantidadLineasArchivo(&cantidadLineas);

        if (cantidadLineas == 0)
        {
            printf("Aun no se han realizado transacciones.\n");
            return;
        }

        FILE* file = fopen("../output/Transacciones.txt", "r");
        if (!file)
        {
            printf("Error al abrir el archivo.\n");
            return;
        }

        char transacciones[cantidadLineas][120];
        char linea[120];
        int i = 0;

        while (i < (cantidadLineas) && fgets(linea, sizeof(linea), file) != NULL)
        {
            strcpy(transacciones[i], linea);
            i++;
        }

        fclose(file);
    }
}
