#include "../headers/headersTransaciones/compra.h"
#include "../headers/estructuras.h"
#include "../headers/operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void obtenerFechaActual(FechaCreacion *fechaActual) {
    time_t tiempoActual = time(NULL);
    struct tm *infoTiempo = localtime(&tiempoActual);

    fechaActual->dia = infoTiempo->tm_mday;
    fechaActual->mes = infoTiempo->tm_mon + 1;
    fechaActual->anio = infoTiempo->tm_year + 1900;
    fechaActual->hora = infoTiempo->tm_hour;
    fechaActual->minuto = infoTiempo->tm_min;
    fechaActual->segundo = infoTiempo->tm_sec;
}

void escribirCompraEnArchivo(Transacciones *transaccion) {

    FILE *archivoTransacciones = fopen("../output/Transacciones.txt", "a");

    if (!archivoTransacciones) {
        printf("No se pudo abrir el archivo de compras para escritura\n");
        return;
    }

    fprintf(archivoTransacciones, "%d | %.2f | %s | %s | %02d/%02d/%04d %02d:%02d:%02d | %s \n",
        transaccion->referencia, transaccion->datos.monto, transaccion->datos.pan, transaccion->datos.cvv,
        transaccion->creacion.dia, transaccion->creacion.mes, transaccion->creacion.anio,
        transaccion->creacion.hora, transaccion->creacion.minuto, transaccion->creacion.segundo,
        transaccion->estado);

    fclose(archivoTransacciones);
}

void leerArchivo() {
  FILE *file;
  char c;
  int contador = 0;
  file =fopen("../output/Transacciones.txt","r");

	if(file!=NULL){
		while(!feof(file)){
			c=fgetc(file);
            contador++;
		}
    printf("Lineas: %d\n",contador);

	}else{
		printf("Error al abrir el archivo");
	}
}

void guardarCompra(Datos datosCompra) {

    static short numeroTotalCompras = 1;

    if (numeroTotalCompras > 20) {
    	printf("Limite de transacciones alcanzado: 20\n");
    	return;
	}

	Transacciones *nuevaTransaccion;
	nuevaTransaccion = malloc(sizeof(Transacciones));

	if (nuevaTransaccion == NULL) {
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