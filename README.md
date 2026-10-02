# Obligatorio 2

Segundo obligatorio de **Estructuras de Datos y Algoritmos 1**, Facultad de Ingeniería, ORT Uruguay. El proyecto migra las consignas de `2026s1_Ejercicios2` a CMake y admite Linux, macOS y Windows.

## Entregas

Completar las implementaciones en `src/ejercicios`. No modificar headers, firmas, parámetros ni acceder a la representación de un TAD desde una función que lo recibe. Cada archivo `.cpp` define sus propios `struct`; las funciones auxiliares y sus contratos pre/pos deben quedar en el `.cpp` correspondiente.

1. `pila_int.cpp`: implementar `PilaInt`; `push`, `top`, `pop` y `cantidadElementos` deben ser $O(1)$ en el peor caso. La especificación no es acotada.
2. `ejercicios.cpp`: implementar `EstaContenida`. Respetar multiplicidades, no modificar las pilas y no usar estructuras auxiliares aparte de `PilaInt`.
3. `cola_int.cpp`: implementar `ColaInt`; `encolar`, `principio`, `desencolar` y `cantidadElementos` deben ser $O(1)$ en el peor caso. La especificación no es acotada.
4. `ejercicios.cpp`: implementar `EliminarMaximos`, preservando el orden relativo y usando únicamente `ColaInt` como estructura auxiliar.
5. `lista_pos_int.cpp`: implementar `ListaPosInt`; `elemento` y `cantidadElementos` deben ser $O(1)$ en el peor caso. La especificación no es acotada.
6. `multiset_int.cpp`: implementar `MultisetInt`; `agregar`, `borrar` y `pertenece` deben ser $O(log n)$ en promedio, y `cantidadElementos` $O(1)$. La especificación no es acotada.
7. `ejercicios.cpp`: implementar `ObtenerRepetidos`, sin elementos repetidos en el resultado y sin usar estructuras auxiliares aparte de `MultisetInt` y `ListaPosInt`.
8. `tabla_int_string.cpp`: implementar `TablaIntString` con hashing abierto; `estaDefinida` y `recuperar` deben ser $O(1)$ en promedio. El tamaño esperado se recibe al crear la tabla, pero pueden agregarse más elementos.
9. `ejercicios.cpp`: implementar `RestringirDominio` sin modificar el multiset recibido.
10. `grafo_int_lista.cpp`: implementar `GrafoInt` con listas de adyacencia. La especificación es acotada.
11. `grafo_int_matriz.cpp`: implementar `GrafoInt` con matrices de adyacencia. La especificación es acotada.
12. `ejercicios.cpp`: implementar `RecorridaDFS`, sin modificar el grafo. Debe funcionar con ambas representaciones.

Todos los ejercicios son obligatorios. Cada TAD debe estar completamente implementado para poder probar los ejercicios que lo usan. Las pruebas propias de docentes pueden agregarse en `src/pruebas`; las pruebas incluidas son una base y no agotan los casos límite.

## Requisitos

- CMake 3.15 o posterior y compilador C++17.
- Catch2 para pruebas, MemPlumber para detectar fugas y nanobench para mediciones de complejidad. Las tres dependencias están incluidas en `include/lib` y `src/lib`.

## Compilar y ejecutar

Desde la raíz del proyecto:

```sh
cmake -S . -B build
cmake --build build
```

Se generan dos ejecutables, uno por representación del grafo:

```sh
./build/obligatorio2_lista
./build/obligatorio2_matriz
```

En Windows con Visual Studio, los ejecutables quedan en `build/Debug/obligatorio2_lista.exe` y `build/Debug/obligatorio2_matriz.exe`.

Catch2 permite filtrar las pruebas por etiqueta. Por ejemplo:

```sh
./build/obligatorio2_lista "[file:cola]"
./build/obligatorio2_matriz "[file:grafo]"
./build/obligatorio2_lista "[memory]"
```

Para emitir únicamente el porcentaje de pruebas aprobadas:

```sh
./build/obligatorio2_lista --reporter grading
```

Los benchmarks nanobench son ocultos para las ejecuciones normales. Para ejecutarlos explícitamente:

```sh
./build/obligatorio2_lista "[.benchmark]"
```

## Entrega

Una entrega debe compilar en una copia limpia del proyecto. Entregar únicamente los archivos `.cpp` de `src/ejercicios` asociados a los ejercicios requeridos por el curso; no incluir cambios a headers, pruebas, dependencias ni configuración. Las funciones de los ejercicios 2, 4, 7, 9 y 12 están agrupadas en `ejercicios.cpp`.