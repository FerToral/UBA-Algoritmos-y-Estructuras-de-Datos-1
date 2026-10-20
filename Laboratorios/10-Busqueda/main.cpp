#include "ejercicios.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
int main() {
    using reloj = std::chrono::steady_clock;
    volatile long long consumir = 0;
    std::cout << "n,binaria_ms,jump_ms\n";
    for (int n : {100, 1000, 10000, 100000}) {
        std::vector<int> v(n);
        std::iota(v.begin(), v.end(), 0);
        auto medir = [&](bool binaria) {
            auto inicio = reloj::now();
            for (int i = 0; i < 10000; ++i)
                consumir += binaria ? busqueda::busquedaBinaria(v, n + 1)
                                    : busqueda::busquedaJumpSearch(v, n + 1);
            return std::chrono::duration<double, std::milli>(reloj::now() - inicio).count() / 10000;
        };
        auto b = medir(true), j = medir(false);
        std::cout << n << ',' << b << ',' << j << '\n';
    }
    return consumir == 1;
}
