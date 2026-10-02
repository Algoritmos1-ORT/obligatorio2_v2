#pragma once

#if defined(GRAFO_INT_LISTA)
#include "GrafoIntLista.h"
#elif defined(GRAFO_INT_MATRIZ)
#include "GrafoIntMatriz.h"
#else
#error "Select GRAFO_INT_LISTA or GRAFO_INT_MATRIZ"
#endif

#include "PilaIntImp.h"
#include "ColaIntImp.h"
#include "ListaPosIntImp.h"
#include "MultisetIntImp.h"
#include "TablaIntStringImp.h"