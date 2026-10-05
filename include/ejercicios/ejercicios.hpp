#pragma once

#include "pila_int.hpp"
#include "cola_int.hpp"
#include "lista_pos_int.hpp"
#include "tabla_int_string.hpp"
#include "multiset_int.hpp"
#include "grafo_int.hpp"

bool EstaContenida(PilaInt p1, PilaInt p2);
void EliminarMaximos(ColaInt& c);
ListaPosInt ObtenerRepetidos(MultisetInt m);
void RestringirDominio(TablaIntString& t, MultisetInt permitidos);
ColaInt RecorridaDFS(GrafoInt grafo, int origen);
