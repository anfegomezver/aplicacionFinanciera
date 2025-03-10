#ifndef COMPRA_H
#define COMPRA_H

typedef struct
{
    char mes[3];
    char anio[5];
} FechaTarjeta;

typedef struct
{
    float monto;
    char pan[17];
    char cvv[5];
    char tipoT[30];
    FechaTarjeta fecha;
} Datos;

void crearCompra();
int validarCaracteres(char []);
int esValidaTarjeta(char*, char*);
int tipoTarjeta(char*,int*,char*);
int esReal(int, char*);

#endif