#include "auxiliares.h"
#include "definiciones.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

bool sonGrillasIguales(grilla &g1, grilla &g2) {
    bool sonIguales = true;
    int cantAparicionesEnG2 = 0;
    double epsilon = 0.0001;
    if (g1.size() != g2.size())
        return false;
    for (int i = 0; i < g1.size() && sonIguales; i++) {
        double esq1LatG1 = obtenerLatitud(get<0>(g1[i])),
               esq1LongG1 = obtenerLongitud(get<0>(g1[i])),
               esq2LatG1 = obtenerLatitud(get<1>(g1[i])),
               esq2LongG1 = obtenerLongitud(get<1>(g1[i]));
        for (int j = 0; j < g1.size(); j++) {

            double esq1LatG2 = obtenerLatitud(get<0>(g2[j])),
                   esq1LongG2 = obtenerLongitud(get<0>(g2[j])),
                   esq2LatG2 = obtenerLatitud(get<1>(g2[j])),
                   esq2LongG2 = obtenerLongitud(get<1>(g2[j]));
            if (get<2>(g1[i]) == get<2>(g2[j])) {
                if (abs(esq1LatG1 - esq1LatG2) <= epsilon &&
                    abs(esq1LongG1 - esq1LongG2) <= epsilon) {
                    if (abs(esq2LatG1 - esq2LatG2) <= epsilon &&
                        abs(esq2LongG1 - esq2LongG2) <= epsilon)
                        cantAparicionesEnG2++;
                }
            }
        }
        if (cantAparicionesEnG2 != 1)
            sonIguales = false;
        cantAparicionesEnG2 = 0;
    }
    return sonIguales;
}

bool esUnError(tiempo tmp, vector<tiempo> errores) {
    bool pertenece = false;
    int i = 0;

    while (i < errores.size() && !pertenece) {
        if (errores[i] == tmp)
            pertenece = true;
        i++;
    }

    return pertenece;
}

tuple<tuple<tiempo, gps>, tuple<tiempo, gps>>
losDosPuntosMasCercanosCorrectos(viaje v, vector<tiempo> &errores, int k) {
    tuple<tuple<tiempo, gps>, tuple<tiempo, gps>> puntosCercano;
    int ubicacionCercano, ubicacionCercano2;
    bool hayPuntoMasCercano = true;
    for (int j = 0; j < v.size(); j++) {
        if (!esUnError(obtenerTiempo(v[j]), errores)) {
            for (int l = 0; l < v.size() && hayPuntoMasCercano; l++) {
                if (!esUnError(obtenerTiempo(v[l]), errores)) {
                    if (abs(obtenerTiempo(v[j]) - obtenerTiempo(v[k])) >
                        abs(obtenerTiempo(v[l]) - obtenerTiempo(v[k]))) {
                        hayPuntoMasCercano = false;
                    }
                }
            }
            if (hayPuntoMasCercano)
                ubicacionCercano = j;
            hayPuntoMasCercano = true;
        }
    }

    for (int j = 0; j < v.size(); j++) {
        if (!esUnError(obtenerTiempo(v[j]), errores) && j != ubicacionCercano) {
            for (int l = 0; l < v.size() && hayPuntoMasCercano; l++) {
                if (!esUnError(obtenerTiempo(v[l]), errores) && l != ubicacionCercano) {
                    if (abs(obtenerTiempo(v[j]) - obtenerTiempo(v[k])) >
                        abs(obtenerTiempo(v[l]) - obtenerTiempo(v[k]))) {
                        hayPuntoMasCercano = false;
                    }
                }
            }
            if (hayPuntoMasCercano)
                ubicacionCercano2 = j;
            hayPuntoMasCercano = true;
        }
    }
    if (obtenerTiempo(v[ubicacionCercano]) < obtenerTiempo(v[ubicacionCercano2])) {
        get<0>(puntosCercano) = v[ubicacionCercano];
        get<1>(puntosCercano) = v[ubicacionCercano2];
    } else {
        get<1>(puntosCercano) = v[ubicacionCercano];
        get<0>(puntosCercano) = v[ubicacionCercano2];
    }

    return puntosCercano;
}

tuple<tiempo, tiempo> tiempoMinimoYMaximo(vector<tuple<tiempo, gps>> &viaje) {
    tiempo tmin = obtenerTiempo(viaje[0]), tmax = 0;

    for (int j = 0; j < viaje.size(); j++) {
        if (obtenerTiempo(viaje[j]) < tmin) {
            tmin = obtenerTiempo(viaje[j]);
        }
        if (obtenerTiempo(viaje[j]) > tmax) {
            tmax = obtenerTiempo(viaje[j]);
        }
    }

    return make_tuple(tmin, tmax);
}

nombre posicionEnlaGrilla(gps punto, grilla g) {
    int i = 0;
    bool encontrada = false;
    nombre nombreCeldaEncontrada;
    double latP = obtenerLatitud(punto), longP = obtenerLongitud(punto);
    double latInicioCelda, longInicioCelda, latFinCelda, longFinCelda;

    do {
        latInicioCelda = obtenerLatitud(get<0>(g[i]));
        longInicioCelda = obtenerLongitud(get<0>(g[i]));
        latFinCelda = obtenerLatitud(get<1>(g[i]));
        longFinCelda = obtenerLongitud(get<1>(g[i]));

        if (latFinCelda < latP && latP <= latInicioCelda) {
            if (longInicioCelda <= longP && longP < longFinCelda) {
                nombreCeldaEncontrada = get<2>(g[i]);
                encontrada = true;
            }
        }

        i++;
    } while (!encontrada && i < g.size());

    return nombreCeldaEncontrada;
}

double distanciaEntreCeldas(nombre n1, nombre n2) {
    return sqrt(pow(get<0>(n1) - get<0>(n2), 2) + pow(get<1>(n1) - get<1>(n2), 2));
}

vector<tuple<tiempo, gps>> ordenarViaje(vector<tuple<tiempo, gps>> &viaje) {
    int n = int(viaje.size());
    tuple<tiempo, gps> aux;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (obtenerTiempo(viaje[i]) > obtenerTiempo(viaje[j])) {
                aux = viaje[j];
                viaje[j] = viaje[i];
                viaje[i] = aux;
            }
        }
    }
    return viaje;
}

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1)*pi / 180.0;
    latitud2 = (latitud2)*pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) * cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud) {
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat - (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);
}

gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo) {
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for (int i = 0; i < g.size(); i++) {
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t" << esq1_lng << "\t" << esq2_lat << "\t" << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")" << endl;
    }
    myfile.close();
}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo) {
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for (int i = 0; i < recorridos.size(); i++) {
        for (int k = 0; k < recorridos[i].size(); k++) {
            lat = get<0>(recorridos[i][k]);
            lng = get<1>(recorridos[i][k]);

            myfile << i << "\t" << lat << "\t" << lng << endl;
        }
    }
    myfile.close();
}
