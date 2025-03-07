#include <string.h>

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

int validarTamano(char* cadena, int tamano)
{
    if (((int)strlen(cadena)) < tamano)
    {
        return 1;
    }
    return 0;
}
