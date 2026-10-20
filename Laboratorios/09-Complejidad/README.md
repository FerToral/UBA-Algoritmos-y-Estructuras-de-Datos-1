# Laboratorio09 · Complejidad

Seis actividades que relacionan operaciones, mediciones y órdenes de crecimiento.

| Ejercicio | Trabajo |
| --- | --- |
|1|Duplicados cuadrático y estimación c=tiempo/n² para datos ascendentes, descendentes, aleatorios e iguales|
|2|CSV para n=1,501,...,9501 y gráficos|
|3|Corte al encontrar un duplicado: comparar tiempo y cantidad de operaciones|
|4|Ejemplos O(1),O(n),O(n³),O(n log n) y tabla de mediciones/estimaciones|
|5|Medir size,push_back,pop_back,lectura/escritura por índice,flip,clear y empty|
|6|Subconjunto con suma dada: búsqueda exhaustiva y crecimiento exponencial|

## Ejecutar

Compilar con CMake y ejecutar desde esta carpeta:

```console
build/complejidad_demo duplicados > duplicados.csv
build/complejidad_demo ordenes > ordenes.csv
build/complejidad_demo stl > stl.csv
build/complejidad_demo subconjuntos > subconjuntos.csv
python graficar.py duplicados.csv duplicados.svg
```

El gráfico requiere matplotlib; C++ no tiene esa dependencia. En Windows usar `.exe`.

## Interpretar sin confundir estimaciones con mediciones

Sin corte se comparan n(n-1)/2 pares. Con corte, los valores iguales terminan en la primera comparación, pero un vector sin repetidos conserva el peor caso cuadrático. Mejorar el caso favorable no demuestra que mejoró el peor caso.

Para extrapolar a2200000000 elementos, usar c*n² con un c medido sobre entradas suficientemente grandes. No se reserva ese vector ni se afirma haberlo ejecutado. La constante depende de máquina, compilador, optimización, reloj y datos.

`cubico_estimado_s` extrapola desde n=100: **no es tiempo medido** para n=1000,10000 o100000. El experimento cúbico se limita a200 y el exponencial a24. La búsqueda de subconjuntos usa una entrada sin solución para recorrer el árbol completo: T(n)=2T(n-1)+O(1).

El costo de `push_back` es amortizado constante, aunque una realocación mueve elementos: se registran capacidades antes/después. Se compara lectura al principio, medio y final. Las operaciones muy pequeñas incluyen ruido del reloj y del consumo del resultado. `clear` tiene cota lineal general, pero con `int` el compilador puede eliminar destrucciones triviales; una medición no cambia la cota especificada. `flip` recorre los bits almacenados.

Compilar en Release, repetir y registrar el entorno. La construcción aleatoria usa semilla fija. El modo `datos-bpp 1000` genera entradas propias para laboratorio11, con capacidad150 y hasta un millón de objetos.

[Contexto y créditos de la cursada](../../CREDITOS.md).
