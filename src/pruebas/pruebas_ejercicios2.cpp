#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"

using namespace pruebas;

TEST_CASE("TablaIntString: RestringirDominio conserva asociaciones permitidas", "[file:ejercicios2]")
{
    TablaIntString table = crearTablaIntString(4);
    agregar(table, 1, "one");
    agregar(table, 2, "two");
    agregar(table, 3, "three");
    MultisetInt allowed = crearMultisetInt();
    agregar(allowed, 2, 3);
    agregar(allowed, 3, 1);
    RestringirDominio(table, allowed);
    CHECK(cantidadElementos(table) == 2);
    CHECK_FALSE(estaDefinida(table, 1));
    CHECK(estaDefinida(table, 2));
    CHECK(estaDefinida(table, 3));
    CHECK(cantidadElementos(allowed) == 4);
    destruir(allowed);
    destruir(table);
}

TEST_CASE("GrafoInt: RecorridaDFS visita alcanzables una sola vez sin modificar grafo", "[file:ejercicios2][grafo]")
{
    GrafoInt graph = crearGrafo(6, true);
    addGraphEdges(graph, {{0, 1}, {0, 2}, {1, 3}, {2, 4}, {4, 1}});
    ColaInt traversal = RecorridaDFS(graph, 0);
    const std::vector<int> visitOrder = drain(traversal);
    CHECK(visitOrder.size() == 5);
    CHECK(visitOrder.front() == 0);
    std::vector<int> visited = visitOrder;
    std::sort(visited.begin(), visited.end());
    CHECK(visited == std::vector<int>{0, 1, 2, 3, 4});
    CHECK(cantidadAristas(graph) == 5);
    destruir(graph);
}
