#include "../../headers/headersTransaciones/cierre.h"
#include "../../headers/operaciones.h"

#include "../../headers/headersTransaciones/reporteTotal.h"

#include <stdio.h>

void cerrar(){
    char opcion;
    crearReporteTotal();

    printf("Estas seguro de que quieres realizar el cierre?\n1: si\n2: no\n\nIngrese una opcion");
    scanf("%c",&opcion);
    fflush(stdin);
    switch (opcion) {
        case '1':
            limpiarArchivo();
            printf("Se borro el historico de transacciones\n");
    case '2':
        return;
        default: printf("Opcion incorrecta");
    }
    return;
}