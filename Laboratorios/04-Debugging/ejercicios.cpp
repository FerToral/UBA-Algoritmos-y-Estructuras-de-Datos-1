#include "ejercicios.h"
#include <algorithm>
#include <cmath>
#include <istream>
#include <stdexcept>
#include <string>
namespace debugging {
bool estaOrdenado(const std::vector<int> &v) {
    return std::is_sorted(v.begin(), v.end()) || std::is_sorted(v.rbegin(), v.rend());
}
bool esPrimo(int n) {
    if (n < 2)
        return false;
    for (int i = 2; i <= n / i; ++i)
        if (n % i == 0)
            return false;
    return true;
}
bool pertenece(int n, const std::vector<int> &v) {
    return std::find(v.begin(), v.end(), n) != v.end();
}
double desvioEstandar(const std::vector<double> &v) {
    if (v.empty())
        throw std::invalid_argument("Muestra no vacia");
    double media = 0, m2 = 0;
    unsigned n = 0;
    for (double x : v) {
        if (!std::isfinite(x))
            throw std::invalid_argument("Valores finitos");
        ++n;
        double delta = x - media;
        media += delta / n;
        m2 += delta * (x - media);
    }
    return std::sqrt(m2 / n);
}
std::uint64_t fibonacci(unsigned n) {
    if (n > 93)
        throw std::overflow_error("Fibonacci fuera de rango");
    if (!n)
        return 0;
    std::uint64_t a = 0, b = 1;
    for (unsigned i = 1; i < n; ++i) {
        auto siguiente = a + b;
        a = b;
        b = siguiente;
    }
    return b;
}
long long maximoComunDivisor(int x, int y) {
    long long a = x, b = y;
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b) {
        auto r = a % b;
        a = b;
        b = r;
    }
    return a;
}
long long sumaDoble(const std::vector<int> &v) {
    long long suma = 0;
    for (int x : v)
        if (x > 0 && x % 2 == 0)
            suma += 2LL * x;
    return suma;
}
unsigned cantPalabras(std::istream &in) {
    std::string palabra;
    unsigned total = 0;
    while (in >> palabra)
        ++total;
    if (in.bad())
        throw std::runtime_error("Error de lectura");
    return total;
}
double valorMedio(std::istream &in) {
    double x, media = 0;
    unsigned n = 0;
    while (in >> x)
        if (x > 0 && x < 1) {
            ++n;
            media += (x - media) / n;
        }
    if (!in.eof())
        throw std::invalid_argument("Dato no numerico");
    if (!n)
        throw std::domain_error("No hay mediciones validas");
    return media;
}
void fraccion(const std::vector<int> &v, double &r) {
    if (v.empty()) {
        r = 0;
        return;
    }
    unsigned positivos = 0;
    for (int x : v)
        if (x > 0)
            ++positivos;
    r = double(positivos) / v.size();
}
} // namespace debugging
