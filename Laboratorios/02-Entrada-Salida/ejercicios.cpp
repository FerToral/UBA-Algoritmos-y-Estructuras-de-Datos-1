#include "ejercicios.h"
#include <climits>
#include <cmath>
#include <limits>
#include <ostream>
#include <stdexcept>
namespace entrada_salida {
Notas analizar(const std::vector<int> &notas) {
    if (notas.empty())
        throw std::invalid_argument("No hay notas");
    Notas r{0, 0, 0, 0, false};
    for (int n : notas) {
        if (n < 0 || n > 10)
            throw std::invalid_argument("Nota entre0 y10");
        r.suma += n;
        if (n > 6)
            ++r.aprobados;
        else
            ++r.reprobados;
    }
    r.promedio = double(r.suma) / notas.size();
    r.ampliar = 3ULL * r.aprobados > 2ULL * notas.size();
    return r;
}
std::uint64_t binarioADecimal(const std::string &s) {
    if (s.empty())
        throw std::invalid_argument("Binario vacio");
    std::uint64_t r = 0;
    for (char c : s) {
        if (c != '0' && c != '1')
            throw std::invalid_argument("Solo0 y1");
        auto bit = unsigned(c - '0');
        if (r > (std::numeric_limits<std::uint64_t>::max() - bit) / 2)
            throw std::overflow_error("Binario fuera de rango");
        r = r * 2 + bit;
    }
    return r;
}
Circulo circulo(double radio) {
    if (!std::isfinite(radio) || radio < 0)
        throw std::invalid_argument("Radio no negativo y finito");
    constexpr double pi = 3.14159;
    auto area = pi * radio * radio;
    if (!std::isfinite(area))
        throw std::overflow_error("Area fuera de rango");
    return {2 * radio, 2 * pi * radio, area};
}
int triplicarPorValor(int cuenta) {
    if (cuenta > INT_MAX / 3 || cuenta < INT_MIN / 3)
        throw std::overflow_error("Triple fuera de rango");
    return cuenta * 3;
}
void triplicarPorReferencia(int &cuenta) {
    cuenta = triplicarPorValor(cuenta);
}
void intercambiar(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
static std::uint64_t paso(std::uint64_t n) {
    if (!n)
        throw std::invalid_argument("Collatz parte de un positivo");
    if (n % 2 == 0)
        return n / 2;
    if (n > (std::numeric_limits<std::uint64_t>::max() - 1) / 3)
        throw std::overflow_error("Paso Collatz fuera de rango");
    return 3 * n + 1;
}
unsigned collatzIterativo(std::uint64_t n, std::ostream &out) {
    if (!n)
        throw std::invalid_argument("Collatz positivo");
    unsigned pasos = 0;
    out << n;
    while (n != 1) {
        if (pasos == 1000000)
            throw std::runtime_error("Limite de pasos de la demostracion");
        n = paso(n);
        out << ' ' << n;
        ++pasos;
    }
    out << '\n';
    return pasos;
}
static unsigned collatzRec(std::uint64_t n, std::ostream &out, unsigned profundidad) {
    if (profundidad >= 2000)
        throw std::runtime_error("Limite de pila de la demostracion");
    out << n;
    if (n == 1) {
        out << '\n';
        return 0;
    }
    out << ' ';
    return 1 + collatzRec(paso(n), out, profundidad + 1);
}
unsigned collatzRecursivo(std::uint64_t n, std::ostream &out) {
    if (!n)
        throw std::invalid_argument("Collatz positivo");
    return collatzRec(n, out, 0);
}
static void dominio(int a, int b) {
    if (a < 0 || b <= 0)
        throw std::invalid_argument("Dividendo>=0, divisor>0");
}
std::pair<int, int> divisionIterativa(int a, int b) {
    dominio(a, b);
    int q = 0;
    while (a >= b) {
        a -= b;
        ++q;
    }
    return {q, a};
}
std::pair<int, int> divisionRecursiva(int a, int b) {
    dominio(a, b);
    if (a < b)
        return {0, a};
    if (a / b > 2000)
        throw std::invalid_argument("Usar version iterativa para cocientes grandes");
    auto r = divisionRecursiva(a - b, b);
    ++r.first;
    return r;
}
} // namespace entrada_salida
