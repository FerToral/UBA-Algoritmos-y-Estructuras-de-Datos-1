# Laboratorio11 · Ordenamiento

Dos problemas para aplicar algoritmos de ordenamiento: asignación a contenedores y búsqueda de anagramas.

## Contenedores: Bin Packing

Leer cantidad, capacidad y volúmenes desde un archivo. Comparar Next Fit, Best Fit y Best Fit después de ordenar los objetos de mayor a menor. Medir el ordenamiento para distintos tamaños de entrada. Las heurísticas buscan una buena distribución, pero **no garantizan el mínimo** en todos los casos.

Se implementan insertion sort, selection sort y merge sort. Los dos primeros tienen peor caso cuadrático; merge sort es O(n log n) y usa memoria auxiliar O(n). Best Fit utiliza un multiset de capacidades restantes para localizar el contenedor adecuado en O(log n).

```console
build/ordenamiento_demo bpp datos/ejemplo-bpp.in
```

El archivo comienza con `cantidad capacidad`, seguido de exactamente esa cantidad de volúmenes positivos que no superen la capacidad. Los datos grandes pueden generarse con la herramienta del módulo de complejidad; no se incluyen binarios históricos.

## Anagramas

Comparar palabras mediante dos firmas: letras ordenadas y producto de primos distintos asignados a las letras. Recorrer el diccionario y listar todas las coincidencias, sin duplicar entradas.

```console
build/ordenamiento_demo anagramas listen datos/ingles.dic
```

El diccionario incluido contiene entradas inglesas a-z de CMUdict, con licencia y procedencia junto a los datos. No se presenta como una lista exhaustiva de todas las palabras del idioma. Se puede usar cualquier otro archivo de una palabra por línea que respete el alfabeto de la práctica.

El producto de primos se representa con bloques de entero grande, no con `int` o `double`: así las palabras largas no producen falsos resultados por desbordamiento o redondeo. La propiedad utilizada es la unicidad de la factorización en primos. La entrada debe contener sólo minúsculas a-z; el texto vacío tiene producto1.

## Compilar y comprobar

Usar CMake/CTest como en los demás laboratorios. Las pruebas comparan los tres ordenamientos con `std::sort`, verifican los ejemplos de contenedores, los dos métodos de anagramas y una palabra que supera la capacidad de un entero convencional.

[Contexto y créditos de la cursada](../../CREDITOS.md).
