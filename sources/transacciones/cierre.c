#include "../../headers/headersTransaciones/cierre.h"
#include "../../headers/operaciones.h"
#include "../../headers/headersTransaciones/reporteTotal.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>

void cerrar()
{
    const char* ruta = "../output/Transacciones.txt";
    int cont;
    obtenerTamArchivo(ruta, &cont);
    char opcion;
    printf("************ CIERRE *************\n\n");
    crearReporteTotal();
    printf("\nPresiona una tecla para continuar...");
    getch();

    system("cls");
    printf("************ CIERRE *************\n\n");

    if (cont!=0)
    {
        printf(
        "Estas seguro de que quieres realizar el cierre?\n\n1: Si, estoy seguro\n2: No, no estoy seguro\n\nIngrese una opcion: ");
        scanf("%c", &opcion);
        fflush(stdin);
        system("cls");
        printf("************ CIERRE *************\n\n");
        switch (opcion)
        {
        case '1':
            limpiarArchivo();

            printf("Se borro el historico de transacciones.\n");
            break;
        case '2':
            printf("Volviendo al menu...\n");

            return;
        default: printf("Opcion incorrecta.\n");
        }
    }

}
