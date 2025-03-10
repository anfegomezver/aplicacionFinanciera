#include <stdio.h>
#include "../../headers/headersTransaciones/compra.h"
#include "../../headers/operaciones.h"
#include "../../headers/validaciones.h"
#include "../../headers/estructuras.h"
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

void crearCompra(){

	printf("********************** COMPRA **********************\n\n");

	Datos* datos = malloc(sizeof(Datos));
	FechaTarjeta* fechaTarjeta = malloc(sizeof(FechaTarjeta));

	//Ingresar monto

	char monto[11];

	printf("Ingrese el monto (solo se toman en cuenta 2 cifras decimales. MAX 7 cifras ejm:xxxxxxx.xx): ");
	scanf("%10s", monto);
	fflush(stdin);

	short contadorPunto = 0;
	int posicionPunto =0;
	int puntoAlFinal = 0;

	//Validar caracteres del monto
	for (int i = 0; i < ((int)(strlen(monto))); i++){
		if (!isdigit(monto[i]) && monto[i] != '.') {
			printf("\n\nCaracteres invalidos.\n");
			return;
		}
		else if (monto[i] == '.'){
			contadorPunto++;
			posicionPunto = i;
		}
		else if (i == ((int)(strlen(monto) - 1))){
			posicionPunto = i;
		}
		if ('.' == monto[((int)(strlen(monto) - 1))]){
			puntoAlFinal = 1;
		}
		if (contadorPunto >= 2){
			printf("\n\nCaracteres invalidos.\n");
			return;
		}
	}

	// Si solo tiene parte entera que no pase de 7
	if (contadorPunto == 0 && strlen(monto) > 7){
		printf("\n\nTamano no permitido\n");
		return;
	}

	//Si el punto esta al final
	if (posicionPunto == ((int)(strlen(monto) - 1)))
	{
		datos->monto = atof(monto);
	}

	//Si el punto pasa de los 7 digitos
	else if (posicionPunto > 6){
		printf("\n\nTamano no permitido.\n");
		return;
	}

	//Si cumple con el formato
	else
	{
		char cadenaMonto[posicionPunto + 2];
		for (int i = 0; i < posicionPunto + 2; i++)
		{
			cadenaMonto[i] = monto[i];
		}
		datos->monto = atof(cadenaMonto);
	}

	//-----------------------------------------------------------------------------------------------------------------------

	char pan[18];
	int cantDigitosCvv = 3;
	char tipoT[30];

	printf("\n\nIngrese el PAN de la tarjeta: ");
	scanf("%17s", pan);

	fflush(stdin);
	if (validarCaracteres(pan))
	{
		printf("\n\nIngresaste un caracter invalido.\n");
		return;
	}
	else if (tipoTarjeta(pan, &cantDigitosCvv, tipoT) == 0)
	{
		return;
	}

	strcpy(datos->pan, pan);
	strcpy(datos->tipoT, tipoT);
	printf("Tipo: %s\n", tipoT);

	//-----------------------------------------------------------------------------------------------------------------------

	char cvv[6];
	printf("\n\nIngrese el cvv de la tarjeta: ");
	scanf("%5s", cvv);
	fflush(stdin);

	if (strlen(cvv) != cantDigitosCvv)
	{
		printf("\n\nTamano no permitido\n");
		return;
	}

	strcpy(datos->cvv, cvv);

	if (validarCaracteres(datos->cvv))
	{
		system("cls");
		printf("*********** COMPRA ***********\n\n");

		printf("Ingresaste un caracter invalido.\n");
		return;
	}
	else if (validarTamano(datos->cvv, 3))
	{
		system("cls");
		printf("*********** COMPRA ***********\n\n");

		printf("El pan de la tarjeta esta incompleto.\n");
		return;
	}

	//-----------------------------------------------------------------------------------------------------------------------

	char anio[5];
	char mes[3];

	printf("A continuacion ingresara la fecha de vencimiento de la tarjeta.\n\nIngrese el mes (en num ejm: 01,02): ");
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

	printf("\nIngrese el anio (4 digitos): ");
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

	if (esValidaTarjeta(mes, anio))
	{
		return;
	}
	strcpy(fechaTarjeta->mes, mes);
	strcpy(fechaTarjeta->anio, anio);

	strcpy(datos->fecha.mes, fechaTarjeta->mes);
	strcpy(datos->fecha.anio, fechaTarjeta->anio);

	guardarCompra(*datos);

	printf("\nCOMPRA REGISTRADA EXITOSAMENTE\n");
}

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
		system("cls");
		printf("*********** COMPRA ***********\n\n");

		printf("Tarjeta no valida: año menor al actual.\n");
		return 1;
	}

	if (anioT == anioActual && mesT < mesActual)
	{
		system("cls");
		printf("*********** COMPRA ***********\n\n");
		printf("Tarjeta no valida: mes menor al actual.\n");
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

	char digitosTrajeta[5];

	for (int i = 0; i < 4; i++)
	{
		digitosTrajeta[i] = pan[i];
	}

	int digitos = atoi(digitosTrajeta);

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
		printf("Tu tarjeta es Falsa.\n");
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
		printf("Tu tarjeta es falsa.\n");
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
				strcpy(tipoT, "Mastercad");
				return 1;
			}
		}
		printf("Tu tarjeta es falsa.");
		return 0;
	default: printf("El numero de tarjeta no es valido.\n");
		return 0;
	}
}
