#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

/**
* Retorna un puntero a entero que indica la cantidad de caracteres de *str.
**/
extern int *string_length( const char *str );

/**
* Retorna un puntero a entero cuyo valor apuntado depende de la condicion
* de igualdad entre (char*) str y (char*) str2. El valor sera 0 si ambas
* son iguales y 1 si no lo son.
**/
extern int *string_equals( const char *str1, const char *str2 );

/**
* La cadena de caracteres (char*) src es copiada a (char*) dest.
* El valor de retorno es un puntero a la direccion de memoria del primer
* caracter de (char*) dest.
**/
extern char *string_copy( char *dest, char *src );

/**
* Invierte la cadena de caracteres pasada como parametro
**/
extern void string_invert( char *str );

/**
* Concatena (char*) src al final de (char*) dest. Si src es la cadena
* "Mundo!" y dest es la cadena "Hola ", luego de la invocacion dest
* apunta a la cadena "Hola Mundo!".
**/
extern void string_concat( char *dest, const char *src );

/**
* Asigna el caracter src en la posicion del caracter nulo de dest y
* añade un nuevo caracter nulo luego del caracter src.
**/
extern void char_append( char *dest, const char src );

#endif // STRINGS_H_INCLUDED
