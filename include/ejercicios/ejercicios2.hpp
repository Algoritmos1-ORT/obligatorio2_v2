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
// POS: deja en t únicamente las asociaciones cuyos dominios pertenecen a
//      permitidos. No modifica el multiset permitido.
void RestringirDominio(TablaIntString& t, MultisetInt permitidos);

// PRE: 0 <= origen < cantidadVertices(grafo).
// POS: retorna una cola con los vértices alcanzables desde origen recorridos
//      en profundidad. No modifica grafo y funciona con ambas
//      representaciones.
ColaInt RecorridaDFS(GrafoInt grafo, int origen);
