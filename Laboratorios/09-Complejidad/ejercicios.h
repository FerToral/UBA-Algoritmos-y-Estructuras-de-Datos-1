#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace complejidad {
std::vector<int> construirVector(unsigned n, const std::string &disposicion);
bool hayDuplicados(const std::vector<int> &v, std::uint64_t &comparaciones);
bool hayDuplicadosCorte(const std::vector<int> &v, std::uint64_t &comparaciones);
bool algunSubconjuntoSuma(const std::vector<int> &v, long long objetivo, std::uint64_t &llamadas);
std::uint64_t trabajoCubico(unsigned n);
} // namespace complejidad
