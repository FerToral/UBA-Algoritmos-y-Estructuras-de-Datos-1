#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "vector"

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    // O(n): la búsqueda de los tiempos extremos recorre el viaje una vez.
    tuple<tiempo, tiempo> intervalo = tiempoMinimoYMaximo(v) ;
    tiempo tmin=  get<0>(intervalo),tmax =  get<1>(intervalo);

    return tmax - tmin;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    // O(n^2): ordenarViaje usa dos ciclos; luego se suman los n-1 tramos.
    distancia d=0;
    ordenarViaje(v);

    for(int i=0; i<v.size()-1;i++){
        d+=   distEnKM(obtenerPosicion(v[i]),obtenerPosicion(v[i+1]));
    }
    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    double velocidad;
    ordenarViaje(v);

    for(int i=0; i<v.size()-1; i++){

        velocidad =  distEnKM(get<1>(v[i]),get<1>(v[i+1]))*3600/(obtenerTiempo(v[i+1]) - obtenerTiempo(v[i]));
        if(velocidad > 80){
            resp= true;
        }
    }


    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    // O(|v| * |r|): cada punto del recorrido se compara con el viaje.
    // Tanto distEnKM como el umbral u se expresan en kilómetros.
    vector<gps> resp={};
    bool aux= true;
    for(int i=0; i<r.size();i++){
        for(int j=0; j<v.size() && aux; j++){
            if(distEnKM(obtenerPosicion(v[j]), r[i]) < u)
                aux=false;
        }
        if(aux)
            resp.push_back(r[i]);
        aux=true;
    }

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp=0;
    tuple<tiempo,tiempo> minYmax;

    for(int i=0; i<f.size();i++){
        minYmax = tiempoMinimoYMaximo(f[i]);
        if(!(get<1>(minYmax) < t0 || get<0>(minYmax) > tf)){
            resp++;
        }
    }

    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    const double alto = (obtenerLatitud(esq1) - obtenerLatitud(esq2))/n ;
    const double ancho = (obtenerLongitud(esq2) - obtenerLongitud(esq1))/m;
    const double latEsq1= obtenerLatitud(esq1), lonEsq1 = obtenerLongitud(esq1);
    tuple<gps,gps,nombre> celda;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            get<0>(get<0>(celda)) = latEsq1 - alto*(i-1);
            get<0>(get<1>(celda)) = obtenerLatitud(get<0>(celda)) - alto;
            get<1>(get<0>(celda)) = lonEsq1 + ancho*(j-1);
            get<1>(get<1>(celda)) = obtenerLongitud(get<0>(celda)) + ancho;
            get<2>(celda) = make_tuple(i,j);
            resp.push_back(celda);
        }
    }

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int cantidadSaltos=0;

    ordenarViaje(v);

    for (int i = 0; i < v.size() - 1; i++) {

        if(distanciaEntreCeldas(posicionEnlaGrilla(get<1>(v[i]), g), posicionEnlaGrilla(get<1>(v[i + 1]), g)) > 1)
            cantidadSaltos++;
    }

    return cantidadSaltos;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    tuple<tuple<tiempo, gps>, tuple<tiempo, gps>> puntosCercano;

    double velocidadMediaLat, velocidadMediaLong,deltaT;

    for(int i=0; i<v.size(); i++) {
        if(esUnError(get<0>(v[i]), errores))
        {
            puntosCercano= losDosPuntosMasCercanosCorrectos(v, errores, i);

            deltaT= obtenerTiempo(get<1>(puntosCercano)) - obtenerTiempo(get<0>(puntosCercano));

            velocidadMediaLat = (obtenerLatitud(obtenerPosicion(get<1>(puntosCercano)))-obtenerLatitud(obtenerPosicion(get<0>(puntosCercano))))/deltaT;
            velocidadMediaLong = (obtenerLongitud(obtenerPosicion(get<1>(puntosCercano)))-obtenerLongitud(obtenerPosicion(get<0>(puntosCercano))))/deltaT;

            get<0>(get<1>(v[i])) = velocidadMediaLat*(obtenerTiempo(v[i])- obtenerTiempo(get<0>(puntosCercano))) +
                                obtenerLatitud(obtenerPosicion(get<0>(puntosCercano)));
            get<1>(get<1>(v[i]))= velocidadMediaLong*(obtenerTiempo(v[i])- obtenerTiempo(get<0>(puntosCercano))) + obtenerLongitud(obtenerPosicion(get<0>(puntosCercano)));
        }
    }
}
