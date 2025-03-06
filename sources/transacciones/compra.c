#include <stdio.h>
#include "../../headers/headersTransaciones/compra.h"
#include "../../headers/operaciones.h"
#include "../../headers/validaciones.h"
#include "../../headers/estructuras.h"
#include <stdlib.h>
#include <string.h>

void crearCompra()
{

	Datos *datos = malloc(sizeof(Datos));
	FechaTarjeta *fechaTarjeta = malloc(sizeof(FechaTarjeta));

	char monto[11];

	printf("Ingrese el monto(Solo se toman en cuenta 2 cifras decimales.\n MAX 7 cifras ejm:xxxxxxx.xx):\n");
	scanf("%10s", monto);

	fflush(stdin);

	short contadorPunto = 0;
	short posicionPunto;
	short puntoAlFinal = 0;
	for (int i = 0; i < ((int)(strlen(monto))); i++)
	{
		if ((monto[i] < '0' || monto[i] > '9') && monto[i] != '.')
		{

			printf("Caracteres invalidos\n");
			return;
		}
		else if (monto[i] == '.')
		{
			contadorPunto++;
			posicionPunto = i;
		}
		else if (i == ((int)(strlen(monto) - 1)))
		{
			posicionPunto = i;
		}
		if ('.' == monto[((int)(strlen(monto) - 1))])
		{
			puntoAlFinal = 1;
		}
		if (contadorPunto >= 2)
		{
			printf("Caracteres invalidos\n");
			return;
		}
	}
	if (contadorPunto == 0 && strlen(monto) > 7) {
        printf("Tamano no permitido\n");
        return;
    }

	if (posicionPunto == ((int)(strlen(monto) - 1)))
	{
		datos->monto = atof(monto);
	}
	else if (posicionPunto > 6)
	{
		printf("Tamano no permitido\n");
		return;
	}
	else if (puntoAlFinal)
	{
		char cadenaMonto[posicionPunto - 1];
		for (int i = 0; i < posicionPunto - 1; i++)
		{
			cadenaMonto[i] = monto[i];
		}
		datos->monto = atof(cadenaMonto);
	}
	else
	{
		char cadenaMonto[posicionPunto + 2];
		for (int i = 0; i < posicionPunto + 2; i++)
		{
			cadenaMonto[i] = monto[i];
		}
		datos->monto = atof(cadenaMonto);
	}

	printf("Ingrese el PAN de la tarjeta (16 digitos)\nNOTA: Si sobrepasas el limite se tomaran los primeros 16 digitos:\n");
	scanf("%16s", datos->pan);

	fflush(stdin);
	if (validarCaracteres(datos->pan))
	{
		printf("Ingresaste un caracter invalido.\n");
		return;
	}
	else if (validarTamano(datos->pan, 16))
	{
		printf("El pan de la tarjeta esta incompleto.\n");
		return;
	}

	printf("Tu tarjeta registrada es: %s\n", datos->pan);

	printf("Ingrese el cvv de la tarjeta:\nNOTA: Si sobrepasas el limite se tomaran los primeros 3 digitos:\n");
	scanf("%3s", datos->cvv);

	fflush(stdin);

	if (validarCaracteres(datos->cvv))
	{
		printf("Ingresaste un caracter invalido.\n");
		return;
	}
	else if (validarTamano(datos->cvv, 3))
	{
		printf("El pan de la tarjeta esta incompleto.\n");
		return;
	}

	char anio[5];
	char mes[3];

	printf("A continuacion ingresara la fecha de vencimiento de la tarjeta\nIngrese el mes(en num ejm: 01,02):\n");
	scanf("%2s", mes);
	fflush(stdin);

	if (validarCaracteres(mes))
	{
		printf("Ingresaste un caracter invalido.\n");
		return;
	}
	else if (validarTamano(mes, 2))
	{
		printf("El mes esta incompleto.\n");
		return;
	}
	if (atoi(mes) > 12)
	{
		printf("El mes esta mal digitado.\n");
		return;
	}

	printf("Ingrese el anio(4 digitos):\n");
	scanf("%4s", anio);
	fflush(stdin);

	if (validarCaracteres(anio))
	{
		printf("Ingresaste un caracter invalido.\n");
		return;
	}
	else if (validarTamano(anio, 4))
	{
		printf("El anio esta incompleto.\n");
		return;
	}
	if (atoi(anio) < 2000 || atoi(anio) > 2060)
	{
		printf("El anio esta mal digitado.\n");
		return;
	}


	if (esValidaTarjeta(mes,anio)){
		return;
	}
	strcpy(fechaTarjeta->mes, mes);
	strcpy(fechaTarjeta->anio, anio);

	guardarCompra(*datos);
	printf("COMPRA REGISTRADA\n");
}

int esValidaTarjeta(char *mes, char *anio) {

    FechaCreacion fechaActual;
    obtenerFechaActual(&fechaActual);

    int anioActual = fechaActual.anio;
    int mesActual = fechaActual.mes;

    int mesT = atoi(mes);
    int anioT = atoi(anio);

    if (anioT < anioActual) {
        printf("Tarjeta no valida: año menor al actual.\n");
        return 1;
    }

    if (anioT == anioActual && mesT < mesActual) {
        printf("Tarjeta no valida: mes menor al actual.\n");
        return 1;
    }

    printf("Tarjeta valida.\n");
    return 0;
}
