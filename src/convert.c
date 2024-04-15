#include <stdio.h>
#include <stdlib.h>
#include "convert_entero.h"
#include "convert_fraccionario.h"
#include "convertlib.h"
#include "strings.h"

int main( int argc, char *argv[] ) {
	// Declaracion de variables
	int *punto_leido;
	char *parte_entera;
	char *parte_fraccionaria;
	long unsigned int *decimal_entero;
	double *decimal_fraccionario;
	short int *verbose;
	tInstance *program;
	int *tam_number;
	int * i;

	// Asignacion de memoria
	punto_leido = ( int * ) malloc( sizeof( int ) );
	if ( punto_leido == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	parte_entera = ( char * ) malloc( 11 * sizeof( char ) );
	if ( parte_entera == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	parte_fraccionaria = ( char * ) malloc( 6 * sizeof( char ) );
	if ( parte_fraccionaria == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	decimal_entero = ( long unsigned int * ) malloc( sizeof( long unsigned int ) );
	if ( decimal_entero == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	decimal_fraccionario = ( double * ) malloc( sizeof( double ) );
	if ( decimal_fraccionario == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	verbose = ( short int * ) malloc( sizeof( short int ) );
	if ( verbose == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	program = ( tInstance * ) malloc( sizeof( tInstance ) );
	if ( program == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	tam_number = ( int * ) malloc( sizeof( int ) );
	if ( tam_number == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	i = ( int * ) malloc( sizeof( int ) );
	if ( i == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	//Creamos un registro tInstance e inicializamos las variables
	parser( argc, argv, program );
	*punto_leido = 0;
	*parte_entera = '\0';
	*parte_fraccionaria = '\0';
	*decimal_entero = 0;
	*decimal_fraccionario = 0;
	verbose = &program->verbose;
	*tam_number = *string_length( program->number );
	*i = 0;


	// Leemos los digitos uno a uno, los chequeamos para generar parte entera y fraccionaria
	for ( *i = 0; *i < ( *tam_number ); (*i)++ ) {
		if ( *check_digit( &program->source, program->number[*i] ) == 0 && *punto_leido == 0 ) {
			// Digito valido de la parte entera
			char_append( parte_entera, program->number[*i] );
		}
		else if ( *check_digit( &program->source, program->number[*i] ) == 0 && *punto_leido == 1 ) {
			// Digito valido de la parte fraccionaria
			char_append( parte_fraccionaria, program->number[*i] );
		}
		else if ( *check_digit( &program->source, program->number[*i] ) == 1 && *punto_leido == 0 ) {
			// Punto decimal
			*punto_leido = 1;
		}
		else {
			// Digito no correspondiente con la base de origen
			printf( "El numero no corresponde a la base %i.", program->source );
			exit( EXIT_FAILURE );
		}
	}

    if( *string_length(parte_entera) > 10 ) {
        printf( "Error: La parte entera del numero ingresado supera los 10 digitos." );
        exit(EXIT_FAILURE);
    }

    if( *string_length( parte_fraccionaria ) > 5 ) {
        printf( "Error: La parte fraccionaria del numero ingresado supera los 5 digitos." );
        exit(EXIT_FAILURE);
    }

	printf( "-> Convertir %s de base %i a base %i\n\n", program->number, program->source,
					program->dest );
	if ( *verbose == 1 ) {
		printf( "Se emplea la base decimal como base auxiliar para efectuar las conversiones. \n\n" );
	}

	// Efectuamos la conversion
	if ( ( ( int ) program->number[0] - 48 ) != 0 ) {
		// Si el numero tiene parte entera
		decimal_entero = a_decimal_entero( parte_entera, &program->source, verbose );
		parte_entera = desde_decimal_entero( decimal_entero, &program->dest, verbose );
	}

	if ( *punto_leido != 0 ) {
		// Si el numero tiene parte fraccionaria
		decimal_fraccionario = a_decimal_fraccionario( parte_fraccionaria, &program->source, verbose );
		parte_fraccionaria =
            desde_decimal_fraccionario( decimal_fraccionario, &program->dest, verbose );
	}

	if ( *punto_leido != 0 && ( ( int ) program->number[0] - 48 ) != 0 ) {
		printf( "=> Resultado final: %s.%s \n", parte_entera, parte_fraccionaria );
	}
	else {
		if ( *punto_leido == 0 ) {
			printf( "=> Resultado final: %s \n", parte_entera );
		}
		else {
			printf( "=> Resultado final: 0.%s \n", parte_fraccionaria );
		}
	}

	// Bloque de liberacion de memoria
	free( tam_number );
	free( parte_fraccionaria );
	free( parte_entera );
	free( decimal_entero );
	free( decimal_fraccionario );
	free( punto_leido );
	free( program );

	return 0;
}
