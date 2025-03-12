#include <stdio.h>
#include "../../headers/headersTransaciones/compra.h"
#include "../../headers/operaciones.h"
#include "../../headers/estructuras.h"
#include <stdlib.h>
#include <string.h>

void crearCompra()
{
	printf("********************** COMPRA **********************\n\n");

	Datos* datos = malloc(sizeof(Datos));


	int limiteCompras = 20;
	int cantidadLineas;
	cantidadLineasArchivo(&cantidadLineas);

	if (cantidadLineas==-1)
	{
		return;
	}

	if (cantidadLineas > limiteCompras)
	{
		printf("Limite de compras alcanzado.\n");
		return;
	}

	//Ingresar monto

	char monto[15];

	printf("Ingrese el monto: ");
	scanf("%14s", monto);

	while (getchar() != '\n');

	int contadorPunto = 0;
	int posicionPunto = -1;

	if ((monto[0] == '0' && monto[1] != '.' && monto[1] != '\0') || monto[0] == '.')
	{
		printf("\nValor no permitido.\n");
		return;
	}

	for (int i = 0; i < ((int)(strlen(monto))); i++)
	{
		if ((monto[i] < '0' || monto[i] > '9') && monto[i] != '.')
		{
			printf("\nCaracteres invalidos.\n");
			return;
		}
		else if (monto[i] == '.')
		{
			contadorPunto++;
			if (contadorPunto >= 2)
			{
				printf("\nCaracteres invalidos.\n");
				return;
			}
			posicionPunto = i;
		}
	}

	if (contadorPunto == 0)
	{
		posicionPunto = strlen(monto);
	}

	if ((contadorPunto == 0 && strlen(monto) > 10) || (contadorPunto == 1 && posicionPunto > 11))
	{
		printf("\nTamano no permitido.\n");
		return;
	}

	datos->monto = atof(monto);


	//Ingresar PAN

	char pan[18];
	int cantDigitosCvv = 3;
	char tipoT[27];

	printf("\nIngrese el pan de la tarjeta: ");
	scanf("%17s", pan);

	while (getchar() != '\n');
	if (validarCaracteres(pan))
	{
		printf("\nCaracter invalido.\n");
		return;
	}
	else if (tipoTarjeta(pan, &cantDigitosCvv, tipoT) == 0)
	{
		return;
	}

	strcpy(datos->pan, pan);
	strcpy(datos->tipoT, tipoT);
	printf("\nTipo de tarjeta: %s\n", tipoT);

	//Ingresar cvv

	char cvv[5];

	printf("\nIngrese el cvv de la tarjeta: ");
	scanf("%4s", cvv);
	while (getchar() != '\n');

	if (strlen(cvv) != cantDigitosCvv)
	{
		printf("\nTamano no permitido.\n");
		return;
	}

	if (validarCaracteres(cvv))
	{
		printf("\nCaracter invalido.\n");
		return;
	}

	strcpy(datos->cvv, cvv);

	//Ingresar fecha

	FechaTarjeta* fechaTarjeta = malloc(sizeof(FechaTarjeta));

	char anio[6];
	char mes[4];

	printf("\nIngrese el mes (Ejm: 01,02, ... , 12): ");
	scanf("%3s", mes);
	while (getchar() != '\n');

	if ((int)strlen(mes) != 2)
	{
		printf("\nTamano no permitido.\n");
		return;
	}

	if (validarCaracteres(mes))
	{
		printf("\nCaracter invalido.\n");
		return;
	}

	if (atoi(mes) > 12 || atoi(mes) == 0)
	{
		printf("\nRango no permitido.\n");
		return;
	}

	printf("\nIngrese el anio (4 digitos): ");
	scanf("%5s", anio);
	while (getchar() != '\n');

	if (validarCaracteres(anio))
	{
		printf("\nCaracter invalido.\n");
		return;
	}

	if ((int)strlen(anio) != 4)
	{
		printf("\nTamano no permitido.\n");
		return;
	}

	if (atoi(anio) < 2000 || atoi(anio) > 2300)
	{
		printf("\nRango no permitido.\n");
		return;
	}

	if (esValidaTarjeta(mes, anio))
	{
		return;
	}
	strcpy(fechaTarjeta->mes, mes);
	strcpy(fechaTarjeta->anio, anio);

	strcpy(datos->fecha.mes, fechaTarjeta->mes);
	strcpy(datos->fecha.anio, fechaTarjeta->anio);

	guardarCompra(*datos);

	printf("\nCOMPRA REGISTRADA EXITOSAMENTE.\n");

	free(fechaTarjeta);
	free(datos);
}

//Validaciones de tarjeta

int esValidaTarjeta(char* mes, char* anio)
{
	FechaCreacion fechaActual;
	obtenerFechaActual(&fechaActual);

	int anioActual = fechaActual.anio;
	int mesActual = fechaActual.mes;

	int mesT = atoi(mes);
	int anioT = atoi(anio);

	if (anioT < anioActual)
	{
		printf("\nFecha no valida.\n");
		return 1;
	}

	if (anioT == anioActual && mesT < mesActual)
	{
		printf("\nFecha no valida.\n");
		return 1;
	}

	return 0;
}

int esReal(int cantidadCaracteres, char* pan)
{
	int numerosTarjeta[cantidadCaracteres];

	for (int i = 0; i < cantidadCaracteres; i++)
	{
		numerosTarjeta[i] = pan[i] - '0';
	}

	int sum = 0;
	int aux = 0;

	for (int i = 0; i < cantidadCaracteres; i++)
	{
		int index = cantidadCaracteres - 1 - i;
		int valor = numerosTarjeta[index];

		if (i % 2 == 1)
		{
			aux = valor * 2;
			sum += (aux / 10) + (aux % 10);
		}
		else
		{
			sum += valor;
		}
	}
	return (sum % 10 == 0) ? 1 : 0;
}

int tipoTarjeta(char* pan, int* cantCvv, char* tipoT)
{
	int cantidadCaracteres = strlen(pan);

	char digitosTarjeta[5];

	for (int i = 0; i < 4; i++)
	{
		digitosTarjeta[i] = pan[i];
	}

	int digitos = atoi(digitosTarjeta);

	switch (cantidadCaracteres)
	{
	case 14:
		digitos = digitos / 10;
		if ((digitos >= 300 && digitos <= 305) || (digitos == 309) || ((digitos / 10) == 36) || ((digitos / 10) == 38)
			|| ((digitos / 10) == 39))
		{
			if (esReal(cantidadCaracteres, pan))
			{
				strcpy(tipoT, "Diners Club International");
				return 1;
			}
		}
		printf("\nTarjeta no valida.\n");
		return 0;
	case 15:


		if ((digitos / 100 == 37) || (digitos / 100 == 34))
		{
			if (esReal(cantidadCaracteres, pan))
			{
				strcpy(tipoT, "American Express");
				*cantCvv = 4;
				return 1;
			}
		}
		printf("\nTarjeta no valida.\n");
		return 0;
	case 16:
		if (digitos / 1000 == 4)
		{
			if (esReal(cantidadCaracteres, pan))
			{
				strcpy(tipoT, "Visa");
				return 1;
			}
		}
		else if (((digitos / 100) >= 51 && (digitos / 100) <= 55) || ((digitos) >= 2221 && (digitos) <= 2720))
		{
			if (esReal(cantidadCaracteres, pan))
			{
				strcpy(tipoT, "Mastercard");
				return 1;
			}
		}
		printf("\nTarjeta no valida.\n");
		return 0;
	default: printf("\nTamano no permitido.\n");
		return 0;
	}
}

int validarCaracteres(char* cadena)
{
	for (int i = 0; cadena[i] != '\0'; i++)
	{
		if (cadena[i] < '0' || cadena[i] > '9')
		{
			return 1;
		}
	}
	return 0;
}
