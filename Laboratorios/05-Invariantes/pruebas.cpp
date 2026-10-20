#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <algorithm>
int main() {
    COMPROBAR(!existePico({}) && !existePico({1, 1, 1}));
    COMPROBAR(existePico({1, 3, 2}));
    COMPROBAR(mcd(28, 56) == 28);
    COMPROBAR(indiceMinSubsec({3, -2, -2}, 0, 2) == 1);
    for (int n = 0; n <= 6; ++n) {
        int total = 1;
        for (int i = 0; i < n; ++i)
            total *= 3;
        for (int codigo = 0; codigo < total; ++codigo) {
            int k = codigo;
            std::vector<int> v;
            for (int i = 0; i < n; ++i) {
                v.push_back(k % 3);
                k /= 3;
            }
            auto esperado = v;
            std::sort(esperado.begin(), esperado.end());
            auto a = v, b = v;
            ordenar1(a);
            ordenar2(b);
            COMPROBAR(a == esperado && b == esperado);
        }
    }
    for (int a = 0; a < 100; ++a)
        for (int b = 1; b < 20; ++b) {
            auto r = division(a, b);
            COMPROBAR(std::get<0>(r) == a / b && std::get<1>(r) == a % b);
        }
}
