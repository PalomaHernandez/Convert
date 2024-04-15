#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "strings.h"

/**
* Convierte el número pasado como parámetro y perteneciente a la base también
* pasada como parámetro a entero decimal.
**/
unsigned long int *a_decimal_entero( char *number, int *base_from, short *verbose ) {
	// Declaracion de variables
	unsigned long int *result;
	int *tam_number;

	// Asignacion de memoria
	tam_number = ( int * ) malloc( sizeof( int ) );
	if ( tam_number == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	result = ( unsigned long int * ) malloc( sizeof( unsigned long int ) );
	if ( result == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	tam_number = string_length( number );
	*result = 0;

	// Efectuamos la conversion propiamente dicha, mostrando los pasos
	// adecuados si se detecta el modo verboso activo.
	if ( *verbose == 1 ) {
		printf
			( ":: Utilizando el metodo de la multiplicacion convertimos el numero entero %s en base %i a base 10 \n",
				number, *base_from );
		printf( "Efectuamos la suma de los siguientes terminos:\n" );
	}
	for ( int i = ( *tam_number ) - 1; i >= 0; i-- ) {
		switch ( *number ) {
			case '0' ... '9':
				if ( *verbose == 1 ) {
					// El numero 0 en la tabla ASCII equivale al caracter 48
					// Castear un char a int nos brinda su posicion en la tabla ASCII
					printf( "\t%ix%i^\(%i)\n", ( ( int ) ( *number ) - 48 ), *base_from, i );
				}
				*result += ( ( int ) ( *number ) - 48 ) * ( int ) pow( *base_from, i );
				break;
			case 'A' ... 'F':
				if ( *verbose == 1 ) {
					// La letra A en la tabla ASCII equivale al caracter 65
					// Castear un char a int nos brinda su posicion en la tabla ASCII
					printf( "\t%ix%i^\(%i)\n", ( ( int ) ( *number ) - 55 ), *base_from, i );
				}
				*result += ( ( int ) ( *number ) - 55 ) * ( int ) pow( *base_from, i );
				break;
			default:
				break;
		}
		++number;
	}
	if ( *verbose == 1 ) {
		printf( "Resultado: %lu\n\n", *result );
	}

	// Bloque de liberacion de memoria
	free( tam_number );

	return result;
}

/**
* Convierte el número entero en base decimal pasado como parámetro
* a la base pasada como parámetro.
**/
char *desde_decimal_entero( unsigned int *number, int *base_to, short *verbose ) {
	// Declaracion de variables
	int *resto;
	int *iterador;
	char *result;

	// Asignacion de memoria
	result = ( char * ) malloc( sizeof( char ) * 40 );
	if ( result == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	resto = ( int * ) malloc( sizeof( int ) );
	if ( resto == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	iterador = ( int * ) malloc( sizeof( int ) );
	if ( iterador == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*resto = 0;
	*iterador = 0;

	// Efectuamos la conversion propiamente dicha, mostrando los pasos
	// adecuados si se detecta el modo verboso activo.
	if ( *verbose == 1 ) {
		printf
			( ":: Utilizando el metodo de la division convertimos el numero entero %i en base 10 a base %i: \n",
				*number, *base_to );
	}
	if ( *number == 0 ) {
		result[0] = ( char ) ( 48 );
		result[1] = '\0';
	}
	else {
		while ( *number != 0 ) {
			if ( *verbose == 1 ) {
				printf( "X_\(%i): %u mod %i = %i y ", *iterador, *number, *base_to, *number % *base_to );
			}
			*resto = *number % *base_to;
			if ( *verbose == 1 ) {
				printf( "Q_\(%i): \(%u - %i)/%i = %u\n", *iterador, *number, *resto, *base_to,
								( *number - *resto ) / ( *base_to ) );
			}
			*number = ( *number - *resto ) / ( *base_to );
			if ( *resto <= 9 ) {
				// El numero 0 en la tabla ASCII equivale al caracter 48
				// Castear un char a int nos brinda su posicion en la tabla ASCII
				result[*iterador] = ( char ) ( *resto + 48 );
			}
			else {
				// La letra A en la tabla ASCII equivale al caracter 65
				// Castear un char a int nos brinda su posicion en la tabla ASCII
				result[*iterador] = ( char ) ( *resto + 55 );
			}
			( *iterador )++;
		}
		result[*iterador] = '\0';
		string_invert( result );
	}
	if ( *verbose == 1 ) {
		printf( "Resultado: %s\n\n", result );
	}

	// Bloque de liberacion de memoria
	free( resto );
	free( iterador );

	return result;
}
