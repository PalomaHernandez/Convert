#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

/**
* El registro instance se define para mantener los valores de las
* opciones que se le pasan al programa como argumentos.
* number mantiene el numero pasado con la opcion -n
* source mantiene la base de origen (entero entre 2 y 16)
* dest mantiene la base de destino (entero entre 2 y 16)
* verbose mantiene 0 o 1 segun este o no activo el modo verboso
**/
typedef struct instance {
	char number[16];
	int source;
	int dest;
	short verbose;
} tInstance;

/**
* La funcion parser se encarga de leer los argumentos y asignarlos
* en el registro a fin de ser utilizados posteriormente en el programa.
* Tambien retorna codigo de error en los casos que asi lo requieran.
**/
extern void parser( int argc, char *argv[], tInstance *args );

/**
* Chequea que digit pertenezca a la base. Retorna 0 si el digito pertenece
* a la base, 1 si el digito es el punto decimal y 2 en caso de no pertenencia.
**/
extern int *check_digit( int *base, char digit );

/**
* La funcion usage muestra por pantalla la ayuda del programa.
**/
extern void usage(  );


#endif // CONVERT_H_INCLUDED
