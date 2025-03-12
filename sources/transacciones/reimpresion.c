#include <ctype.h>
#include <stdio.h>
#include "../../headers/operaciones.h"
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void reimprimir()
{
    int cantidadLineas;
    cantidadLineasArchivo(&cantidadLineas);
    if (cantidadLineas==-1)
    {
        return;
    }

    if (cantidadLineas == 0)
    {
        printf("********************** REIMPRESION **********************\n\n");
        printf("Aun no se han realizado transacciones.\n");
        printf("\nPresiona una tecla para continuar...");
        getch();
        return;
    }

    FILE* file = fopen("../output/Transacciones.dat", "r");
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

    int j = cantidadLineas - 1;

    while (1)
    {
        system("cls");
        printf("********************** REIMPRESION **********************\n\n\n");

        printf("%-4s | %-13s | %-26s | %-16s | %-4s | %-7s | %-19s | %-8s\n",
               "Ref", "Monto", "Tipo Tarjeta", "PAN", "CVV", "Expira", "Creacion", "Estado");
        printf(
            "---------------------------------------------------------------------------------------------------------------------\n");


        //-------------------------------------------------------------------------------------
        int referencia;
        float monto;
        char tipoT[27], pan[17], cvv[5], expira[8], creacion[20], hora[20], estado[8];

        sscanf(transacciones[j], "%d | %f | %[^|] | %s | %s | %s | %s %s | %s",
                       &referencia, &monto, tipoT, pan, cvv, expira, creacion, hora, estado);

        char panEnmascarado[17];
        for (int p = 0; p < strlen(pan); p++)
        {
            if ((p>=4)&&(p<(strlen(pan)-4)))
            {
                panEnmascarado[p] = '*';
                continue;
            }
            panEnmascarado[p] = pan[p];
        }

        panEnmascarado[strlen(pan)] = '\0';

        printf("%-4d | %-13.2f | %-26s | %-16s | %-4s | %s | %s %s | %s \n\n",
       referencia, monto, tipoT, panEnmascarado, cvv, expira, creacion,hora, estado);

        //-------------------------------------------------------------------------------------

        if (j < cantidadLineas - 1)
        {
            printf("Presiona 'A' para ver la transaccion anterior.\n");
        }
        if (j > 0)
        {
            printf("Presiona 'D' para ver la siguiente transaccion.\n");
        }
        printf("Presiona 'ESC' para salir.\n");

        const char tecla = (char)getch();

        if (tecla == 'a' || tecla == 'A')
        {
            if (j < cantidadLineas - 1)
            {
                j++;
            }
        }
        else if (tecla == 'd' || tecla == 'D')
        {
            if (j > 0)
            {
                j--;
            }
        }
        else if (tecla == 27)
        {
            break;
        }
    }
}


