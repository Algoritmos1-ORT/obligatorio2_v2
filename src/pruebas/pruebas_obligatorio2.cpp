#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include "Ejercicios.h"
#include "mem_tracking_fixture.hpp"

namespace {

void pushAll(PilaInt& stack, const std::vector<int>& values)
{
    for (int value : values)
        push(stack, value);
}

void enqueueAll(ColaInt& queue, const std::vector<int>& values)
{
    for (int value : values)
        encolar(queue, value);
}

std::vector<int> drain(ColaInt queue)
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

std::vector<int> readList(ListaPosInt list)
{
    std::vector<int> values;
    for (unsigned int i = 0; i < cantidadElementos(list); ++i)
        values.push_back(elemento(list, i));
    return values;
}

void addGraphEdges(GrafoInt& graph,
                   const std::vector<std::pair<int, int>>& edges,
                   int weight = 1)
{
    for (const auto& edge : edges)
        agregarArista(graph, edge.first, edge.second, weight);
}

} // namespace

TEST_CASE("PilaInt: operaciones, clon y liberacion", "[file:pila]")
{
    PilaInt stack = crearPilaInt();
    REQUIRE(esVacia(stack));
    REQUIRE(cantidadElementos(stack) == 0);

    pushAll(stack, {4, -2, 4});
    REQUIRE_FALSE(esVacia(stack));
    CHECK(top(stack) == 4);
    CHECK(cantidadElementos(stack) == 3);

    PilaInt copy = clon(stack);
    pop(copy);
    CHECK(cantidadElementos(copy) == 2);
    CHECK(cantidadElementos(stack) == 3);
    CHECK(top(stack) == 4);
    destruir(copy);
    pop(stack);
    pop(stack);
    pop(stack);
    CHECK(esVacia(stack));
    destruir(stack);
}

TEST_CASE("ColaInt: operaciones, clon y liberacion", "[file:cola]")
{
    ColaInt queue = crearColaInt();
    REQUIRE(esVacia(queue));
    REQUIRE(cantidadElementos(queue) == 0);

    enqueueAll(queue, {4, -2, 4});
    CHECK(principio(queue) == 4);
    CHECK(cantidadElementos(queue) == 3);

    ColaInt copy = clon(queue);
    desencolar(copy);
    CHECK(principio(copy) == -2);
    CHECK(principio(queue) == 4);
    destruir(copy);
    CHECK(drain(queue) == std::vector<int>{4, -2, 4});
}

TEST_CASE("ListaPosInt: insercion posicional, borrado y clon", "[file:lista]")
{
    ListaPosInt list = crearListaPosInt();
    agregar(list, 2, 0);
    agregar(list, 4, 1);
    agregar(list, 3, 1);
    agregar(list, 5, 99);
    CHECK(readList(list) == std::vector<int>{2, 3, 4, 5});
    CHECK(cantidadElementos(list) == 4);

    ListaPosInt copy = clon(list);
    borrar(copy, 0);
    borrar(copy, 99);
    CHECK(readList(copy) == std::vector<int>{3, 4, 5});
    CHECK(readList(list) == std::vector<int>{2, 3, 4, 5});
    destruir(copy);
    destruir(list);
}

TEST_CASE("MultisetInt: frecuencias y operaciones de conjuntos", "[file:multiset]")
{
    MultisetInt left = crearMultisetInt();
    MultisetInt right = crearMultisetInt();
    agregar(left, -1, 1);
    agregar(left, 2, 3);
    agregar(left, 5, 2);
    agregar(right, 2, 1);
    agregar(right, 3, 1);
    agregar(right, 5, 3);

    CHECK(pertenece(left, -1));
    CHECK_FALSE(pertenece(left, 3));
    CHECK(cantidadElementos(left) == 6);
    CHECK_FALSE(esVacio(left));
    CHECK(contenidoEn(right, left) == false);

    MultisetInt united = unionConjuntos(left, right);
    MultisetInt common = interseccionConjuntos(left, right);
    MultisetInt difference = diferenciaConjuntos(left, right);
    CHECK(cantidadElementos(united) == 8);
    CHECK(cantidadElementos(common) == 3);
    CHECK(cantidadElementos(difference) == 3);
    CHECK(pertenece(common, 2));
    CHECK(pertenece(difference, -1));

    borrar(left, 2);
    CHECK(cantidadElementos(left) == 5);
    CHECK(pertenece(left, 2));
    MultisetInt copy = clon(left);
    borrar(copy, 2);
    CHECK(cantidadElementos(copy) == 4);
    CHECK(cantidadElementos(left) == 5);

    destruir(copy);
    destruir(difference);
    destruir(common);
    destruir(united);
    destruir(right);
    destruir(left);
}

TEST_CASE("TablaIntString: agregar, actualizar, borrar y clonar", "[file:tabla]")
{
    TablaIntString table = crearTablaIntString(2);
    agregar(table, -3, "negative");
    agregar(table, 5, "five");
    agregar(table, 7, "seven");
    agregar(table, 5, "updated");
    CHECK(cantidadElementos(table) == 3);
    CHECK(estaDefinida(table, -3));
    CHECK(std::string(recuperar(table, 5)) == "updated");
    CHECK_FALSE(estaDefinida(table, 8));

    TablaIntString copy = clon(table);
    borrar(copy, 5);
    CHECK_FALSE(estaDefinida(copy, 5));
    CHECK(estaDefinida(table, 5));
    CHECK(cantidadElementos(copy) == 2);
    destruir(copy);
    borrar(table, -3);
    CHECK(cantidadElementos(table) == 2);
    destruir(table);
}

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

TEST_CASE("Estructuras: operaciones balancean memoria", "[memory]")
{
    checkMemoriaEjecucion([] {
        PilaInt stack = crearPilaInt();
        push(stack, 3);
        PilaInt stackCopy = clon(stack);
        destruir(stackCopy);
        destruir(stack);
    });
    checkMemoriaEjecucion([] {
        ColaInt queue = crearColaInt();
        encolar(queue, 3);
        ColaInt queueCopy = clon(queue);
        destruir(queueCopy);
        destruir(queue);
    });
    checkMemoriaEjecucion([] {
        ListaPosInt list = crearListaPosInt();
        agregar(list, 3, 0);
        ListaPosInt listCopy = clon(list);
        destruir(listCopy);
        destruir(list);
    });
    checkMemoriaEjecucion([] {
        MultisetInt values = crearMultisetInt();
        agregar(values, 3, 1);
        MultisetInt copy = clon(values);
        destruir(copy);
        destruir(values);
    });
    checkMemoriaEjecucion([] {
        TablaIntString table = crearTablaIntString(1);
        agregar(table, 3, "three");
        TablaIntString copy = clon(table);
        destruir(copy);
        destruir(table);
    });
}

TEST_CASE("Complejidad de operaciones: referencias nanobench", "[.benchmark]")
{
    auto measuredGrowth = [](const std::string& label, auto operation)
    {
        ankerl::nanobench::Bench bench;
        bench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
        for (unsigned int count = 128; count <= 2048; count *= 2)
            bench.complexityN(count).run(label, [&] { operation(count); });

        const auto fits = bench.complexityBigO();
        REQUIRE_FALSE(fits.empty());
        return fits.front().name();
    };

    const std::string stackGrowth = measuredGrowth("PilaInt push + pop", [](unsigned int count) {
        PilaInt stack = crearPilaInt();
        for (unsigned int i = 0; i < count; ++i)
            push(stack, static_cast<int>(i));
        for (unsigned int i = 0; i < count; ++i)
            pop(stack);
        ankerl::nanobench::doNotOptimizeAway(cantidadElementos(stack));
        destruir(stack);
    });
    CHECK((stackGrowth == "O(n)" || stackGrowth == "O(1)"));

    const std::string queueGrowth = measuredGrowth("ColaInt enqueue + dequeue", [](unsigned int count) {
        ColaInt queue = crearColaInt();
        for (unsigned int i = 0; i < count; ++i)
            encolar(queue, static_cast<int>(i));
        for (unsigned int i = 0; i < count; ++i)
            desencolar(queue);
        ankerl::nanobench::doNotOptimizeAway(cantidadElementos(queue));
        destruir(queue);
    });
    CHECK((queueGrowth == "O(n)" || queueGrowth == "O(1)"));

    ankerl::nanobench::Bench listBench;
    listBench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
    for (unsigned int count = 128; count <= 2048; count *= 2)
    {
        ListaPosInt list = crearListaPosInt();
        for (unsigned int i = 0; i < count; ++i)
            agregar(list, static_cast<int>(i), i);
        listBench.complexityN(count).run("ListaPosInt element + count", [&] {
            ankerl::nanobench::doNotOptimizeAway(elemento(list, count - 1));
            ankerl::nanobench::doNotOptimizeAway(cantidadElementos(list));
        });
        destruir(list);
    }
    const auto listFits = listBench.complexityBigO();
    REQUIRE_FALSE(listFits.empty());
    CHECK((listFits.front().name() == "O(1)" || listFits.front().name() == "O(n)"));

    ankerl::nanobench::Bench multisetBench;
    multisetBench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
    ankerl::nanobench::Bench tableBench;
    tableBench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
    for (unsigned int count = 128; count <= 2048; count *= 2)
    {
        MultisetInt values = crearMultisetInt();
        TablaIntString table = crearTablaIntString(count);
        std::vector<std::string> labels;
        labels.reserve(count);
        for (unsigned int i = 0; i < count; ++i)
        {
            agregar(values, static_cast<int>(i), 1);
            labels.push_back("value-" + std::to_string(i));
            agregar(table, static_cast<int>(i), labels.back().c_str());
        }

        multisetBench.complexityN(count).run("MultisetInt pertenece", [&] {
            ankerl::nanobench::doNotOptimizeAway(pertenece(values, static_cast<int>(count / 2)));
        });
        tableBench.complexityN(count).run("TablaIntString lookup", [&] {
            ankerl::nanobench::doNotOptimizeAway(recuperar(table, static_cast<int>(count / 2)));
        });
        destruir(values);
        destruir(table);
    }
    const auto multisetFits = multisetBench.complexityBigO();
    const auto tableFits = tableBench.complexityBigO();
    REQUIRE_FALSE(multisetFits.empty());
    REQUIRE_FALSE(tableFits.empty());
    CHECK((multisetFits.front().name() == "O(log n)" || multisetFits.front().name() == "O(1)"));
    CHECK((tableFits.front().name() == "O(1)" || tableFits.front().name() == "O(log n)"));
}