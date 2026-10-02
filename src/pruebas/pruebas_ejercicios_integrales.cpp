#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"

using namespace pruebas;

TEST_CASE("EstaContenida: respeta multiplicidades y no modifica pilas", "[file:ejercicios]")
{
    PilaInt required = crearPilaInt();
    PilaInt available = crearPilaInt();
    pushAll(required, {1, 7, 4, 2, 7, 4, 4, 7});
    pushAll(available, {7, 3, 7, 2, 4, 4, 4, 7, 1, 4, 8});
    CHECK(EstaContenida(required, available));
    CHECK(cantidadElementos(required) == 8);
    CHECK(cantidadElementos(available) == 11);

    PilaInt tooFew = crearPilaInt();
    pushAll(tooFew, {1, 2, 2, 2});
    PilaInt oneEach = crearPilaInt();
    pushAll(oneEach, {1, 2, 2});
    CHECK_FALSE(EstaContenida(tooFew, oneEach));
    PilaInt empty = crearPilaInt();
    CHECK(EstaContenida(empty, oneEach));
    destruir(empty);
    destruir(tooFew);
    destruir(oneEach);
    destruir(required);
    destruir(available);
}

TEST_CASE("EliminarMaximos: elimina todas las apariciones y conserva orden", "[file:ejercicios]")
{
    ColaInt queue = crearColaInt();
    enqueueAll(queue, {5, 9, 3, 9, 2, 9, 1});
    EliminarMaximos(queue);
    CHECK(drain(queue) == std::vector<int>{5, 3, 2, 1});

    ColaInt allMaximum = crearColaInt();
    enqueueAll(allMaximum, {-4, -4, -4});
    EliminarMaximos(allMaximum);
    CHECK(esVacia(allMaximum));
    destruir(allMaximum);
}

TEST_CASE("ObtenerRepetidos: devuelve valores repetidos una sola vez", "[file:ejercicios]")
{
    MultisetInt values = crearMultisetInt();
    agregar(values, 7, 4);
    agregar(values, -2, 1);
    agregar(values, 3, 2);
    agregar(values, 0, 3);
    ListaPosInt repeated = ObtenerRepetidos(values);
    const std::vector<int> result = readList(repeated);
    CHECK(result.size() == 3);
    CHECK(std::count(result.begin(), result.end(), 7) == 1);
    CHECK(std::count(result.begin(), result.end(), 3) == 1);
    CHECK(std::count(result.begin(), result.end(), 0) == 1);
    CHECK(std::find(result.begin(), result.end(), -2) == result.end());
    destruir(repeated);
    destruir(values);
}

TEST_CASE("RestringirDominio: conserva asociaciones permitidas", "[file:ejercicios]")
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

TEST_CASE("RecorridaDFS: visita alcanzables una sola vez sin modificar grafo", "[file:ejercicios][grafo]")
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
