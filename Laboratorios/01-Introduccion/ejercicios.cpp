#include "ejercicios.h"
#include <algorithm>
#include <climits>
#include <limits>
#include <stdexcept>
#include <vector>
namespace introduccion {
int siguiente(int x) {
    if (x == INT_MAX)
        throw std::overflow_error("No hay siguiente representable");
    return x + 1;
}
long long suma(int x, int y) {
    return static_cast<long long>(x) + y;
}
long long sumaOProducto(int x, int y) {
    return x > y ? suma(x, y) : static_cast<long long>(x) * y;
}
bool esPrimo(int n) {
    if (n < 2)
        return false;
    for (int d = 2; d <= n / d; ++d)
        if (n % d == 0)
            return false;
    return true;
}
static std::uint64_t fib(unsigned n, std::uint64_t a, std::uint64_t b) {
    if (n == 0)
        return a;
    if (n == 1)
        return b;
    return fib(n - 1, b, a + b);
}
static void rangoFib(unsigned n) {
    if (n > 93)
        throw std::overflow_error("Fibonacci supera uint64");
}
std::uint64_t fibonacciRecursivo(unsigned n) {
    rangoFib(n);
    return fib(n, 0, 1);
}
std::uint64_t fibonacciWhile(unsigned n) {
    rangoFib(n);
    std::uint64_t a = 0, b = 1;
    unsigned i = 0;
    while (i < n) {
        if (i + 1 == n)
            return b;
        auto c = a + b;
        a = b;
        b = c;
        ++i;
    }
    return a;
}
std::uint64_t fibonacciFor(unsigned n) {
    rangoFib(n);
    if (n == 0)
        return 0;
    std::uint64_t a = 0, b = 1;
    for (unsigned i = 1; i < n; ++i) {
        auto c = a + b;
        a = b;
        b = c;
    }
    return b;
}
static void natural(int n) {
    if (n < 0)
        throw std::invalid_argument("Se requiere un natural");
}
long long imparesRecursivo(int n) {
    natural(n);
    if (n < 2)
        return 0;
    int ultimo = (n % 2 == 0 ? n - 1 : n - 2);
    return ultimo + imparesRecursivo(ultimo);
}
long long imparesWhile(int n) {
    natural(n);
    long long s = 0;
    int i = 1;
    while (i < n) {
        s += i;
        if (i > INT_MAX - 2)
            break;
        i += 2;
    }
    return s;
}
long long imparesFor(int n) {
    natural(n);
    long long s = 0;
    for (long long i = 1; i < n; i += 2)
        s += i;
    return s;
}
static long long divisoresHasta(int n, int d) {
    if (d == 0)
        return 0;
    return (n % d == 0 ? d : 0) + divisoresHasta(n, d - 1);
}
long long divisoresRecursivo(int n) {
    if (n <= 0)
        throw std::invalid_argument("Entero positivo");
    return divisoresHasta(n, n);
}
long long divisoresWhile(int n) {
    if (n <= 0)
        throw std::invalid_argument("Entero positivo");
    long long s = 0, d = 1;
    while (d <= n) {
        if (n % d == 0)
            s += d;
        ++d;
    }
    return s;
}
long long divisoresFor(int n) {
    if (n <= 0)
        throw std::invalid_argument("Entero positivo");
    long long s = 0;
    for (long long d = 1; d <= n; ++d)
        if (n % d == 0)
            s += d;
    return s;
}
static std::uint64_t sumarSeguro(std::uint64_t a, std::uint64_t b) {
    if (a > std::numeric_limits<std::uint64_t>::max() - b)
        throw std::overflow_error("Combinatorio supera uint64");
    return a + b;
}
static void rangoComb(unsigned n, unsigned k) {
    if (k > n)
        throw std::invalid_argument("0 <= k <= n");
    if (n > 67)
        throw std::overflow_error("La practica limita n a67 para cubrir toda la fila");
}
static std::uint64_t combinar(unsigned n, unsigned k,
                              std::vector<std::vector<std::uint64_t>> &memoria) {
    if (k == 0 || k == n)
        return 1;
    auto &r = memoria[n][k];
    if (!r)
        r = sumarSeguro(combinar(n - 1, k - 1, memoria), combinar(n - 1, k, memoria));
    return r;
}
std::uint64_t combinatorioRecursivo(unsigned n, unsigned k) {
    rangoComb(n, k);
    std::vector<std::vector<std::uint64_t>> m(n + 1, std::vector<std::uint64_t>(n + 1));
    return combinar(n, k, m);
}
std::uint64_t combinatorioIterativo(unsigned n, unsigned k) {
    rangoComb(n, k);
    k = std::min(k, n - k);
    std::vector<std::uint64_t> fila(k + 1);
    fila[0] = 1;
    for (unsigned i = 1; i <= n; ++i)
        for (unsigned j = std::min(i, k); j > 0; --j)
            fila[j] = sumarSeguro(fila[j], fila[j - 1]);
    return fila[k];
}
} // namespace introduccion
