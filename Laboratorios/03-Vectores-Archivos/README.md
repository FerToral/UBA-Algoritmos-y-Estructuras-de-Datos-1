# Laboratorio03 · Vectores y archivos

Quince actividades que conectan secuencias en memoria con lectura y escritura por streams.

| Números | Actividad y función |
| --- | --- |
|1–3|Divisibilidad de todos los elementos, máximo y reverso|
|4–6|Rotación hacia la izquierda, orden creciente/decreciente y factores primos|
|7–9|Presentar un vector, leer enteros separados por espacios y guardar su representación|
|10|Encontrar el primer elemento donde la suma acumulada supera la suma restante|
|11–12|Frecuencias de números y apariciones de una palabra|
|13|Promediar secuencias de igual longitud sin cargarlas en vectores|
|14|Intercalar dos archivos ordenados mediante lectura secuencial|
|15|Obtener la intersección sin repetidos de dos secuencias|

`ejercicios.h` expone versiones sobre streams y envoltorios para archivos. Esto permite probar la lógica con `istringstream` y usar los mismos algoritmos con `ifstream`. Los datos incluidos en `datos/` son ejemplos propios pequeños.

```console
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
build/vectores_archivos_demo datos/numeros.in
```

En Windows, usar el ejecutable `.exe`. Un segundo argumento escribe una versión rotada en la ruta indicada: elegir una salida nueva, no un original histórico.

## Formatos y decisiones

- `leerVector` admite enteros separados por blancos; rechaza un token inválido.
- `guardarVector` escribe la presentación pedida: `[1, 2, 5, 65]`. No es el formato de entrada de `leerVector`.
- La rotación normaliza vueltas completas; un k negativo rota en sentido contrario.
- El divisor debe ser distinto de cero y el máximo requiere un vector no vacío.
- En el ejercicio10 se incluye el elemento actual en la suma acumulada, de acuerdo con el ejemplo de la guía: `[1,2,3,4]` devuelve3. Si nunca se produce el cruce, se informa un error.
- La búsqueda de palabras compara tokens exactos; no elimina puntuación ni cambia mayúsculas.
- El promedio exige igual longitud y la mezcla exige entradas ordenadas. Se comprueban antes de guardar el archivo de salida.
- La intersección devuelve cada valor una vez, en su orden de aparición en la segunda secuencia.

## Conceptos

Leer con `while (entrada >> valor)` evita procesar un dato viejo al llegar al final del archivo. `eof()` no predice si la siguiente extracción será válida. Los ejercicios13–14 conservan sólo los valores actuales de los archivos de entrada; el buffer temporal de salida permite detectar un error antes de sustituir un archivo destino.

[Contexto y créditos de la cursada](../../CREDITOS.md).
