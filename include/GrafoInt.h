#pragma once
// NOTA: Este archivo no debe ser modificado

#include "Implementaciones.h"

struct _representacionGrafoInt;
typedef struct _representacionGrafoInt* GrafoInt;

// PRE: numVertices >= 0 (0 es un grafo sin vertices)
// POS: retorna un nuevo grafo vacío de enteros positivos con numVertices vértices y sin aristas
//      si dirigido = true, el grafo es dirigido; no dirigido en caso contrario
GrafoInt crearGrafo(int numVertices, bool dirigido);

// PRE: 0 <= origen < numVertices, 0 <= destino < numVertices, 0 <= peso
// POS: agrega una arista desde origen hacia destino con el peso dado.
//      Si ya existe, actualiza el peso.
void agregarArista(GrafoInt& grafo, int origen, int destino, int peso);

// PRE: 0 <= origen < numVertices, 0 <= destino < numVertices
// POS: elimina la arista entre origen y destino si existe; no hace nada en caso contrario
void eliminarArista(GrafoInt& grafo, int origen, int destino);

// PRE: 0 <= origen < numVertices, 0 <= destino < numVertices
// POS: retorna true si existe una arista desde origen hacia destino; false en caso contrario
bool tieneArista(GrafoInt grafo, int origen, int destino);

// PRE: 0 <= origen < numVertices, 0 <= destino < numVertices
// POS: retorna el peso de la arista si existe; -1 en caso contrario
int pesoArista(GrafoInt grafo, int origen, int destino);

// PRE: 0 <= vertice < numVertices
// POS: retorna el grado de salida del vértice (cantidad de vecinos alcanzables)
int cantidadConexiones(GrafoInt grafo, int vertice);

// PRE: 0 <= vertice < numVertices
// POS: retorna un arreglo de vértices adyacentes al dado
//      en grafos dirigidos son los vértices alcanzables
int* vecinos(GrafoInt grafo, int vertice);

// PRE: -
// POS: retorna true si el grafo es dirigido; false en caso contrario
bool esDirigido(GrafoInt grafo);

// PRE: -
// POS: retorna la cantidad de vértices del grafo
int cantidadVertices(GrafoInt grafo);

// PRE: -
// POS: retorna la cantidad de aristas del grafo
int cantidadAristas(GrafoInt grafo);

// PRE: -
// POS: retorna una copia del grafo sin compartir memoria
GrafoInt clon(GrafoInt grafo);

// PRE: -
// POS: libera la memoria del grafo
void destruir(GrafoInt& grafo);
