#pragma once

/**
 * @brief Selecciona la representación de GrafoInt configurada para el build.
 *
 * @note Este archivo no debe ser modificado.
 */

#if defined(GRAFO_INT_LISTA)
#include "grafo_int_lista.hpp"
#elif defined(GRAFO_INT_MATRIZ)
#include "grafo_int_matriz.hpp"
#else
#error "Select GRAFO_INT_LISTA or GRAFO_INT_MATRIZ"
#endif

#include "pila_int.hpp"
#include "cola_int.hpp"
#include "lista_pos_int.hpp"
#include "multiset_int.hpp"
#include "tabla_int_string.hpp"
