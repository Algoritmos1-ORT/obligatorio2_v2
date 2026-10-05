#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"
#include "mem_tracking_fixture.hpp"
#include "pruebas_complejidad.hpp"

using namespace pruebas;

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

TEST_CASE("ColaInt: operaciones balancean memoria", "[memory][file:cola]")
{
    checkMemoriaEjecucion([] {
        ColaInt queue = crearColaInt();
        encolar(queue, 3);
        ColaInt queueCopy = clon(queue);
        destruir(queueCopy);
        destruir(queue);
    });
}

TEST_CASE("ColaInt: complejidad", "[benchmark][file:cola]")
{
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
}
