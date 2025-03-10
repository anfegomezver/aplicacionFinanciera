#include "../headers/headersTransaciones/compra.h"
#include "../headers/headersTransaciones/anulacion.h"
#include "../headers/headersTransaciones/cierre.h"
#include "../headers/headersTransaciones/reimpresion.h"
#include "../headers/headersTransaciones/reporteTotal.h"
#include "../headers/operaciones.h"
#include "../headers/menu.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

void menu()
{
    short opcion;
    do
    {
        printf(
            "************ MENU ************\n\n1 - Compra\n2 - Anulacion\n3 - Cierre \n4 - Reimpresion\n5 - Reporte total\n6 - Salir\n\n******************************\n\nIngrese una opcion del menu: ");
        scanf("%hd", &opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            system("cls");
            crearCompra();
            printf("\nPresiona una tecla para continuar...");
            getch();
            system("cls");
            break;
        case 2:
            system("cls");
            //anularCompra();
            printf("\nPresiona una tecla para continuar...");
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            //cerrar();


            break;
        case 4:
            system("cls");
            //reimprimir();
            printf("\nPresiona una tecla para continuar...");
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            printf("******** REPORTE TOTAL ********\n\n");
            //crearReporteTotal();
            printf("\nPresiona una tecla para continuar...");
            getch();
            system("cls");
            break;
        case 6:
            system("cls");
            break;
        default:
            system("cls");
            printf("********************************\n\n");
            printf("Opcion no valida\n");
            printf("\nPresiona una tecla para continuar...");
            getch();
            system("cls");
        }
    }
    while (opcion != 6);

    printf("Fin del programa.\n\n\nIngrese cualquier tecla para cerrar esta ventana...");
    getch();
}
