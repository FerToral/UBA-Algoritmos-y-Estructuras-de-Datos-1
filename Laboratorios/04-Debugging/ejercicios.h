#pragma once
#include <cstdint>
#include <iosfwd>
#include <vector>
namespace debugging {
bool estaOrdenado(const std::vector<int> &v);
bool esPrimo(int n);
bool pertenece(int n, const std::vector<int> &v);
double desvioEstandar(const std::vector<double> &v);
std::uint64_t fibonacci(unsigned n);
long long maximoComunDivisor(int x, int y);
long long sumaDoble(const std::vector<int> &v);
unsigned cantPalabras(std::istream &entrada);
double valorMedio(std::istream &entrada);
void fraccion(const std::vector<int> &v, double &resultado);
} // namespace debugging
