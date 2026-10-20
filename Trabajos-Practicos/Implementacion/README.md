# Esperando el Bondi

Trabajo práctico grupal de Algoritmos y Estructuras de Datos I, UBA,1C2022. Operaciones sobre viajes de colectivos, coordenadas, recorridos y grillas.

## Operaciones

1. Tiempo total de un viaje.
2. Distancia total entre mediciones consecutivas.
3. Detección de exceso de velocidad.
4. Flota activa para un instante.
5. Puntos de un recorrido sin cobertura.
6. Construcción de una grilla geográfica.
7. Cantidad de saltos entre sus celdas.
8. Corrección de mediciones mediante interpolación y extrapolación.

`ejercicios.cpp` implementa las operaciones; `auxiliares.cpp` y `definiciones.h` contienen funciones de apoyo y tipos. `testGrupo` reúne las regresiones propias. GoogleTest se comparte desde `../../Dependencias/googletest`.

## Compilar

```console
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Comprobado con CMake3.22 y GCC11.2 en Windows. Si se utiliza MinGW, su carpeta bin debe estar en PATH también al ejecutar CTest para encontrar las DLL.

## Contratos

Las distancias se expresan en kilómetros, el tiempo en segundos y la velocidad en km/h. Los bordes de la grilla y la conservación de mediciones requieren especial atención: se comprueban grillas rectangulares, orden temporal, umbrales y las exportaciones de coordenadas.

El contexto y las reglas de interpretación están en [criterios y validación](docs/criterios-y-validacion.md). Los originales, el enunciado y las pruebas docentes permanecen en el archivo histórico; este paquete conserva el código y las pruebas propias, sin atribuir el trabajo grupal a una única persona.
