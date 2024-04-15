#ifndef CONVERTENTERO_H_INCLUDED
#define CONVERTENTERO_H_INCLUDED

/**
* Convierte el numero pasado como parametro y perteneciente a la base tambien
* pasada como parametro a entero decimal.
**/
extern unsigned long int *a_decimal_entero( char *number, int *base_from, short *verbose );

/**
* Convierte el numero entero en base decimal pasado como parametro
* a la base pasada como parametro.
**/
extern char *desde_decimal_entero( unsigned long int *number, int *base_to, short *verbose );

#endif // CONVERTENTERO_H_INCLUDED
