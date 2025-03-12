#include "../../headers/headersTransaciones/reporteTotal.h"
#include "../../headers/operaciones.h"
#include <stdio.h>
#include <string.h>

void crearReporteTotal()
{
    FILE* file = fopen("../output/Transacciones.dat", "r");
    if (!file)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("********************** REPORTE TOTAL **********************\n\n");


    int cantidadLineas;
    cantidadLineasArchivo(&cantidadLineas);

    if (cantidadLineas==-1)
    {
        return;
    }

    if (cantidadLineas == 0)
    {
        printf("Aun no se han realizado transacciones.\n");
        return;
    }

    float monto;
    char estado[20];

    float total = 0;
    int cantCompras = 0;
    int cantAnulaciones = 0;

    while (fscanf(file, "%*d | %f | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*d/%*d/%*d %*d:%*d:%*d | %s",
                  &monto, estado) == 2)
    {

        if (strcmp(estado, "Compra") == 0)
        {
            cantCompras++;
            total += monto;
        }
        else
        {
            cantAnulaciones++;
        }
    }

    fclose(file);

    printf("Transacciones realizadas: %d\n", cantidadLineas);
    printf("\nCantidad de compras: %d\n", cantCompras);
    printf("\nCantidad de anulaciones: %d\n", cantAnulaciones);
    printf("\nTotal en compras: $%.2f\n", total);
}
