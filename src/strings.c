#include <stdlib.h>
#include <stdio.h>
#include "strings.h"

/**
* Retorna un puntero a entero que indica la cantidad de caracteres de *str.
**/
int *string_length( const char *str ) {
	// Declaracion de variables
	int *iterator;

	// Asignacion de memoria
	iterator = ( int * ) malloc( sizeof( int ) );
	if ( iterator == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*iterator = 0;

	// Conteo de caracteres en (char*) str
	while ( ( int ) ( *str ) != 0 ) {
		*iterator = *iterator + 1;
		str++;
	}

	return iterator;
}

/**
* Retorna un puntero a entero cuyo valor apuntado depende de la condicion
* de igualdad entre (char*) str y (char*) str2. El valor sera 0 si ambas
* son iguales y 1 si no lo son.
**/
int *string_equals( const char *str, const char *str2 ) {
	// Declaracion de variables
	int *a_retornar;
	int *str_length;
	int *str2_length;

	// Asignacion de memoria
	str_length = ( int * ) malloc( sizeof( int ) );
	if ( str_length == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	str2_length = ( int * ) malloc( sizeof( int ) );
	if ( str2_length == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	a_retornar = ( int * ) malloc( sizeof( int ) );
	if ( a_retornar == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	str_length = string_length( str );
	str2_length = string_length( str2 );
	*a_retornar = 0;

	// Comparacion caracter por caracter
	if ( *str_length != *str2_length ) {
		*a_retornar = 1;
	}
	else {
		while ( ( int ) *str ) {
			if ( ( int ) *str != ( int ) *str2 ) {
				*a_retornar = 1;
			}
			str++;
			str2++;
		}
	}

	// Bloque de liberacion de memoria
	free( str_length );
	free( str2_length );

	return a_retornar;
}

/**
* La cadena de caracteres (char*) src es copiada a (char*) dest.
* El valor de retorno es un puntero a la direccion de memoria del primer
* caracter de (char*) dest.
**/
char *string_copy( char *dest, char *src ) {
	// Guardamos la direccion de memoria apuntada por dest
	char *copia = dest;

	// Efectuamos la copia caracterpor caracter
	while ( ( int ) *src ) {
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';

	return copia;
}

/**
* Invierte la cadena de caracteres pasada como parametro
**/
void string_invert( char *str ) {
	// Declaracion de variables
	char *aux;
	int *i;
	int *tamanio;

	// Asignacion de memoria
	aux = ( char * ) malloc( sizeof( char ) );
	if ( aux == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	i = ( int * ) malloc( sizeof( int ) );
	if ( i == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	tamanio = ( int * ) malloc( sizeof( int ) );
	if ( tamanio == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*i = 0;
	tamanio = string_length( str );

	// Recorremos la cadena e invertimos caracteres
	while ( *i < *tamanio / 2 ) {
		*aux = str[*i];
		str[*i] = str[*tamanio - *i - 1];
		str[*tamanio - *i - 1] = *aux;
		( *i )++;
	}

	// Bloque de liberacion de memoria
	free( aux );
	free( i );
	free( tamanio );
}

/**
* Concatena (char*) src al final de (char*) dest. Si src es la cadena
* "Mundo!" y dest es la cadena "Hola ", luego de la invocacion dest
* apunta a la cadena "Hola Mundo!".
**/
void string_concat( char *dest, const char *src ) {
	// Declaracion de variables
	int *i;
	int *dest_length;
	int *src_length;

	// Asignacion de memoria
	i = ( int * ) malloc( sizeof( int ) );
	if ( i == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	dest_length = ( int * ) malloc( sizeof( int ) );
	if ( dest_length == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	src_length = ( int * ) malloc( sizeof( int ) );
	if ( src_length == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*i = 0;
	dest_length = string_length( dest );
	src_length = string_length( src );

	// Reasignacion de memoria
	dest = ( char * ) realloc( dest, *dest_length + *src_length );

	// Asignamos los caracteres de src en dest
	while ( *i < *src_length ) {
		dest[*i + *dest_length] = src[*i];
		( *i )++;
	}
	dest[*i + *dest_length] = '\0';

	// Bloque de liberacion de memoria
	free( i );
	free( dest_length );
	free( src_length );
}

/**
* Asigna el caracter src en la posicion del caracter nulo de dest y
* añade un nuevo caracter nulo luego del caracter src.
**/
void char_append( char *dest, const char src ) {
	// Guardamos la direccion de memoria apuntada por dest
	char *copia = dest;

	// Avanzamos hasta la ultima posicion de dest y asignamos
	// los valores correspondientes
	while ( *dest != '\0' ) {
		dest++;
	}
	*dest = src;
	dest++;
	*dest = '\0';
	dest = copia;
}
