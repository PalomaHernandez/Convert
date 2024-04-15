#ifndef CONVERTFRACCIONARIO_H_INCLUDED
#define CONVERTFRACCIONARIO_H_INCLUDED

/**
* Convierte el numero pasado como parametro y perteneciente a la base tambien
* pasada como parametro a fraccional decimal.
**/
extern double *a_decimal_fraccionario( char *number, int *base_from, short *verbose );

/**
* Convierte el numero fraccionario en base decimal pasado como
* parametro a la base pasada como parametro.
**/
extern char *desde_decimal_fraccionario( double *number, int *base_to, short *verbose );

#endif // CONVERTFRACCIONARIO_H_INCLUDED
