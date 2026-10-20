#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

bool sonGrillasIguales(grilla& g1, grilla& g2);
double distanciaEntreCeldas(nombre n1, nombre n2);
bool esUnError(tiempo tmp, vector<tiempo> errores);
tuple<tuple<tiempo, gps>, tuple<tiempo, gps>> losDosPuntosMasCercanosCorrectos(viaje v, vector<tiempo>& errores, int k);
tuple<tiempo ,tiempo>  tiempoMinimoYMaximo(vector<tuple<tiempo, gps>>&  viaje);
vector<tuple<tiempo, gps> > ordenarViaje(vector<tuple<tiempo, gps> >& viaje);
double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);

void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);

#endif //TRANSPORTEURBANO_AUXILIARES_H
