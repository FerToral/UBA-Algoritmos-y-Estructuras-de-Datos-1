#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <stdexcept>

namespace {
struct ArchivoDePrueba {
    string ruta;
    explicit ArchivoDePrueba(const string& prefijo) {
        ruta = prefijo + to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".tsv";
        if (std::ifstream(ruta).good()) throw std::runtime_error("El archivo temporal ya existe");
    }
    ~ArchivoDePrueba() { std::remove(ruta.c_str()); }
};
}

TEST(regresionesTEST, tiempoConservaFraccionesSinRedondear) {
    const gps p = puntoGps(-30, -60);
    viaje v = {medicion(0.275, p), medicion(0.05, p), medicion(0.2, p)};
    EXPECT_NEAR(tiempoTotal(v), 0.225, 1e-12);
}

TEST(regresionesTEST, umbralSeMideEnKilometrosYEsEstricto) {
    const gps p = puntoGps(-30, -60);
    const gps q = desviarPunto(p, 1000, 0);
    viaje v = {medicion(0, p), medicion(1, p), medicion(2, p)};
    const distancia u = distEnKM(p, q);
    EXPECT_EQ(recorridoNoCubierto(v, {q}, u).size(), 1u);
    EXPECT_TRUE(recorridoNoCubierto(v, {q}, u + 0.001).empty());
}

TEST(regresionesTEST, recorridoConservaSusPuntosSinDuplicarlos) {
    const gps p = puntoGps(-30, -60);
    const gps q = desviarPunto(p, 3000, 0);
    viaje v = {medicion(0, p), medicion(1, p), medicion(2, p)};
    recorrido r = {p, q};
    vector<gps> resultado = recorridoNoCubierto(v, r, 0.1);
    ASSERT_EQ(resultado.size(), 1u);
    EXPECT_EQ(resultado[0], q);
    EXPECT_EQ(r.size(), 2u);
}

TEST(regresionesTEST, grillaRectangularTieneCoordenadasYNombres) {
    grilla g = construirGrilla(puntoGps(3, 0), puntoGps(1, 6), 2, 3);
    ASSERT_EQ(g.size(), 6u);
    for (int fila = 0; fila < 2; ++fila) {
        for (int columna = 0; columna < 3; ++columna) {
            const celda& c = g[fila * 3 + columna];
            EXPECT_EQ(get<2>(c), make_tuple(fila + 1, columna + 1));
            EXPECT_DOUBLE_EQ(obtenerLatitud(get<0>(c)), 3 - fila);
            EXPECT_DOUBLE_EQ(obtenerLongitud(get<0>(c)), 2 * columna);
            EXPECT_DOUBLE_EQ(obtenerLatitud(get<1>(c)), 2 - fila);
            EXPECT_DOUBLE_EQ(obtenerLongitud(get<1>(c)), 2 * columna + 2);
        }
    }
}

TEST(regresionesTEST, grillaDeUnaCeldaConservaEsquinas) {
    const gps a = puntoGps(2, 0), b = puntoGps(0, 2);
    grilla g = construirGrilla(a, b, 1, 1);
    ASSERT_EQ(g.size(), 1u);
    EXPECT_EQ(get<0>(g[0]), a);
    EXPECT_EQ(get<1>(g[0]), b);
    EXPECT_EQ(get<2>(g[0]), make_tuple(1, 1));
}

TEST(regresionesTEST, saltoDiagonalSigueLaDistanciaEuclideaDelContrato) {
    grilla g = construirGrilla(puntoGps(3, 0), puntoGps(0, 3), 3, 3);
    viaje v = {medicion(2, puntoGps(1.5, 1.5)),
               medicion(0, puntoGps(2.5, 0.5)),
               medicion(1, puntoGps(2.5, 0.5))};
    EXPECT_EQ(cantidadDeSaltos(g, v), 1);
}

TEST(regresionesTEST, permanecerEnCeldaNoProduceSaltos) {
    grilla g = construirGrilla(puntoGps(3, 0), puntoGps(0, 3), 3, 3);
    viaje v = {medicion(2, puntoGps(2.5, 0.5)),
               medicion(0, puntoGps(2.6, 0.6)),
               medicion(1, puntoGps(2.7, 0.7))};
    EXPECT_EQ(cantidadDeSaltos(g, v), 0);
}

TEST(regresionesTEST, distanciaOrdenaPorTiempoSinCambiarElArgumento) {
    const gps p = puntoGps(-30, -60);
    const gps q = desviarPunto(p, 1000, 0), r = desviarPunto(p, 3000, 0);
    viaje v = {medicion(2, r), medicion(0, p), medicion(1, q)};
    const viaje original = v;
    EXPECT_NEAR(distanciaTotal(v), distEnKM(p, q) + distEnKM(q, r), 1e-9);
    EXPECT_EQ(v, original);
}

TEST(regresionesTEST, flotaIncluyeContactoConExtremosDeFranja) {
    const gps p = puntoGps(-30, -60);
    viaje a = {medicion(0, p), medicion(1, p), medicion(2, p)};
    viaje b = {medicion(3, p), medicion(4, p), medicion(5, p)};
    viaje c = {medicion(6, p), medicion(7, p), medicion(8, p)};
    EXPECT_EQ(flota({a, b, c}, 2, 3), 2);
    EXPECT_EQ(flota({}, 2, 3), 0);
}

TEST(regresionesTEST, velocidadApenasMayorQueOchentaEsExceso) {
    const gps p = puntoGps(-30, -60);
    const gps q = desviarPunto(p, 1000, 0), r = desviarPunto(p, 2000, 0);
    const tiempo paso = distEnKM(p, q) * 3600 / 80.00005;
    viaje v = {medicion(0, p), medicion(paso, q), medicion(2 * paso, r)};
    EXPECT_TRUE(excesoDeVelocidad(v));
}

TEST(regresionesTEST, correccionRecuperaExtremoEInteriorSinReordenar) {
    viaje v;
    const vector<int> orden = {6, 3, 2, 0, 1, 5, 4};
    for (int t : orden) {
        const gps p = (t == 0 || t == 3) ? puntoGps(0, 0) : puntoGps(1 + 0.01 * t, 2 + 0.02 * t);
        v.push_back(medicion(t, p));
    }
    corregirViaje(v, {0, 3});
    for (unsigned i = 0; i < v.size(); ++i) {
        EXPECT_EQ(obtenerTiempo(v[i]), orden[i]);
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])), 1 + 0.01 * orden[i], 1e-12);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])), 2 + 0.02 * orden[i], 1e-12);
    }
}

TEST(regresionesTEST, corregirSinErroresNoCambiaElViaje) {
    viaje v;
    for (int t = 0; t < 7; ++t) v.push_back(medicion(t, puntoGps(1, 2)));
    const viaje original = v;
    corregirViaje(v, {});
    EXPECT_EQ(v, original);
}

TEST(regresionesTEST, compararGrillasConsideraNombresCoordenadasYContenido) {
    grilla a = construirGrilla(puntoGps(3, 0), puntoGps(1, 6), 2, 3);
    grilla b = a;
    std::reverse(b.begin(), b.end());
    EXPECT_TRUE(sonGrillasIguales(a, b));
    b.pop_back();
    EXPECT_FALSE(sonGrillasIguales(a, b));
    b = a;
    get<2>(b[0]) = make_tuple(9, 9);
    EXPECT_FALSE(sonGrillasIguales(a, b));
    b = a;
    get<0>(get<1>(b[0])) += 0.001;
    EXPECT_FALSE(sonGrillasIguales(a, b));
}

TEST(regresionesTEST, exportarGrillaProduceLosCamposQueLeeElCuaderno) {
    ArchivoDePrueba archivo("prueba_grilla_");
    grilla g = construirGrilla(puntoGps(3, 0), puntoGps(1, 6), 2, 3);
    guardarGrillaEnArchivo(g, archivo.ruta);
    std::ifstream entrada(archivo.ruta);
    ASSERT_TRUE(entrada.good());
    double lat1, lon1, lat2, lon2;
    string nombreCelda;
    unsigned fila = 0;
    while (entrada >> lat1 >> lon1 >> lat2 >> lon2 >> nombreCelda) {
        ASSERT_LT(fila, g.size());
        EXPECT_DOUBLE_EQ(lat1, obtenerLatitud(get<0>(g[fila])));
        EXPECT_DOUBLE_EQ(lon1, obtenerLongitud(get<0>(g[fila])));
        EXPECT_DOUBLE_EQ(lat2, obtenerLatitud(get<1>(g[fila])));
        EXPECT_DOUBLE_EQ(lon2, obtenerLongitud(get<1>(g[fila])));
        EXPECT_EQ(nombreCelda, "(" + to_string(get<0>(get<2>(g[fila]))) + "," + to_string(get<1>(get<2>(g[fila]))) + ")");
        ++fila;
    }
    EXPECT_EQ(fila, g.size());
}

TEST(regresionesTEST, exportarRecorridosConservaIdentificadorYCoordenadas) {
    ArchivoDePrueba archivo("prueba_recorridos_");
    vector<recorrido> recorridos = {{puntoGps(1, 2), puntoGps(3, 4)}, {puntoGps(5, 6)}};
    guardarRecorridosEnArchivo(recorridos, archivo.ruta);
    std::ifstream entrada(archivo.ruta);
    ASSERT_TRUE(entrada.good());
    int id;
    double lat, lon;
    int cantidad = 0;
    while (entrada >> id >> lat >> lon) {
        if (cantidad < 2) EXPECT_EQ(id, 0);
        else EXPECT_EQ(id, 1);
        EXPECT_DOUBLE_EQ(lat, 1 + 2 * cantidad);
        EXPECT_DOUBLE_EQ(lon, 2 + 2 * cantidad);
        ++cantidad;
    }
    EXPECT_EQ(cantidad, 3);
}
