#pragma once

#include <vector>

#include "Ejercicios.h"

namespace pruebas {

inline void pushAll(PilaInt& stack, const std::vector<int>& values)
{
    for (int value : values)
        push(stack, value);
}

inline void enqueueAll(ColaInt& queue, const std::vector<int>& values)
{
    for (int value : values)
        encolar(queue, value);
}

inline std::vector<int> drain(ColaInt queue)
{
    std::vector<int> values;
    while (!esVacia(queue))
    {
        values.push_back(principio(queue));
        desencolar(queue);
    }
    destruir(queue);
    return values;
}

inline std::vector<int> readList(ListaPosInt list)
{
    std::vector<int> values;
    for (unsigned int i = 0; i < cantidadElementos(list); ++i)
        values.push_back(elemento(list, i));
    return values;
}

inline void addGraphEdges(GrafoInt& graph,
                   const std::vector<std::pair<int, int>>& edges,
                   int weight = 1)
{
    for (const auto& edge : edges)
        agregarArista(graph, edge.first, edge.second, weight);
}

} // namespace pruebas
