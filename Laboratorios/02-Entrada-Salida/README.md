# Laboratorio02 · Entrada/salida y parámetros

Nueve actividades de repetición, lectura de datos y pasaje por valor o referencia.

| Ejercicio | Actividad |
| --- | --- |
|1|Leer diez notas entre0 y10, mostrar suma y promedio decimal|
|2|Leer una cantidad variable de notas hasta el centinela -1|
|3|Contar aprobados/reprobados, exigir al menos seis notas y evaluar si se pueden ampliar las plazas|
|4|Convertir un número binario a decimal|
|5|Calcular diámetro, circunferencia y área de un círculo|
|6|Comparar triplicar una copia con modificar una referencia|
|7|Intercambiar dos variables por referencia|
|8|Mostrar la sucesión de Collatz y sus pasos, de forma iterativa y recursiva|
|9|División euclídea por restas, iterativa y recursiva|

Compilar con CMake como los demás laboratorios y ejecutar `entrada_salida_demo 1`, cambiando el número por la actividad. Los ejercicios1–5 y9 toman los datos por entrada estándar. No se usan ni guardan notas de personas reales.

## Reglas de los ejercicios

La guía considera aprobado el valor **mayor que6**, no mayor o igual. Ampliar plazas exige **más de dos tercios**, no exactamente dos tercios. El promedio sin datos se informa como error. El binario se lee como cadena para no perder dígitos ni limitarlo al formato decimal de `int`.

Collatz recibe positivos. Se comprueba desbordamiento y se limita el uso de pila en la variante recursiva; una demostración con recursos finitos no prueba la conjetura. La división exige dividendo no negativo y divisor positivo. La versión recursiva por restas está limitada a cocientes pequeños; la iterativa evita ese límite de pila.

El ejemplo de la guía llama15 a los pasos de Collatz(11), pero enumera15 términos y14 transiciones. Aquí se cuentan14 pasos; la sucesión impresa conserva sus15 términos. La prueba comprueba el recorrido, no reproduce ese desfase del enunciado.

## Teoría

Un centinela controla cuándo termina la entrada y no forma parte de los datos. El paso por valor no modifica la variable original; una referencia sí permite hacerlo. La división conserva el invariante `dividendo_original = divisor * cociente + resto` y reduce el resto hasta que sea menor que el divisor.

[Contexto y créditos de la cursada](../../CREDITOS.md).
