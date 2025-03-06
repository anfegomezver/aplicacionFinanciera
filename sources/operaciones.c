#include "../headers/headersTransaciones/compra.h"
#include "../headers/estructuras.h"
#include "../headers/operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void obtenerFechaActual(FechaCreacion* fechaActual)
{
	time_t tiempoActual = time(NULL);
	struct tm* infoTiempo = localtime(&tiempoActual);

	fechaActual->dia = infoTiempo->tm_mday;
	fechaActual->mes = infoTiempo->tm_mon + 1;
	fechaActual->anio = infoTiempo->tm_year + 1900;
	fechaActual->hora = infoTiempo->tm_hour;
	fechaActual->minuto = infoTiempo->tm_min;
	fechaActual->segundo = infoTiempo->tm_sec;
}

void escribirCompraEnArchivo(Transacciones* transaccion)
{
	FILE* archivoTransacciones = fopen("../output/Transacciones.txt", "a");

	if (!archivoTransacciones)
	{
		printf("No se pudo abrir el archivo de compras para escritura\n");
		return;
	}

	fprintf(archivoTransacciones, "%d | %.2f | %s | %s | %02d/%02d/%04d %02d:%02d:%02d | %s @\n",
	        transaccion->referencia, transaccion->datos.monto, transaccion->datos.pan, transaccion->datos.cvv,
	        transaccion->creacion.dia, transaccion->creacion.mes, transaccion->creacion.anio,
	        transaccion->creacion.hora, transaccion->creacion.minuto, transaccion->creacion.segundo,
	        transaccion->estado);



	fclose(archivoTransacciones);
}

void leerArchivo(Transacciones** transacciones)
{
	FILE* file;
	char c;
	int contador = 0;
	file = fopen("../output/Transacciones.txt", "r");

	if (file != NULL)
	{
		while (!feof(file))
		{
			c = fgetc(file);

			if (c == '@')
			{
				contador++;
			}
		}
		printf("Lineas: %d\n", contador);
	}
	else
	{
		printf("Error al abrir el archivo");
	}

	rewind(file);  // Volvemos al inicio para leerlas

	*transacciones = malloc(contador * sizeof(Transacciones));
	if (*transacciones == NULL) {
		printf("El archivo se encuentra vacio\n");
		fclose(file);
		return;
	}

	// Leemos cada transacción directamente
	char linea[80];
	for (int i = 0; i < contador; i++) {
		if (fgets(linea, sizeof(linea), file) != NULL) {
			// Leemos la transacción, ignorando el @ al final
			sscanf(linea, "%d | %f | %s | %s | %d/%d/%d %d:%d:%d | %s @",
				   &transacciones[i]->referencia,
				   &transacciones[i]->datos.monto,
				   transacciones[i]->datos.pan,
				   transacciones[i]->datos.cvv,
				   &transacciones[i]->creacion.dia,
				   &transacciones[i]->creacion.mes,
				   &transacciones[i]->creacion.anio,
				   &transacciones[i]->creacion.hora,
				   &transacciones[i]->creacion.minuto,
				   &transacciones[i]->creacion.segundo,
				   transacciones[i]->estado);
		}
	}
}




void guardarCompra(Datos datosCompra)
{
	static short numeroTotalCompras = 1;

	if (numeroTotalCompras > 20)
	{
		printf("Limite de transacciones alcanzado: 20\n");
		return;
	}

	Transacciones* nuevaTransaccion;
	nuevaTransaccion = malloc(sizeof(Transacciones));

	if (nuevaTransaccion == NULL)
	{
		printf("Error: No se pudo asignar memoria\n");
		return;
	}

	nuevaTransaccion->referencia = numeroTotalCompras;
	strcpy(nuevaTransaccion->estado, "Compra");
	nuevaTransaccion->datos = datosCompra;
	obtenerFechaActual(&nuevaTransaccion->creacion);

	escribirCompraEnArchivo(nuevaTransaccion);

	numeroTotalCompras++;
}
