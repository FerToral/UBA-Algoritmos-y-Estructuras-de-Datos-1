#include "../../pruebas/comprobar.h"
#include "ejercicios.h"
#include <algorithm>
#include <random>
#include <sstream>
int main() {
    using namespace ordenamiento;
    std::mt19937 g(2022);
    for (int n = 0; n < 100; ++n) {
        std::vector<int> v(n);
        for (auto &x : v)
            x = int(g() % 100) - 50;
        auto esperado = v;
        std::sort(esperado.begin(), esperado.end());
        for (auto ordenar : {insertionSort, selectionSort, mergeSort}) {
            auto copia = v;
            ordenar(copia);
            COMPROBAR(copia == esperado);
        }
    }
    std::vector<int> objetos{4, 8, 5, 1, 7, 6, 1, 4, 2, 2};
    COMPROBAR(nextFit(objetos, 10) == 6);
    COMPROBAR(bestFit(objetos, 10) == 5);
    COMPROBAR(bestFitDecreciente(objetos, 10) == 4);
    COMPROBAR(nextFit({}, 10) == 0 && bestFit({}, 10) == 0);
    COMPROBAR(esAnagramaOrdenando("delira", "lidera"));
    COMPROBAR(esAnagramaPrimos("delira", "lidera"));
    COMPROBAR(!esAnagramaPrimos("aaaa", "aaab"));
    COMPROBAR(productoPrimos(std::string(100, 'z')).size() > 100);
    std::istringstream a("listen silent enlist inlets listen tinsel otra"), b(a.str());
    COMPROBAR(buscarAnagramas(a, "listen", false) == buscarAnagramas(b, "listen", true));
    std::istringstream in("3 10 2 4 8");
    int cap;
    COMPROBAR(leerBpp(in, cap) == std::vector<int>({2, 4, 8}) && cap == 10);
    bool error = false;
    try {
        bestFit({11}, 10);
    } catch (const std::invalid_argument &) {
        error = true;
    }
    COMPROBAR(error);
}
