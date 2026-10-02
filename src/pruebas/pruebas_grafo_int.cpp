#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"
#include "mem_tracking_fixture.hpp"

using namespace pruebas;

TEST_CASE("GrafoInt: aristas, pesos, vecinos y clon", "[file:grafo]")
{
    GrafoInt graph = crearGrafo(5, true);
    addGraphEdges(graph, {{0, 1}, {0, 3}, {1, 4}});
    agregarArista(graph, 0, 1, 8);
    CHECK(esDirigido(graph));
    CHECK(cantidadVertices(graph) == 5);
    CHECK(cantidadAristas(graph) == 3);
    CHECK(cantidadConexiones(graph, 0) == 2);
    CHECK(tieneArista(graph, 0, 1));
    CHECK(pesoArista(graph, 0, 1) == 8);
    CHECK(pesoArista(graph, 2, 0) == -1);

    int* adjacent = vecinos(graph, 0);
    std::vector<int> neighbors(adjacent, adjacent + cantidadConexiones(graph, 0));
    delete[] adjacent;
    std::sort(neighbors.begin(), neighbors.end());
    CHECK(neighbors == std::vector<int>{1, 3});

    GrafoInt copy = clon(graph);
    eliminarArista(copy, 0, 1);
    CHECK_FALSE(tieneArista(copy, 0, 1));
    CHECK(tieneArista(graph, 0, 1));
    destruir(copy);
    destruir(graph);
}

TEST_CASE("GrafoInt no dirigido: aristas simetricas y eliminacion", "[file:grafo]")
{
    GrafoInt graph = crearGrafo(3, false);
    agregarArista(graph, 0, 2, 6);
    CHECK_FALSE(esDirigido(graph));
    CHECK(tieneArista(graph, 0, 2));
    CHECK(tieneArista(graph, 2, 0));
    CHECK(pesoArista(graph, 2, 0) == 6);
    CHECK(cantidadAristas(graph) == 1);
    eliminarArista(graph, 2, 0);
    CHECK_FALSE(tieneArista(graph, 0, 2));
    CHECK_FALSE(tieneArista(graph, 2, 0));
    CHECK(cantidadAristas(graph) == 0);
    destruir(graph);
}
