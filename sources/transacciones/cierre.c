#include "../../headers/headersTransaciones/cierre.h"
#include "../../headers/operaciones.h"
#include "../../headers/headersTransaciones/reporteTotal.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cerrar()
{
    FILE* file = fopen("../output/Transacciones.txt", "r");
    if (!file)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("********************** CIERRE **********************\n\n");


    int cantidadLineas;
    cantidadLineasArchivo(&cantidadLineas);

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
        total += monto;
        if (strcmp(estado, "Compra") == 0)
        {
            cantCompras++;
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

    char opcion[3];
    printf("\nDesea realizar el cierre? \n1 - Si\n2 - No\n\nIngrese una opcion: ");
    scanf("%s", &opcion);
    while (getchar() != '\n');
    if ((int)strlen(opcion) != 1)
    {
        opcion[0] = 'x';
    }
    switch (opcion[0])
    {
    case '1':
        FILE* file2 = fopen("../output/Transacciones.txt", "w");

        if (file2 == NULL)
        {
            printf("Error al abrir el archivo.\n");
            return;
        }

        fclose(file);

        printf("\nCIERRE REALIZADO CORRECTAMENTE.\n");
        return;
    case '2': printf("\nVolveras al menu principal.\n");
        return;
    default: printf("\nOpcion no valida.\n");
    }
}
