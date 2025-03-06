cmake_minimum_required(VERSION 3.30)
project(aplicacionFinanciera C)

set(CMAKE_C_STANDARD 99)

add_executable(aplicacionFinanciera sources/main.c
        sources/menu.c
        headers/menu.h
        sources/operaciones.c
        headers/operaciones.h
        sources/validaciones.c
        headers/validaciones.h
        sources/transacciones/anulacion.c
        headers/headersTransaciones/anulacion.h
        sources/transacciones/cierre.c
        headers/headersTransaciones/cierre.h
        sources/transacciones/compra.c
        headers/headersTransaciones/compra.h
        sources/transacciones/reimpresion.c
        headers/headersTransaciones/reimpresion.h
        sources/transacciones/reporteTotal.c
        headers/headersTransaciones/reporteTotal.h
        headers/estructuras.h
)
