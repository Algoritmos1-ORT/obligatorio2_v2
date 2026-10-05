#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"
#include "mem_tracking_fixture.hpp"
#include "pruebas_complejidad.hpp"

using namespace pruebas;

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

TEST_CASE("MultisetInt: operaciones balancean memoria", "[memory][file:multiset]")
{
    checkMemoriaEjecucion([] {
        MultisetInt values = crearMultisetInt();
        agregar(values, 3, 1);
        MultisetInt copy = clon(values);
        destruir(copy);
        destruir(values);
    });
}

TEST_CASE("MultisetInt: complejidad", "[benchmark][file:multiset]")
{
    ankerl::nanobench::Bench multisetBench;
    multisetBench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
    for (unsigned int count = 128; count <= 2048; count *= 2)
    {
        MultisetInt values = crearMultisetInt();
        for (unsigned int i = 0; i < count; ++i)
            agregar(values, static_cast<int>(i), 1);
        multisetBench.complexityN(count).run("MultisetInt pertenece", [&] {
            ankerl::nanobench::doNotOptimizeAway(pertenece(values, static_cast<int>(count / 2)));
        });
        destruir(values);
    }
    const auto fits = multisetBench.complexityBigO();
    REQUIRE_FALSE(fits.empty());
    CHECK((fits.front().name() == "O(1)" || fits.front().name() == "O(log n)"));
}
