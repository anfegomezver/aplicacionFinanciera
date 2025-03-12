#include "../../headers/headersTransaciones/anulacion.h"
#include "../../headers/operaciones.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>

void anularCompra()
{
    int cantidadLineas;
    cantidadLineasArchivo(&cantidadLineas);
    if (cantidadLineas==-1)
    {
        return;
    }

    if (cantidadLineas == 0)
    {
        printf("********************** ANULACION **********************\n\n");
        printf("Aun no se han realizado transacciones.\n");
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

    printf("********************** ANULACION **********************\n\n");

    int lisRef;
    char lisEstado[8];
    int contadorAnulaciones=0;

    for (int m = 0; m < cantidadLineas; m++)
    {
        sscanf(transacciones[m], "%d | %*f | %*[^|] | %*s | %*s | %*s | %*s %*s | %s",
                  &lisRef, lisEstado);



        if (strcmp(lisEstado, "Anulado")==0)
        {
            contadorAnulaciones++;
        }
    }
    if (contadorAnulaciones==cantidadLineas)
    {
        printf("No hay anulaciones por hacer.\n");
        return;
    }

    char referenciaBuscar[3];
    printf("\nIngrese la referencia de la transaccion: ");
    scanf("%2s", referenciaBuscar);

    if (strlen(referenciaBuscar) != 1)
    {
        printf("Tamano invalido.");
        return;
    }
    if (!isdigit(referenciaBuscar[0]))
    {
        printf("Caracter invalido.");
        return;
    }
    if ((atoi(referenciaBuscar))>cantidadLineas)
    {
        printf("Referencia invalida.");
        return;
    }



    int referencia;
    float monto;
    char tipoT[27], pan[17], cvv[5], expira[8], creacion[20], hora[20], estado[8];

    sscanf(transacciones[atoi(referenciaBuscar)-1], "%d | %f | %[^|] | %s | %s | %s | %s %s | %s",
                   &referencia, &monto, tipoT, pan, cvv, expira, creacion, hora, estado);

    if (strcmp(estado, "Anulado")==0)
    {
        printf("\nEsta transaccion ya se encuentra anulada.\n");
        return;
    }

    char ultimosDigitosIngresados[6];

    printf("\nIngrese los ultimos 4 digitos de la tarjeta: ");
    scanf("%s", ultimosDigitosIngresados);
    while (getchar() != '\n');

    if (strlen(ultimosDigitosIngresados) != 4)
    {
        printf("\nTamano no permitido.\n");
        return;
    }

    if (validarCaracteres(ultimosDigitosIngresados))
    {
        printf("\nCaracter invalido.\n");
        return;
    }

    char ultimosDigitos[5];
    int l=0;
    for (int q = (((int)strlen(pan))-4); q < (int)strlen(pan); q++)
    {
        ultimosDigitos[l] = pan[q];
        l++;
    }

    if (strcmp(ultimosDigitos, ultimosDigitosIngresados)==1)
    {
        printf("\nSin coincidencias.\n");
        return;
    }

    int cantDigitosCvv = strlen(cvv);

    char cvvIngresado[5];

    printf("\nIngrese el cvv de la tarjeta: ");
    scanf("%4s", cvvIngresado);
    while (getchar() != '\n');

    if (strlen(cvvIngresado) != cantDigitosCvv)
    {
        printf("\nTamano no permitido.\n");
        return;
    }

    if (validarCaracteres(cvvIngresado))
    {
        printf("\nCaracter invalido.\n");
        return;
    }

    if (strcmp(cvvIngresado, cvv)==1)
    {
        printf("\nSin coincidencias.\n");
        return;
    }





    strcpy(estado, "Anulado\0");

    char buffer[120];

    sprintf(buffer, "%-4d | %-13.2f | %-25s| %-16s | %-4s | %s | %s %s | %s \n",
            referencia, monto, tipoT, pan, cvv, expira, creacion, hora, estado);


    strcpy(transacciones[atoi(referenciaBuscar) - 1], buffer);

    //--------------------------------------------------------------------

    FILE* archivoTransacciones = fopen("../output/Transacciones.dat", "w");

    if (!archivoTransacciones)
    {
        printf("\nNo se pudo abrir el archivo.\n");
        return;
    }
    for (i = 0; i < cantidadLineas; i++)
    {
        fprintf(archivoTransacciones, "%s", transacciones[i]);

    }

    printf("\nANULACION EXITOSA.\n");
    fclose(archivoTransacciones);

}
