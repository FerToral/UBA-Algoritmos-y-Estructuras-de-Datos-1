#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
int main() {
    using namespace complejidad;
    std::uint64_t a, b;
    for (unsigned n = 0; n < 100; ++n) {
        auto v = construirVector(n, "asc");
        COMPROBAR(!hayDuplicados(v, a));
        COMPROBAR(!hayDuplicadosCorte(v, b));
        COMPROBAR(a == std::uint64_t(n) * (n ? n - 1 : 0) / 2 && a == b);
        v = construirVector(n, "iguales");
        COMPROBAR(hayDuplicados(v, a) == (n > 1));
        COMPROBAR(hayDuplicadosCorte(v, b) == (n > 1));
        COMPROBAR(b == (n > 1 ? 1 : 0));
    }
    COMPROBAR(algunSubconjuntoSuma({3, 4, 7}, 11, a));
    COMPROBAR(!algunSubconjuntoSuma({3, 4, 7}, 2, a));
    COMPROBAR(algunSubconjuntoSuma({}, 0, a));
    COMPROBAR(trabajoCubico(1) == 0);
    COMPROBAR(construirVector(4, "desc") == std::vector<int>({3, 2, 1, 0}));
}
