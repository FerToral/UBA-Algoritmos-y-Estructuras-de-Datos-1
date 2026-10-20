# Laboratorio07 · Matrices y tableros

Operaciones sobre matrices representadas mediante vectores de filas.

| Ejercicio | Trabajo |
| --- | --- |
|Producto vectorial|Construir la matriz de productos entre dos vectores|
|Trasposición|Intercambiar filas y columnas, incluso en matrices rectangulares|
|Multiplicación|Combinar matrices con dimensiones compatibles|
|Promedio|Promediar vecinos según el contrato del ejercicio|
|Picos|Contar máximos locales|
|Triangular|Comprobar ceros debajo de la diagonal|
|Amenazas|Detectar reinas que comparten fila, columna o diagonal|
|Diagonales|Calcular la diferencia de sumas|
|Ta-te-ti|Comprobar estados y finalización de un tablero|
|Robot|Contar caminos en una grilla y detectar desbordamiento|

Las funciones están en `ejercicios.cpp` y las comprobaciones propias en `pruebas.cpp`. CMake compila GoogleTest desde la dependencia compartida.

```console
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Antes de recorrer una matriz hay que identificar si el contrato exige rectangularidad o una matriz cuadrada. La traspuesta rectangular no se obtiene intercambiando sobre la misma cantidad de filas. Las pruebas incluyen vacío, una celda, dimensiones incompatibles y relaciones independientes del conteo de caminos.

Los tests docentes y las guías originales se conservan en el archivo de la cursada; aquí se ejecutan pruebas propias sobre el código del módulo.
