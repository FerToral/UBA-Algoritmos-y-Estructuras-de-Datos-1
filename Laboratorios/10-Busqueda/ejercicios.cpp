#include "ejercicios.h"
#include <algorithm>
#include <cmath>
#include <deque>
#include <stdexcept>
namespace busqueda {
int busquedaBinaria(const std::vector<int> &v, int x) {
    int l = 0, r = int(v.size());
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] < x)
            l = m + 1;
        else
            r = m;
    }
    return l < int(v.size()) && v[l] == x ? l : -1;
}
int busquedaJumpSearch(const std::vector<int> &v, int x) {
    if (v.empty())
        return -1;
    int n = int(v.size()), salto = std::max(1, int(std::sqrt(n))), inicio = 0, fin = salto;
    while (v[std::min(fin, n) - 1] < x) {
        inicio = fin;
        if (inicio >= n)
            return -1;
        fin = std::min(n, fin + salto);
    }
    for (int i = inicio; i < std::min(fin, n); ++i) {
        if (v[i] == x)
            return i;
        if (v[i] > x)
            break;
    }
    return -1;
}
int indicePico(const std::vector<int> &v) {
    if (v.empty())
        return -1;
    int l = 0, r = int(v.size()) - 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] < v[m + 1])
            l = m + 1;
        else
            r = m;
    }
    return l;
}
int puntoFijo(const std::vector<int> &v) {
    int l = 0, r = int(v.size());
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] < m)
            l = m + 1;
        else
            r = m;
    }
    return l < int(v.size()) && v[l] == l ? l : -1;
}
int encontrarRotado(const std::vector<int> &v, int x) {
    int l = 0, r = int(v.size()) - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (v[m] == x)
            return m;
        if (v[l] <= v[m]) {
            if (v[l] <= x && x < v[m])
                r = m - 1;
            else
                l = m + 1;
        } else {
            if (v[m] < x && x <= v[r])
                l = m + 1;
            else
                r = m - 1;
        }
    }
    return -1;
}
int menorMasGrande(const std::vector<int> &v, int x) {
    int l = 0, r = int(v.size());
    while (l < r) {
        int m = l + (r - l) / 2;
        if (v[m] <= x)
            l = m + 1;
        else
            r = m;
    }
    return l < int(v.size()) ? l : -1;
}
std::vector<int> masCercanoK(const std::vector<int> &v, int k, int x) {
    if (k < 0)
        throw std::invalid_argument("k no negativo");
    int izq = int(std::lower_bound(v.begin(), v.end(), x) - v.begin()) - 1;
    int der = int(std::upper_bound(v.begin(), v.end(), x) - v.begin());
    std::deque<int> elegidos;
    while (int(elegidos.size()) < k && (izq >= 0 || der < int(v.size()))) {
        bool izquierda =
            der == int(v.size()) ||
            (izq >= 0 && static_cast<long long>(x) - v[izq] <= static_cast<long long>(v[der]) - x);
        if (izquierda)
            elegidos.push_front(v[izq--]);
        else
            elegidos.push_back(v[der++]);
    }
    return {elegidos.begin(), elegidos.end()};
}
} // namespace busqueda
