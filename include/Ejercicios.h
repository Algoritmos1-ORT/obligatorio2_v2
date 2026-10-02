#pragma once

#include "PilaInt.h"
#include "ColaInt.h"
#include "ListaPosInt.h"
#include "TablaIntString.h"
#include "MultisetInt.h"
#include "GrafoInt.h"

bool EstaContenida(PilaInt p1, PilaInt p2);
void EliminarMaximos(ColaInt& c);
ListaPosInt ObtenerRepetidos(MultisetInt m);
void RestringirDominio(TablaIntString& t, MultisetInt permitidos);
ColaInt RecorridaDFS(GrafoInt grafo, int origen);