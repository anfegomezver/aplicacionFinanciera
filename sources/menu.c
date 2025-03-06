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

void menu(){

    short opcion;
    do{
        printf("Ingrese la operacion que desea realizar:\n1 - Compra\n2 - Anulacion\n3 - Cierre (Salir)\n4 - Reimpresion\n5 - Reporte total\n");
        scanf("%hd", &opcion);
        fflush(stdin);
        switch(opcion){
        case 1:
            system("cls");
            crearCompra();
            printf("Presiona una tecla para continuar...\n");
            getch();
            system("cls");
            break;
        case 2:
            system("cls");
            anularCompra();
            printf("Presiona una tecla para continuar...\n");
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            cerrar();
            printf("Presiona una tecla para continuar...\n");
            getch();
            system("cls");
            break;
        case 4:
            system("cls");
            reimprimir();
            printf("Presiona una tecla para continuar...\n");
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            crearReporteTotal();
            printf("Presiona una tecla para continuar...\n");
            getch();
            system("cls");
            break;
        default:
            system("cls");
            printf("opcion invalida\n");
            printf("Presiona una tecla para continuar...\n");
            getch();
            system("cls");
        }
    }while(opcion != 3);

    printf("Fin del programa.\n");
}