# Laboratorio05 · Ciclos con invariantes

Seis actividades: detectar un pico interior, MCD por restas, mínimo de un intervalo, selección, bandera holandesa y división entera.

| Algoritmo | Invariante | Terminación |
| --- | --- | --- |
|Pico|El resultado resume los picos del prefijo recorrido|Longitud pendiente|
|MCD|Ambos valores son positivos y se conserva el MCD|La suma disminuye|
|Mínimo|El resultado minimiza el tramo ya visitado|Quedan menos posiciones|
|Selección|El prefijo está ordenado y no supera al sufijo|n-i|
|Bandera holandesa|Ceros, unos y doses ocupan regiones separadas|Disminuye la región sin clasificar|
|División|n=q*d+r, con resto no negativo|El resto disminuye|

`ordenar2` exige valores0,1,2: no es un ordenamiento general. `ordenar1` sí permite otros enteros. El mínimo devuelve la primera aparición en el intervalo cerrado pedido. El MCD de la práctica exige positivos y la división dividendo no negativo/divisor positivo.

Compilar con CMake y ejecutar CTest. Las pruebas contrastan las salidas con un criterio independiente y recorren vectores pequeños de todas las combinaciones de0,1,2.

La corrección de un ciclo requiere justificar inicialización, conservación, postcondición y terminación. Que algunos ejemplos pasen no reemplaza ese razonamiento.
