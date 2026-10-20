#include "ejercicios.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using Reloj = std::chrono::steady_clock;
volatile std::uint64_t consumo = 0;
template <class F> double medir(F trabajo) {
    auto t = Reloj::now();
    trabajo();
    return std::chrono::duration<double>(Reloj::now() - t).count();
}
int main(int argc, char **argv) {
    using namespace complejidad;
    try {
        std::string modo = argc > 1 ? argv[1] : "duplicados";
        if (modo == "duplicados") {
            std::cout << "n,disposicion,sin_corte_s,con_corte_s,comparaciones,"
                         "comparaciones_corte,c_estimado\n";
            for (unsigned n = 1; n <= 10000; n += 500)
                for (std::string tipo : {"asc", "desc", "azar", "iguales"}) {
                    auto v = construirVector(n, tipo);
                    std::uint64_t a, b;
                    double t = medir([&] { consumo += hayDuplicados(v, a); }),
                           s = medir([&] { consumo += hayDuplicadosCorte(v, b); });
                    std::cout << n << ',' << tipo << ',' << t << ',' << s << ',' << a << ',' << b
                              << ',' << t / (double(n) * n) << '\n';
                }
        } else if (modo == "ordenes") {
            auto muestra = medir([&] { consumo += trabajoCubico(100); });
            double c = muestra / 1000000;
            std::cout << "n,constante_s,lineal_s,nlogn_s,cubico_estimado_s\n";
            for (unsigned n : {100, 1000, 10000, 100000}) {
                auto v = construirVector(n, "desc");
                double constante = medir([&] {
                                       for (int i = 0; i < 100000; ++i)
                                           consumo += v.size();
                                   }) /
                                   100000;
                double lineal = medir([&] {
                    for (int x : v)
                        consumo += x;
                });
                double nlogn = medir([&] {
                    std::sort(v.begin(), v.end());
                    consumo += v.front();
                });
                std::cout << n << ',' << constante << ',' << lineal << ',' << nlogn << ','
                          << c * double(n) * n * n << '\n';
            }
        } else if (modo == "stl") {
            std::cout << "n,size_s,push_s,pop_s,indice0_s,indiceMedio_s,indiceFinal_"
                         "s,escritura_s,flip_s,clear_s,empty_s,capacidad_antes,"
                         "capacidad_despues\n";
            for (unsigned n : {100, 1000, 10000, 100000}) {
                auto v = construirVector(n, "asc");
                v.shrink_to_fit();
                auto cap = v.capacity();
                double tam = medir([&] {
                                 for (int i = 0; i < 100000; ++i)
                                     consumo += v.size();
                             }) /
                             100000;
                double push = medir([&] { v.push_back(1); });
                auto nueva = v.capacity();
                double pop = medir([&] { v.pop_back(); });
                double lecturas[3];
                int k = 0;
                for (unsigned i : {0U, n / 2, n - 1})
                    lecturas[k++] = medir([&] {
                                        for (int j = 0; j < 100000; ++j)
                                            consumo += v[i];
                                    }) /
                                    100000;
                double escritura = medir([&] {
                                       for (int i = 0; i < 100000; ++i) {
                                           v[n / 2] = i;
                                           consumo += v[n / 2];
                                       }
                                   }) /
                                   100000;
                std::vector<bool> bits(n);
                double flip = medir([&] {
                    bits.flip();
                    consumo += bits[0];
                });
                double vacio = medir([&] {
                                   for (int i = 0; i < 100000; ++i)
                                       consumo += v.empty();
                               }) /
                               100000;
                double clear = medir([&] {
                    v.clear();
                    consumo += v.size();
                });
                std::cout << n << ',' << tam << ',' << push << ',' << pop << ',' << lecturas[0]
                          << ',' << lecturas[1] << ',' << lecturas[2] << ',' << escritura << ','
                          << flip << ',' << clear << ',' << vacio << ',' << cap << ',' << nueva
                          << '\n';
            }
        } else if (modo == "subconjuntos") {
            std::cout << "n,segundos,llamadas\n";
            for (unsigned n : {5, 10, 15, 20}) {
                std::vector<int> v(n, 1);
                std::uint64_t llamadas;
                double t = medir([&] { consumo += algunSubconjuntoSuma(v, n + 1, llamadas); });
                std::cout << n << ',' << t << ',' << llamadas << '\n';
            }
        } else if (modo == "datos-bpp") {
            int n = argc > 2 ? std::stoi(argv[2]) : 1000;
            if (n < 0 || n > 1000000)
                throw std::invalid_argument("Entre0 y1000000 objetos");
            std::cout << n << " 150\n";
            for (int i = 0; i < n; ++i)
                std::cout << 1 + (i * 37LL % 150) << ' ';
            std::cout << '\n';
        } else
            throw std::invalid_argument("Modos:duplicados,ordenes,stl,subconjuntos,datos-bpp");
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
