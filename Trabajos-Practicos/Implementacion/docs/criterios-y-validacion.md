# Contratos del TP

## Viajes y unidades

Un viaje reúne mediciones temporales y posiciones. Tiempo total es la diferencia entre el instante máximo y el mínimo. Las distancias se expresan en kilómetros y los tiempos en segundos; para velocidad en km/h se realiza la conversión correspondiente.

El límite del ejercicio es estricto: una velocidad mayor que80km/h constituye exceso. No se redondea una duración fraccionaria si el contrato no lo pide.

## Grillas y recorridos

La grilla tiene n filas y m columnas, con nombres desde(1,1) hasta(n,m). La esquina inicial es noroeste y la final sudeste. Las pruebas rectangulares permiten detectar un intercambio accidental de parámetros.

Los saltos se miden por distancia euclídea entre nombres de celdas, mayor que uno. Por esa definición, una diagonal entre celdas vecinas puede contar como salto. No se sustituye por otra métrica sólo porque produzca un resultado más intuitivo.

## Corrección de mediciones

Se utilizan los dos puntos correctos temporalmente más cercanos. Los puntos marcados como incorrectos no pasan a ser referencias correctas por haber sido interpolados. Se conserva la elección histórica ante empates: la consigna no determina un desempate inequívoco para trayectorias no lineales.

## Comprobar

CTest fija el directorio de trabajo en la raíz del proyecto. Las regresiones comprueban precisión temporal, umbrales, grillas rectangulares, interpolación/extrapolación y exportación de coordenadas. Los archivos de salida de estas pruebas son generados; no son datos personales de viajes reales.

Los modelos y aproximaciones pertenecen al ejercicio académico, no a una herramienta de navegación de precisión.
