#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <algorithm>
#include <climits>
int main() {
    using namespace busqueda;
    for (int n = 0; n < 100; ++n) {
        std::vector<int> v;
        for (int i = 0; i < n; ++i)
            v.push_back(2 * i);
        for (int x = -1; x <= 2 * n; ++x) {
            int esperado = x >= 0 && x % 2 == 0 && x / 2 < n ? x / 2 : -1;
            COMPROBAR(busquedaBinaria(v, x) == esperado);
            COMPROBAR(busquedaJumpSearch(v, x) == esperado);
        }
        for (int giro = 0; giro < n; ++giro) {
            auto rotado = v;
            std::rotate(rotado.begin(), rotado.begin() + giro, rotado.end());
            for (int i = 0; i < n; ++i) {
                int pos = encontrarRotado(rotado, 2 * i);
                COMPROBAR(pos >= 0 && rotado[pos] == 2 * i);
            }
            COMPROBAR(encontrarRotado(rotado, -1) == -1);
        }
    }
    COMPROBAR(puntoFijo({-2, -1, 2, 3, 5}) == 2);
    COMPROBAR(puntoFijo({-1, 0, 1}) == -1);
    COMPROBAR(indicePico({}) == -1);
    for (auto v :
         std::vector<std::vector<int>>{{1}, {1, 2, 3}, {3, 2, 1}, {1, 3, 2, 4, 1}, {2, 2, 2}}) {
        int i = indicePico(v);
        COMPROBAR((i == 0 || v[i] >= v[i - 1]) && (i + 1 == int(v.size()) || v[i] >= v[i + 1]));
    }
    COMPROBAR(menorMasGrande({1, 3, 5}, 3) == 2);
    COMPROBAR(menorMasGrande({1, 3, 5}, 5) == -1);
    COMPROBAR(masCercanoK({1, 2, 3, 4, 5}, 3, 3) == std::vector<int>({1, 2, 4}));
    COMPROBAR(masCercanoK({1, 2, 2, 3}, 9, 2) == std::vector<int>({1, 3}));
    COMPROBAR(masCercanoK({INT_MIN, INT_MAX}, 1, 0) == std::vector<int>({INT_MAX}));
}
