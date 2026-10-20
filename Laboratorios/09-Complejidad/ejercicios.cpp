#include "ejercicios.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>
namespace complejidad {
std::vector<int> construirVector(unsigned n, const std::string &tipo) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    if (tipo == "desc")
        std::reverse(v.begin(), v.end());
    else if (tipo == "azar") {
        std::mt19937 g(2022);
        std::shuffle(v.begin(), v.end(), g);
    } else if (tipo == "iguales")
        std::fill(v.begin(), v.end(), 1);
    else if (tipo != "asc")
        throw std::invalid_argument("asc,desc,azar o iguales");
    return v;
}
bool hayDuplicados(const std::vector<int> &v, std::uint64_t &comparaciones) {
    comparaciones = 0;
    bool encontrado = false;
    for (unsigned i = 0; i < v.size(); ++i)
        for (unsigned j = i + 1; j < v.size(); ++j) {
            ++comparaciones;
            encontrado |= v[i] == v[j];
        }
    return encontrado;
}
bool hayDuplicadosCorte(const std::vector<int> &v, std::uint64_t &comparaciones) {
    comparaciones = 0;
    for (unsigned i = 0; i < v.size(); ++i)
        for (unsigned j = i + 1; j < v.size(); ++j) {
            ++comparaciones;
            if (v[i] == v[j])
                return true;
        }
    return false;
}
static bool subconjunto(const std::vector<int> &v, unsigned i, long long objetivo,
                        std::uint64_t &llamadas) {
    ++llamadas;
    if (i == v.size())
        return objetivo == 0;
    return subconjunto(v, i + 1, objetivo, llamadas) ||
           subconjunto(v, i + 1, objetivo - v[i], llamadas);
}
bool algunSubconjuntoSuma(const std::vector<int> &v, long long objetivo, std::uint64_t &llamadas) {
    if (v.size() > 24)
        throw std::invalid_argument("Demostracion exponencial: hasta24 elementos");
    llamadas = 0;
    return subconjunto(v, 0, objetivo, llamadas);
}
std::uint64_t trabajoCubico(unsigned n) {
    if (n > 200)
        throw std::invalid_argument("Medir n<=200; extrapolar casos grandes");
    std::uint64_t r = 0;
    for (unsigned i = 0; i < n; ++i)
        for (unsigned j = 0; j < n; ++j)
            for (unsigned k = 0; k < n; ++k)
                r += (i + j + k) % 7;
    return r;
}
} // namespace complejidad
