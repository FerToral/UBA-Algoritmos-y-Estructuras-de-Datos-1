# Laboratorio 01 · Introducción a C++

Primeras funciones y comparación entre recursión, `while` y `for`.

| Ejercicio | Trabajo |
| --- | --- |
|1|Compilar un programa que calcule el siguiente de un entero|
|2|Recibir dos enteros y sumarlos|
|3|Sumarlos si el primero es mayor; en otro caso multiplicarlos|
|4|Determinar si un natural es primo|
|5|Calcular Fibonacci con tres formas de repetición|
|6|Sumar los impares estrictamente menores que n|
|7|Sumar los divisores positivos de n|
|8|Calcular combinatorios con la identidad de Pascal y una alternativa iterativa|

Las funciones están en `ejercicios.cpp`; `main.cpp` muestra una demostración. La versión recursiva de Fibonacci usa acumuladores y la del combinatorio memoriza resultados para evitar recalcular el mismo subproblema. Los enteros tienen límites: Fibonacci admite hasta93 y la fila de Pascal hasta67 en `uint64_t`. Las sumas de divisores requieren n positivo; sus versiones recursivas son para entradas pequeñas por el uso de la pila.

```console
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Conceptos

Pasar parámetros y devolver resultados permite probar una función sin mezclarla con entrada/salida. Un ciclo y una recursión pueden expresar la misma relación, pero usan memoria de distinta manera. Antes de operar conviene establecer el dominio y el tipo capaz de representar el resultado.

[Contexto y créditos de la cursada](../../CREDITOS.md).
