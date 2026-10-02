#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"
#include "mem_tracking_fixture.hpp"
#include "pruebas_complejidad.hpp"

using namespace pruebas;

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

TEST_CASE("pila_int: operaciones balancean memoria", "[memory][file:pila]")
{
    checkMemoriaEjecucion([] {
        PilaInt stack = crearPilaInt();
        push(stack, 3);
        PilaInt stackCopy = clon(stack);
        destruir(stackCopy);
        destruir(stack);
    });
}

TEST_CASE("pila_int: referencias nanobench", "[.benchmark]")
{
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
}
