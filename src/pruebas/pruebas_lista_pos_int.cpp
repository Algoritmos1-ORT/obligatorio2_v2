#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"
#include "mem_tracking_fixture.hpp"
#include "pruebas_complejidad.hpp"

using namespace pruebas;

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

TEST_CASE("ListaPosInt: operaciones balancean memoria", "[memory][file:lista]")
{
    checkMemoriaEjecucion([] {
        ListaPosInt list = crearListaPosInt();
        agregar(list, 3, 0);
        ListaPosInt listCopy = clon(list);
        destruir(listCopy);
        destruir(list);
    });
}

TEST_CASE("ListaPosInt: complejidad", "[benchmark][file:lista]")
{
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
}
