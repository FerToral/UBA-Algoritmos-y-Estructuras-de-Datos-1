#pragma once
#include <cstdint>
#include <iosfwd>
#include <string>
#include <utility>
#include <vector>
namespace entrada_salida {
struct Notas {
    long long suma;
    double promedio;
    unsigned aprobados;
    unsigned reprobados;
    bool ampliar;
};
Notas analizar(const std::vector<int> &notas);
std::uint64_t binarioADecimal(const std::string &binario);
struct Circulo {
    double diametro, circunferencia, area;
};
Circulo circulo(double radio);
int triplicarPorValor(int cuenta);
void triplicarPorReferencia(int &cuenta);
void intercambiar(int &a, int &b);
unsigned collatzIterativo(std::uint64_t n, std::ostream &salida);
unsigned collatzRecursivo(std::uint64_t n, std::ostream &salida);
std::pair<int, int> divisionIterativa(int dividendo, int divisor);
std::pair<int, int> divisionRecursiva(int dividendo, int divisor);
} // namespace entrada_salida
