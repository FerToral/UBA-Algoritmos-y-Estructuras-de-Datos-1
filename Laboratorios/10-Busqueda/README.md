# Laboratorio10 · Búsqueda y complejidad

| Ejercicio | Implementación |
| --- | --- |
|1|Búsqueda binaria y jump search sobre un vector ordenado|
|2|Medición de ambas búsquedas para100,1000,10000 y100000 elementos|
|3|Experimentos STL compartidos con laboratorio09|
|4|Índice de algún pico, incluidos extremos y mesetas|
|5|Menor índice donde v[i]=i|
|6|Búsqueda en un vector ordenado y rotado|
|7|Índice del menor elemento estrictamente mayor que x|
|8|Hasta k valores más cercanos a x, excluyendo x y prefiriendo el menor ante empate|

Compilar con CMake y ejecutar CTest. `busqueda_demo` imprime CSV con tiempos medios por búsqueda, en milisegundos. Cada medida repite la operación10000 veces para reducir el efecto de resolución del reloj; el tiempo no es una prueba de corrección ni una constante universal.

## Contratos

Las búsquedas binarias y jump search presuponen orden ascendente. `puntoFijo` y `encontrarRotado` requieren valores distintos. No se recorre todo el vector para validar esas precondiciones dentro de cada búsqueda: eso ocultaría su complejidad logarítmica.

En pico, un elemento debe ser mayor o igual a sus vecinos; los extremos tienen uno y el vector unitario ninguno. El vacío devuelve-1. Los k cercanos se devuelven ordenados, con duplicados si pertenecen a valores distintos de x; se excluyen todas las apariciones de x.

| Algoritmo | Tiempo, sin contar construcción de datos |
| --- | --- |
|Binaria, punto fijo, rotado, sucesor, pico|O(log n)|
|Jump search|O(raíz de n)|
|k cercanos|O(log n+k), con deque para conservar orden|

Los experimentos y conceptos sobre `size`, `push_back`, acceso, borrado y `vector<bool>::flip` están en [laboratorio09](../09-Complejidad/).

[Contexto y créditos de la cursada](../../CREDITOS.md).
