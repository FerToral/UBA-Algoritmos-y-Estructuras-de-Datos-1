#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <climits>
int main() {
    using namespace introduccion;
    COMPROBAR(siguiente(10) == 11);
    COMPROBAR(suma(INT_MAX, INT_MAX) == 4294967294LL);
    COMPROBAR(sumaOProducto(2, 3) == 6);
    COMPROBAR(sumaOProducto(4, 3) == 7);
    COMPROBAR(!esPrimo(1) && esPrimo(2) && esPrimo(97) && !esPrimo(100));
    for (unsigned n = 0; n <= 93; ++n) {
        COMPROBAR(fibonacciRecursivo(n) == fibonacciWhile(n));
        COMPROBAR(fibonacciFor(n) == fibonacciWhile(n));
    }
    COMPROBAR(fibonacciFor(93) == 12200160415121876738ULL);
    for (int n = 0; n < 100; ++n) {
        COMPROBAR(imparesRecursivo(n) == imparesWhile(n));
        COMPROBAR(imparesFor(n) == imparesWhile(n));
    }
    COMPROBAR(imparesFor(10) == 25);
    for (int n = 1; n < 200; ++n) {
        COMPROBAR(divisoresRecursivo(n) == divisoresWhile(n));
        COMPROBAR(divisoresFor(n) == divisoresWhile(n));
    }
    COMPROBAR(divisoresFor(12) == 28);
    for (unsigned n = 0; n <= 67; ++n)
        for (unsigned k = 0; k <= n; ++k)
            COMPROBAR(combinatorioIterativo(n, k) == combinatorioRecursivo(n, k));
    COMPROBAR(combinatorioIterativo(10, 3) == 120);
    bool error = false;
    try {
        fibonacciFor(94);
    } catch (const std::overflow_error &) {
        error = true;
    }
    COMPROBAR(error);
}
