#pragma once
// NOTA: Este archivo no debe ser modificado

#include "implementaciones.hpp"

struct _representacionTablaIntString;
typedef struct _representacionTablaIntString* TablaIntString;

// PRE: -
// POS: retorna una nueva tabla vacia.
//		Al crear la tabla se recibe la cantidad esperada de elementos, 
//		aunque puedan insertarse mas elementos.
TablaIntString crearTablaIntString(unsigned int esperados);

// PRE: -
// POS: Define T(d) = r si la tabla no esta definida en d.
//  	En caso contrario actualiza el valor T(d) con r.
void agregar(TablaIntString& t, int d, const char* r);

// PRE: -
// POS: Retorna true si y solo si la tabla esta definida en d.
//      Complejidad esperada: O(1) en promedio.
bool estaDefinida(TablaIntString t, int d);

// PRE: estaDefinida(d)    
// POS: Retorna T(d)
//      Complejidad esperada: O(1) en promedio.
const char* recuperar(TablaIntString t, int d);

// PRE: -
// POS: Borra la asociacion ligada a d, siempre que esta exista.
//      Complejidad esperada: O(1) en promedio.
void borrar(TablaIntString& t, int d);

// PRE: !esVacia()
// POS: Retorna un dominio cualquiera de la tabla
//      Complejidad esperada: O(1) peor caso.
int elemento(TablaIntString t);

// PRE: -
// POS: retorna true si y solo si la tabla esta vacia
//      Complejidad esperada: O(1) peor caso.
bool esVacia(TablaIntString t);

// PRE: -
// POS: retorna la cantidad de elementos presentes en la tabla
//      Complejidad esperada: O(1) peor caso.
unsigned int cantidadElementos(TablaIntString t);

// PRE: -
// POS: libera la memoria de la tabla
void destruir(TablaIntString& t);

// PRE: -
// POS: retorna una copia de la tabla t sin compartir memoria
TablaIntString clon(TablaIntString t);
