# Algoritmos y Estructuras de Datos I · UBA

Laboratorios de programación, especificación y trabajo práctico de implementación de la Facultad de Ciencias Exactas y Naturales.

## Recorrido de laboratorios

| Laboratorio | Contenido |
| --- | --- |
| [00 · LaTeX](Laboratorios/00-LaTeX/) | Notación, contratos y cuantificadores |
| [01 · Introducción](Laboratorios/01-Introduccion/) | Funciones, recursión y ciclos |
| [02 · Entrada y salida](Laboratorios/02-Entrada-Salida/) | Parámetros, centinelas y división euclídea |
| [03 · Vectores y archivos](Laboratorios/03-Vectores-Archivos/) | Secuencias, streams y procesamiento de archivos |
| [04 · Debugging](Laboratorios/04-Debugging/) | Defectos reproducibles y pruebas de valores completos |
| [05 · Invariantes](Laboratorios/05-Invariantes/) | Ciclos, ordenamiento y división |
| [06 · Testing](Laboratorios/06-Testing/) | Particiones, casos límite y diagnóstico de implementaciones |
| [07 · Matrices](Laboratorios/07-Matrices/) | Operaciones, tableros y recorridos |
| [08 · Cadenas](Laboratorios/08-Cadenas/) | Transformaciones, anagramas y subsecuencias |
| [09 · Complejidad](Laboratorios/09-Complejidad/) | Experimentos, CSV, gráficos y análisis de crecimiento |
| [10 · Búsqueda](Laboratorios/10-Busqueda/) | Binaria, jump search, picos y vectores rotados |
| [11 · Ordenamiento](Laboratorios/11-Ordenamiento/) | Bin packing y anagramas |

Cada laboratorio incluye su descripción de actividades, conceptos, código y comprobaciones. Se puede compilar por separado, sin abrir un proyecto enorme que mezcle todos los `main`.

## Trabajos y entregables

- [Esperando el Bondi](Trabajos-Practicos/Implementacion/): grillas, recorridos, tiempos y flotas.
- [Entregables de introducción](Entregables/01-Introduccion/): Fibonacci, división, intercambio, orden y rotación con sus programas de consola.

## Compilar

Requisitos: compilador C++14, CMake y una herramienta de construcción. Los proyectos funcionan en CLion o desde terminal:

```console
cmake -S Laboratorios/03-Vectores-Archivos -B build/vectores
cmake --build build/vectores
ctest --test-dir build/vectores --output-on-failure
```

En Windows, con CMake y el compilador en PATH:

```powershell
./herramientas/comprobar.ps1
```

Si se utiliza MinGW, agregar `-Generador "MinGW Makefiles"`. El script construye cada bloque en su carpeta, sin colisiones entre laboratorios y entregables. GoogleTest se incluye con su licencia, completo y sin necesidad de descargarlo al compilar.

Los gráficos del laboratorio09 usan matplotlib; el resto de los ejecutables no requiere Python. El diccionario de anagramas también está incluido, con su licencia y procedencia.

## Contexto

La colección parte de la cursada1C2022 y sus materiales de apoyo. Algunas guías conservan pie1C2021; los [créditos](CREDITOS.md) distinguen esas fuentes, las entregas históricas y las resoluciones posteriores. Este repositorio se centra en laboratorios y TP de implementación; no sustituye todas las prácticas teóricas ni una corrección docente.
