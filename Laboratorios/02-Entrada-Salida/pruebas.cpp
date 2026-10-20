#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <cmath>
#include <sstream>
int main() {
    using namespace entrada_salida;
    auto n = analizar({7, 8, 9, 10, 6, 5});
    COMPROBAR(n.suma == 45 && n.promedio == 7.5 && n.aprobados == 4 && !n.ampliar);
    COMPROBAR(analizar({7, 7, 7, 7, 7, 0}).ampliar);
    COMPROBAR(binarioADecimal("1010") == 10);
    COMPROBAR(binarioADecimal(std::string(64, '1')) == 18446744073709551615ULL);
    bool error = false;
    try {
        binarioADecimal("102");
    } catch (const std::invalid_argument &) {
        error = true;
    }
    COMPROBAR(error);
    auto c = circulo(2);
    COMPROBAR(c.diametro == 4 && std::abs(c.area - 12.56636) < 1e-9);
    int cuenta = 5;
    COMPROBAR(triplicarPorValor(cuenta) == 15 && cuenta == 5);
    triplicarPorReferencia(cuenta);
    COMPROBAR(cuenta == 15);
    int a = 2, b = 7;
    intercambiar(a, b);
    COMPROBAR(a == 7 && b == 2);
    intercambiar(a, a);
    COMPROBAR(a == 7);
    std::ostringstream x, y;
    COMPROBAR(collatzIterativo(11, x) == 14);
    COMPROBAR(collatzRecursivo(11, y) == 14);
    COMPROBAR(x.str() == y.str());
    for (int i = 0; i < 100; ++i)
        for (int j = 1; j < 20; ++j) {
            auto r = divisionIterativa(i, j);
            COMPROBAR(r == divisionRecursiva(i, j));
            COMPROBAR(r.first == i / j && r.second == i % j);
        }
}
