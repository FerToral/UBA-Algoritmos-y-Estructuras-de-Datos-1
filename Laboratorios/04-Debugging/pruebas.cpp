#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <climits>
#include <cmath>
#include <sstream>
int main() {
    using namespace debugging;
    COMPROBAR(estaOrdenado({}) && estaOrdenado({3, 2, 1}) && estaOrdenado({0, 0, 0}) &&
              !estaOrdenado({0, 1, 0}));
    COMPROBAR(esPrimo(919) && !esPrimo(-2) && !esPrimo(1));
    COMPROBAR(pertenece(-323, {5, -323, 253}) && !pertenece(1, {}));
    COMPROBAR(std::abs(desvioEstandar({20, 15, 26, 32, 18, 28, 35, 14, 26, 22, 17}) -
                       std::sqrt(44.0)) < 1e-9);
    COMPROBAR(fibonacci(0) == 0 && fibonacci(50) == 12586269025ULL);
    COMPROBAR(maximoComunDivisor(-6, 10) == 2 && maximoComunDivisor(INT_MIN, 0) == 2147483648LL);
    COMPROBAR(sumaDoble({-2, 1, 2, -2}) == 4);
    std::istringstream a("uno dos tres\n");
    COMPROBAR(cantPalabras(a) == 3);
    std::istringstream b("0.2 0.4 0.6 0 1 -2 7");
    COMPROBAR(std::abs(valorMedio(b) - .4) < 1e-9);
    double r = -1;
    fraccion({1, -1, 2, 0}, r);
    COMPROBAR(r == .5);
    fraccion({}, r);
    COMPROBAR(r == 0);
}
