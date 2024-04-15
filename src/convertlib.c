#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "convertlib.h"
#include "strings.h"

/**
* La funcion parser se encarga de leer los argumentos y asignarlos
* en el registro a fin de ser utilizados posteriormente en el programa.
* Tambien retorna codigo de error en los casos que asi lo requieran.
**/
void parser( int argc, char *argv[], tInstance *args ) {
	// Declaracion de variables
	int *help;										// Para determinar si se pasa el argumento -h
	int *valor_obtenido;					// Almacena el valor que le pasamos a las opciones -s y -d
	int *tam_number;
	int *equals_opt_n;
	int *equals_opt_s;
	int *equals_opt_d;
	int *equals_opt_v;
	int *equals_opt_h;

	// Asignacion de memoria
	help = ( int * ) malloc( sizeof( int ) );
	if ( help == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	valor_obtenido = ( int * ) malloc( sizeof( int ) );
	if ( valor_obtenido == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	tam_number = ( int * ) malloc( sizeof( int ) );
	if ( tam_number == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	equals_opt_s = ( int * ) malloc( sizeof( int ) );
	if ( equals_opt_s == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	equals_opt_n = ( int * ) malloc( sizeof( int ) );
	if ( equals_opt_n == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	equals_opt_d = ( int * ) malloc( sizeof( int ) );
	if ( equals_opt_d == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	equals_opt_v = ( int * ) malloc( sizeof( int ) );
	if ( equals_opt_v == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	equals_opt_h = ( int * ) malloc( sizeof( int ) );
	if ( equals_opt_h == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	string_copy( args->number, "" );
	*help = 0;
	args->source = 0;
	args->dest = 0;
	args->verbose = 0;

	// Parseamos las opciones y asignamos valores al registro
	if ( argc == 1 ) {
		printf( "ERROR: Ninguna opcion ingresada.\n\n" );
		usage(  );
		exit( EXIT_FAILURE );
	}
	for ( int i = 1; i < argc && !( *help ); i++ ) {
		equals_opt_n = string_equals( argv[i], "-n" );
		equals_opt_s = string_equals( argv[i], "-s" );
		equals_opt_d = string_equals( argv[i], "-d" );
		equals_opt_v = string_equals( argv[i], "-v" );
		equals_opt_h = string_equals( argv[i], "-h" );
		if ( *equals_opt_n == 0 ) {
			// Chequeo que -n haya sido pasado una sola vez
			tam_number = string_length( args->number );
			if ( *tam_number > 0 ) {
				printf( "ERROR: La opcion -n fue pasada mas de una vez.\n" );
				exit( EXIT_FAILURE );
			}
			// Chequeo que se haya pasado un valor a -n
			if ( ++i < argc ) {
				// Asignamos su valor al registro
				string_copy( args->number, argv[i] );
			}
			else {
				printf( "ERROR: No se ha suministrado un valor para la opcion -n.\n\n" );
				usage(  );
				exit( EXIT_FAILURE );
			}
		}
		else if ( *equals_opt_s == 0 ) {
			// Chequeo que se haya pasado un valor a -s
			if ( ++i < argc ) {
				*valor_obtenido = atoi( argv[i] );
			}
			else {
				printf( "ERROR: No se ha suministrado un valor para la opcion -s.\n\n" );
				usage(  );
				exit( EXIT_FAILURE );
			}
			// Chequeo que -s haya sido pasado una sola vez
			if ( args->source || *valor_obtenido < 2 || *valor_obtenido > 16 ) {
				printf
					( "ERROR: La opcion -s fue pasada mas de una vez o la base indicada esta fuera del rango permitido.\n" );
				exit( EXIT_FAILURE );
			}
			// Asignamos su valor al registro
			args->source = *valor_obtenido;
		}
		else if ( *equals_opt_d == 0 ) {
			// Chequeo que se haya pasado un valor a -d
			if ( ++i < argc ) {
				*valor_obtenido = atoi( argv[i] );
			}
			else {
				printf( "ERROR: No se ha suministrado un valor para la opcion -d.\n\n" );
				usage(  );
				exit( EXIT_FAILURE );
			}
			// Chequeo que -d haya sido pasado una sola vez
			if ( args->dest || *valor_obtenido < 2 || *valor_obtenido > 16 ) {
				printf
					( "ERROR: La opcion -d fue pasada mas de una vez o la base indicada esta fuera del rango permitido.\n" );
				exit( EXIT_FAILURE );
			}
			// Asignamos su valor al registro
			args->dest = *valor_obtenido;
		}
		else if ( *equals_opt_v == 0 ) {
			// Chequeo que -v haya sido pasado una sola vez
			if ( args->verbose ) {
				printf( "ERROR: La opcion -v fue pasada mas de una vez.\n" );
				exit( EXIT_FAILURE );
			}
			// Asignamos su valor al registro
			args->verbose = 1;
		}
		else if ( *equals_opt_h == 0 ) {
			*help = 1;
			usage(  );
			exit( EXIT_SUCCESS );
		}
		else {
			printf( "ERROR: Se detecto una opcion desconocida o un argumento faltante.\n\n" );
			usage(  );
			exit( EXIT_FAILURE );
		}
	}

	// Seteo de valores por defecto
	if ( args->source == 0 ) {
		args->source = 10;
	}
	if ( args->dest == 0 ) {
		args->dest = 10;
	}

	// Bloque de liberacion de memoria
	free( help );
	free( valor_obtenido );
	free( tam_number );
	free( equals_opt_n );
	free( equals_opt_s );
	free( equals_opt_d );
	free( equals_opt_v );
	free( equals_opt_h );
}

/**
* Chequea que digit pertenezca a la base. Retorna 0 si el digito pertenece
* a la base, 1 si el digito es el punto decimal y 2 en caso de no pertenencia.
**/
int *check_digit( int *base, char digit ) {
	// Declaracion de variables
	int *valid;

	// Asignacion de memoria
	valid = ( int * ) malloc( sizeof( int ) );
	if ( valid == NULL ) {
		printf( "Error: malloc(): la memoria no ha podido ser asignada" );
		exit( EXIT_FAILURE );
	}

	// Inicializacion de variables
	*valid = 0;

	// Chequeo de cada digito respecto a la base indicada
	switch ( toupper( digit ) ) {
		case 'F':
			if ( *base < 16 ) {
				*valid = 2;
			}
			break;
		case 'E':
			if ( *base < 15 ) {
				*valid = 2;
			}
			break;
		case 'D':
			if ( *base < 14 ) {
				*valid = 2;
			}
			break;
		case 'C':
			if ( *base < 13 ) {
				*valid = 2;
			}
			break;
		case 'B':
			if ( *base < 12 ) {
				*valid = 2;
			}
			break;
		case 'A':
			if ( *base < 11 ) {
				*valid = 2;
			}
			break;
		case 'G' ... 'Z':
			*valid = 2;
			break;
		case '0' ... '9':
			if ( ( ( int ) digit - 48 ) >= *base ) {
				*valid = 2;
			}
			break;
		case '.':
			*valid = 1;
			break;
		default:
			*valid = 2;
			break;
	}

	return valid;
}

/**
* La funcion usage muestra por pantalla la ayuda del programa.
**/
void usage(  ) {
	printf( "Uso: \n  convert -n <number> [-s <source_base>] [-d <dest_base>] [-v] [-h]\n\n"
					"Opciones:\n"
					"  -n <number>\t\tNumero a ser convertido. Se admiten 10 digitos para la parte entera y 5 para la parte fraccionaria.\n"
					"  -s <source_base>\tEstablece la base de origen. Valores posibles entre 2 y 16. (Valor por defecto: 10)\n"
					"  -d <dest_base>\tEstablece la base de destino. Valores posibles entre 2 y 16. (Valor por defecto: 10)\n"
					"  -v\t\t\tActiva el modo verboso en cuyo caso el paso a paso es mostrado por pantalla.\n"
					"  -h\t\t\tMuestra esta ayuda y sale.\n" );
}
