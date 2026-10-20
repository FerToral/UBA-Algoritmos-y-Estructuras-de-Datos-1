#pragma once
#include <vector>
namespace busqueda {
int busquedaBinaria(const std::vector<int> &v, int x);
int busquedaJumpSearch(const std::vector<int> &v, int x);
int indicePico(const std::vector<int> &v);
int puntoFijo(const std::vector<int> &v);
int encontrarRotado(const std::vector<int> &v, int x);
int menorMasGrande(const std::vector<int> &v, int x);
std::vector<int> masCercanoK(const std::vector<int> &v, int k, int x);
} // namespace busqueda
