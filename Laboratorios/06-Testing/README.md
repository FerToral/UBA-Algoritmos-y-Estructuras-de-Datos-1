# Laboratorio06 · Testing

Práctica de particiones, límites y caja blanca: primalidad, puntajes, taxis, baldosas, electores y conteo por inclusión-exclusión.

## Actividades

- Primalidad: separar cero, uno, negativos, primos y compuestos.
- Puntaje: cubrir sus cuatro combinaciones de decisiones y el límite9/10.
- Taxis: encontrar contraejemplos en tres implementaciones defectuosas. La actividad pide diagnosticarlas, por eso sus salidas erróneas se conservan y se contrastan con el óptimo en comentarios.
- Baldosas: cubrir las combinaciones de divisibilidad, entradas no positivas y desbordamiento.
- Dragones: aplicar inclusión-exclusión con mínimo común múltiplo y contrastar con un conteo directo en dominios pequeños.
- Electores: comprobar calendario, límites de edad y fechas de nacimiento inválidas para una fecha de elección explícita.

## Ejecutar

```console
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

GoogleTest está incluido en `../../Dependencias/googletest`. Se compilan los seis ejercicios y las pruebas propias de `pruebas/regresiones.cpp`.

## Alcance de las comprobaciones

Pasar el test de una variante de taxis confirma que se reproduce el defecto documentado, no que sea un algoritmo correcto. Los casos(1,0,1),(1,1,0),(0,1,0) y(2,2,0) sirven para seguir el error a mano.

La función electoral recibe el año por parámetro. La firma histórica usa2017 como valor de la práctica; no es una regla electoral actual ni asesoramiento. Las decisiones de la actividad se estudian como un contrato académico.
