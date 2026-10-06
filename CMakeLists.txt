cmake_minimum_required(VERSION 3.15)

project(Obligatorio2 VERSION 2.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_SOURCES
    src/main.cpp
    src/lib/catch_amalgamated.cpp
    src/lib/memplumber.cpp
    src/ejercicios/pila_int.cpp
    src/ejercicios/cola_int.cpp
    src/ejercicios/lista_pos_int.cpp
    src/ejercicios/multiset_int.cpp
    src/ejercicios/tabla_int_string.cpp
    src/ejercicios/ejercicios1.cpp
    src/ejercicios/ejercicios2.cpp
    src/pruebas/pruebas_pila_int.cpp
    src/pruebas/pruebas_cola_int.cpp
    src/pruebas/pruebas_lista_pos_int.cpp
    src/pruebas/pruebas_multiset_int.cpp
    src/pruebas/pruebas_tabla_int_string.cpp
    src/pruebas/pruebas_grafo_int.cpp
    src/pruebas/pruebas_ejercicios1.cpp
    src/pruebas/pruebas_ejercicios2.cpp
    src/pruebas/nanobench_impl.cpp
    src/pruebas/mem_tracking_fixture.cpp
    src/reporters/grading_reporter.cpp
    src/reporters/readable_reporter.cpp
)

function(add_obligatorio2_target target graph_source graph_definition)
    add_executable(${target} ${COMMON_SOURCES} ${graph_source})
    target_include_directories(${target} PRIVATE
        include
        include/lib
        include/pruebas
    )
    target_compile_definitions(${target} PRIVATE
        ${graph_definition}
        CATCH_AMALGAMATED_CUSTOM_MAIN
        CATCH_CONFIG_DEFAULT_REPORTER="readable"
    )
endfunction()

add_obligatorio2_target(obligatorio2_lista src/ejercicios/grafo_int_lista.cpp GRAFO_INT_LISTA)
add_obligatorio2_target(obligatorio2_matriz src/ejercicios/grafo_int_matriz.cpp GRAFO_INT_MATRIZ)

enable_testing()
add_test(NAME obligatorio2_lista COMMAND obligatorio2_lista --reporter compact)
add_test(NAME obligatorio2_matriz COMMAND obligatorio2_matriz --reporter compact)