#include <stdlib.h>
#include <stdio.h>
#include "strings.h"

/**
* Convierte el número pasado como parámetro y perteneciente a la base también
* pasada como parámetro a fraccional decimal.
**/
double *a_decimal_fraccionario( char *number, int *base_from, short *verbose ) {
	// Declaracion de variables
	int *i;
	int *j;
	double *result;
	double *result_aux;
	int *digito;
	int *number_length;

	// Asignacion de memoria
	i = ( int * ) malloc( sizeof( int ) );
	if ( i == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	j = ( int * ) malloc( sizeof( int ) );
	if ( j == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	result = ( double * ) malloc( sizeof( double ) );
	if ( result == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	result_aux = ( double * ) malloc( sizeof( double ) );
	if ( result_aux == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	digito = ( int * ) malloc( sizeof( int ) );
	if ( digito == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	number_length = ( int * ) malloc( sizeof( int ) );
	if ( number_length == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*i = 0;
	*j = 0;
	*result = 0;
	*result_aux = 0;
	*digito = 0;
	number_length = string_length( number );

	// Efectuamos la conversion propiamente dicha, mostrando los pasos
	// adecuados si se detecta el modo verboso activo.
	if ( *verbose == 1 ) {
		printf
			( ":: Utilizando el metodo de la division convertimos el numero fraccionario %s en base %i a base 10: \n",
				number, *base_from );
	}
	for ( *j = ( *number_length - 1 ); *j >= 0; ( *j )-- ) {
		switch ( number[*j] ) {
			case '0' ... '9':
				// El numero 0 en la tabla ASCII equivale al caracter 48
				// Castear un char a int nos brinda su posicion en la tabla ASCII
				*digito = ( ( int ) ( number[*j] ) - 48 );
				break;
			case 'A' ... 'F':
				// La letra A en la tabla ASCII equivale al caracter 65
				// Castear un char a int nos brinda su posicion en la tabla ASCII
				*digito = ( ( int ) ( number[*j] ) - 55 );
				break;
			default:
				break;
		}

		*result_aux = *result;
		*result = ( *result + *digito ) / *base_from;

		if ( *verbose == 1 ) {
			if ( *i == 0 ) {
				printf( "X_\(%i): %i / %i = %g \n", *i, *digito, *base_from, *result );
			}
			else {
				printf( "X_\(%i): (%g + %i) / %i = %g \n", *i, *result_aux, *digito, *base_from, *result );
			}
		}
		( *i )++;
	}
	if ( *verbose == 1 ) {
		printf( "Resultado: %g \n\n", *result );
	}

	// Bloque de liberacion de memoria
	free( i );
	free( j );
	free( result_aux );
	free( number_length );
	free( digito );

	return result;
}

/**
* Convierte el número fraccionario en base decimal pasado como
* parámetro a la base pasada como parámetro.
**/
char *desde_decimal_fraccionario( double *number, int *base_to, short *verbose ) {
	// Declaracion de variables
	int *digito_entero;
	int *iterador;
	char *result;

	// Asignacion de memoria
	result = ( char * ) malloc( sizeof( char ) * 6 );
	if ( result == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	digito_entero = ( int * ) malloc( sizeof( int ) );
	if ( digito_entero == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	iterador = ( int * ) malloc( sizeof( int ) );
	if ( iterador == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*digito_entero = 0;
	*iterador = 0;

	// Efectuamos la conversion propiamente dicha, mostrando los pasos
	// adecuados si se detecta el modo verboso activo.
	if ( *verbose == 1 ) {
		printf
			( ":: Utilizando el metodo de la multiplicacion convertimos el numero fraccionario %g en base 10 a base %i: \n",
				*number, *base_to );

	}
	while ( *iterador <= 5 ) {
		if ( *verbose == 1 ) {
			printf( "X_\(%i): %g * %i = %g -->", *iterador, *number, *base_to,
							( *number ) * ( *base_to ) );
		}
		*number *= ( *base_to );
		*digito_entero = ( int ) *number;
		*number -= ( *digito_entero );

		if ( *digito_entero <= 9 ) {
			// El numero 0 en la tabla ASCII equivale al caracter 48
			// Castear un char a int nos brinda su posicion en la tabla ASCII
			result[*iterador] = ( char ) ( *digito_entero + 48 );
		}
		else {
			// La letra A en la tabla ASCII equivale al caracter 65
			// Castear un char a int nos brinda su posicion en la tabla ASCII
			result[*iterador] = ( char ) ( *digito_entero + 55 );
		}
		if ( *verbose == 1 ) {
			printf( " Digito resultante en base %i: %c \n", *base_to, ( result[*iterador] ) );
		}
		( *iterador )++;
	}
	result[*iterador] = '\0';
	if ( *verbose == 1 ) {
		printf( "Resultado: 0.%s\n\n", result );
	}

	// Bloque de liberacion de memoria
	free( digito_entero );
	free( iterador );

	return result;
}
