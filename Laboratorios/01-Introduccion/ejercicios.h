#pragma once
#include <cstdint>
namespace introduccion {
int siguiente(int x);
long long suma(int x, int y);
long long sumaOProducto(int x, int y);
bool esPrimo(int n);
std::uint64_t fibonacciRecursivo(unsigned n);
std::uint64_t fibonacciWhile(unsigned n);
std::uint64_t fibonacciFor(unsigned n);
long long imparesRecursivo(int n);
long long imparesWhile(int n);
long long imparesFor(int n);
long long divisoresRecursivo(int n);
long long divisoresWhile(int n);
long long divisoresFor(int n);
std::uint64_t combinatorioRecursivo(unsigned n, unsigned k);
std::uint64_t combinatorioIterativo(unsigned n, unsigned k);
} // namespace introduccion
