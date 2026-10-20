#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <climits>
#include <sstream>
int main() {
    using namespace vectores_archivos;
    COMPROBAR(divide({2, 4, 6}, 2));
    COMPROBAR(!divide({2, 3}, 2));
    COMPROBAR(mayor({-5, -2, -9}) == -2);
    COMPROBAR(reverso({1, 2, 3}) == std::vector<int>({3, 2, 1}));
    COMPROBAR(rotar({1, 2, 3, 4, 5, 6}, 2) == std::vector<int>({3, 4, 5, 6, 1, 2}));
    COMPROBAR(rotar({1, 2, 3}, -1) == std::vector<int>({3, 1, 2}));
    COMPROBAR(rotar({}, 99).empty());
    COMPROBAR(estaOrdenado({3, 2, 1}) && !estaOrdenado({1, 3, 2}));
    COMPROBAR(factoresPrimos(60) == std::vector<int>({2, 2, 3, 5}));
    COMPROBAR(factoresPrimos(1).empty());
    std::ostringstream v;
    mostrarVector({1, 2, 5, 65}, v);
    COMPROBAR(v.str() == "[1, 2, 5, 65]");
    std::istringstream in("1 2 -3 ");
    COMPROBAR(leerVector(in) == std::vector<int>({1, 2, -3}));
    COMPROBAR(elementoMedio({1, 2, 3, 4}) == 3);
    std::istringstream repetidos("1 2 2 1 1 4");
    auto c = cantApariciones(repetidos);
    COMPROBAR(c[1] == 3 && c[2] == 2 && c[4] == 1);
    std::istringstream palabras("a b a\na");
    COMPROBAR(cantidadAparicionesDePalabra(palabras, "a") == 3);
    std::istringstream a("1 2 3 4"), b("1 25 3 12");
    std::ostringstream promedioOut;
    promedio(a, b, promedioOut);
    COMPROBAR(promedioOut.str() == "1 13.5 3 8\n");
    std::istringstream x("1 4 8 19"), y("3 25 31");
    std::ostringstream mezcla;
    ordenarSecuencias(x, y, mezcla);
    COMPROBAR(mezcla.str() == "1 3 4 8 19 25 31\n");
    std::istringstream izq("1 2 2 3"), der("2 4 2 1");
    COMPROBAR(interseccion(izq, der) == std::vector<int>({2, 1}));
    bool error = false;
    try {
        std::istringstream z("1 x");
        leerVector(z);
    } catch (const std::invalid_argument &) {
        error = true;
    }
    COMPROBAR(error);
    error = false;
    try {
        std::istringstream p("1 2"), q("1");
        std::ostringstream r;
        promedio(p, q, r);
    } catch (const std::invalid_argument &) {
        error = true;
    }
    COMPROBAR(error);
}
