# Laboratorio08 · Cadenas

Doce consignas de transformación y comparación de texto.

| Actividad | Funciones |
| --- | --- |
|Separación e inversión de palabras|split, darVueltaPalabra|
|Orden relativo y agrupación|subsecuencia, agruparAnagramas|
|Caracteres repetidos y simetría|tieneRepetidos, esPalindromo|
|Rotación y prefijos|rotar, darVueltaK|
|Risas|risaMasLarga y lectura de datos|
|Adicionales|abueloLaino, cantidadDeFelicitaciones, middleOut|

## Ejecutar

Compilar con CMake y usar CTest. Los ejecutables `rotar` y `subsecuencia` permiten probar las actividades de consola por separado.

Los algoritmos se limitan a tamaño, inserción al final, limpieza y acceso por índice, sin usar `substr` para resolver rotación. Trabajan con caracteres de un byte, no con grafemas Unicode.

## Contratos y ejemplos

- `split` omite fragmentos vacíos e invertir palabras normaliza espacios.
- Los grupos de anagramas mantienen el orden de aparición y las repeticiones.
- El palíndromo es literal: no se eliminan automáticamente signos ni tildes.
- Risas busca la mayor alternancia contigua entre a y h; otros caracteres interrumpen el tramo.
- Abuelo Laino devuelve S/N y trata tanto i como I.
- Felicitaciones conserva los pares DR internos y busca cómo encadenar los extremos de los nombres. Se contrasta con permutaciones exhaustivas de entradas pequeñas.
- Middle Out conserva un intervalo del destino que sea subsecuencia del origen. El mínimo de movimientos es la longitud total menos el tramo conservable; multiconjuntos diferentes dan-1.

Las pruebas propias incluyen comparaciones independientes mediante permutaciones y búsqueda en anchura, además de las salidas esperadas de ejemplos pequeños.
