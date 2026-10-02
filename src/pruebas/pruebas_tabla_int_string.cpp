#include <algorithm>
#include <string>
#include <vector>

#include "catch_amalgamated.hpp"
#include "pruebas_auxiliares.hpp"
#include "mem_tracking_fixture.hpp"
#include "pruebas_complejidad.hpp"

using namespace pruebas;

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

TEST_CASE("tabla_int_string: operaciones balancean memoria", "[memory][file:tabla]")
{
    checkMemoriaEjecucion([] {
        TablaIntString table = crearTablaIntString(1);
        agregar(table, 3, "three");
        TablaIntString copy = clon(table);
        destruir(copy);
        destruir(table);
    });
}

TEST_CASE("tabla_int_string: referencias nanobench", "[.benchmark]")
{
    ankerl::nanobench::Bench tableBench;
    tableBench.output(nullptr).minEpochTime(std::chrono::milliseconds(1));
    for (unsigned int count = 128; count <= 2048; count *= 2)
    {
        TablaIntString table = crearTablaIntString(count);
        std::vector<std::string> labels;
        labels.reserve(count);
        for (unsigned int i = 0; i < count; ++i)
        {
            labels.push_back("value-" + std::to_string(i));
            agregar(table, static_cast<int>(i), labels.back().c_str());
        }
        tableBench.complexityN(count).run("TablaIntString lookup", [&] {
            ankerl::nanobench::doNotOptimizeAway(recuperar(table, static_cast<int>(count / 2)));
        });
        destruir(table);
    }
    const auto fits = tableBench.complexityBigO();
    REQUIRE_FALSE(fits.empty());
    CHECK((fits.front().name() == "O(1)" || fits.front().name() == "O(log n)"));
}
