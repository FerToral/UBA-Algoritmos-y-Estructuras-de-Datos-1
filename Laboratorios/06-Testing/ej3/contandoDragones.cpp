#include "contandoDragones.h"
#include <stdexcept>
namespace {
long long mcd(long long a, long long b) {
    while (b) { const auto resto = a % b; a = b; b = resto; }
    return a;
}
long long mcmAcotado(long long a, long long b, long long T) {
    const auto cociente = a / mcd(a, b);
    return cociente > T / b ? T + 1 : cociente * b;
}
}
// Inclusión-exclusión sin recorrer los T dragones.
int contandoDragones(int T, int d1, int d2, int d3) {
    if (T < 0 || d1 <= 0 || d2 <= d1 || d3 <= d2)
        throw std::invalid_argument("Se requiere T >= 0 y 0 < d1 < d2 < d3");
    const long long t = T;
    const auto m12 = mcmAcotado(d1, d2, t), m13 = mcmAcotado(d1, d3, t);
    const auto m23 = mcmAcotado(d2, d3, t), m123 = mcmAcotado(m12, d3, t);
    return static_cast<int>(t-t/d1-t/d2-t/d3+t/m12+t/m13+t/m23-t/m123);
}
