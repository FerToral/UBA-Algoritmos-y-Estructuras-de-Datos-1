# Laboratorio04 · Debugging

Diez actividades de depuración. La guía se apoya en programas y casos de prueba: el trabajo consiste en identificar el defecto, reproducirlo y comprobar el resultado corregido.

| Ejercicio | Función y situación a revisar |
| --- | --- |
|1|Orden creciente o decreciente; vectores vacíos, iguales y con cambios de sentido|
|2|Primalidad; cero, uno, negativos y límites del ciclo|
|3|Pertenencia; el último elemento y el vector vacío|
|4|Desvío estándar poblacional, sin división entera ni denominador incorrecto|
|5|Fibonacci; casos base y resultados que no entran en32bits|
|6|MCD con cero y signos negativos|
|7|Acumular el doble de los elementos positivos y pares|
|8|Contar palabras sin procesar otra vez el último token|
|9|Promediar mediciones estrictamente entre0 y1|
|10|Devolver por referencia la proporción de positivos, conservando la parte decimal|

Las funciones actuales trabajan sobre datos o streams recibidos como parámetros. No dependen de rutas absolutas ni de los archivos privados originales. Las pruebas se compilan con CMake y se ejecutan con CTest.

## Qué observar con el depurador

Poner un breakpoint antes del ciclo, observar índices y acumuladores y avanzar sobre el último elemento. Comparar `=` con `+=`, el valor antes/después de una extracción y los tipos de ambos operandos de una división. En el ejercicio10, verificar que el argumento de salida sea una referencia tanto en la declaración como en la definición.

La batería histórica de referencia convertía algunos resultados numéricos a `bool` antes de compararlos: dos números diferentes pero no nulos podían pasar como iguales. Las pruebas actuales comparan los valores completos, incluido Fibonacci50. No se usa el contador de tests como sustituto de revisar qué comprueban.

Se rechazan conjuntos vacíos cuando no existe un promedio/desvío; la fracción vacía se define como0, como en los casos de la actividad. El MCD(0,0) también devuelve0 por convención. El desvío divide por n, no por n-1.

[Contexto y créditos de la cursada](../../CREDITOS.md).
