#pragma once

/**
 * @brief Declaraciones de los ejercicios integrales.
 *
 * @note Este archivo no debe ser modificado.
 */

#include "pila_int.hpp"
#include "cola_int.hpp"
#include "lista_pos_int.hpp"
#include "tabla_int_string.hpp"
#include "multiset_int.hpp"
#include "grafo_int.hpp"

// PRE: -
// POS: retorna true si y solo si p2 contiene todos los elementos de p1,
//      respetando sus multiplicidades. No modifica ninguna de las pilas.
//      Solo puede usar PilaInt como estructura auxiliar.
bool EstaContenida(PilaInt p1, PilaInt p2);

// PRE: -
// POS: elimina de c todas las apariciones de su valor máximo y preserva el
//      orden relativo de los elementos restantes. Solo puede usar ColaInt
//      como estructura auxiliar.
void EliminarMaximos(ColaInt& c);

// PRE: -
// POS: retorna una lista con cada valor de m cuya multiplicidad es mayor que
//      uno, sin valores repetidos. Solo puede usar MultisetInt y ListaPosInt
//      como estructuras auxiliares.
ListaPosInt ObtenerRepetidos(MultisetInt m);

// PRE: -
// POS: deja en t únicamente las asociaciones cuyos dominios pertenecen a
//      permitidos. No modifica el multiset permitido.
void RestringirDominio(TablaIntString& t, MultisetInt permitidos);

// PRE: 0 <= origen < cantidadVertices(grafo).
// POS: retorna una cola con los vértices alcanzables desde origen recorridos
//      en profundidad. No modifica grafo y funciona con ambas
//      representaciones.
ColaInt RecorridaDFS(GrafoInt grafo, int origen);
