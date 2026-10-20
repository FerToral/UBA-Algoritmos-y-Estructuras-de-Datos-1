#include "ejercicios.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <istream>
#include <set>
#include <sstream>
#include <stdexcept>
namespace ordenamiento {
void insertionSort(std::vector<int> &v) {
    for (unsigned i = 1; i < v.size(); ++i) {
        int actual = v[i];
        unsigned j = i;
        while (j > 0 && v[j - 1] > actual) {
            v[j] = v[j - 1];
            --j;
        }
        v[j] = actual;
    }
}
void selectionSort(std::vector<int> &v) {
    for (unsigned i = 0; i < v.size(); ++i) {
        unsigned minimo = i;
        for (unsigned j = i + 1; j < v.size(); ++j)
            if (v[j] < v[minimo])
                minimo = j;
        std::swap(v[i], v[minimo]);
    }
}
static void merge(std::vector<int> &v, std::vector<int> &aux, unsigned a, unsigned b) {
    if (b - a < 2)
        return;
    unsigned m = a + (b - a) / 2;
    merge(v, aux, a, m);
    merge(v, aux, m, b);
    unsigned i = a, j = m, k = a;
    while (i < m || j < b)
        aux[k++] = (j == b || (i < m && v[i] <= v[j])) ? v[i++] : v[j++];
    for (i = a; i < b; ++i)
        v[i] = aux[i];
}
void mergeSort(std::vector<int> &v) {
    std::vector<int> aux(v.size());
    merge(v, aux, 0, unsigned(v.size()));
}
static void validar(const std::vector<int> &objetos, int capacidad) {
    if (capacidad <= 0)
        throw std::invalid_argument("Capacidad positiva");
    for (int x : objetos)
        if (x <= 0 || x > capacidad)
            throw std::invalid_argument("Objeto fuera de capacidad");
}
unsigned nextFit(const std::vector<int> &objetos, int capacidad) {
    validar(objetos, capacidad);
    if (objetos.empty())
        return 0;
    unsigned cajas = 1;
    int libre = capacidad;
    for (int x : objetos) {
        if (x > libre) {
            ++cajas;
            libre = capacidad;
        }
        libre -= x;
    }
    return cajas;
}
unsigned bestFit(const std::vector<int> &objetos, int capacidad) {
    validar(objetos, capacidad);
    std::multiset<int> libres;
    for (int x : objetos) {
        auto i = libres.lower_bound(x);
        int libre = capacidad;
        if (i != libres.end()) {
            libre = *i;
            libres.erase(i);
        }
        libres.insert(libre - x);
    }
    return unsigned(libres.size());
}
unsigned bestFitDecreciente(std::vector<int> objetos, int capacidad) {
    mergeSort(objetos);
    std::reverse(objetos.begin(), objetos.end());
    return bestFit(objetos, capacidad);
}
static void letras(const std::string &s) {
    for (char c : s)
        if (c < 'a' || c > 'z')
            throw std::invalid_argument("Solo letras minusculas a-z");
}
bool esAnagramaOrdenando(std::string a, std::string b) {
    letras(a);
    letras(b);
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return a == b;
}
std::string productoPrimos(const std::string &palabra) {
    letras(palabra);
    const unsigned primos[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                               43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    constexpr std::uint64_t base = 1000000000;
    std::vector<std::uint32_t> bloques{1};
    for (char c : palabra) {
        std::uint64_t acarreo = 0;
        for (auto &bloque : bloques) {
            auto valor = std::uint64_t(bloque) * primos[c - 'a'] + acarreo;
            bloque = std::uint32_t(valor % base);
            acarreo = valor / base;
        }
        if (acarreo)
            bloques.push_back(std::uint32_t(acarreo));
    }
    std::ostringstream out;
    out << bloques.back();
    for (int i = int(bloques.size()) - 2; i >= 0; --i)
        out << std::setw(9) << std::setfill('0') << bloques[i];
    return out.str();
}
bool esAnagramaPrimos(const std::string &a, const std::string &b) {
    return productoPrimos(a) == productoPrimos(b);
}
std::vector<std::string> buscarAnagramas(std::istream &in, const std::string &palabra,
                                         bool primos) {
    letras(palabra);
    std::vector<std::string> resultado;
    std::set<std::string> vistos;
    std::string candidato;
    std::string firma = primos ? productoPrimos(palabra) : palabra;
    if (!primos)
        std::sort(firma.begin(), firma.end());
    while (in >> candidato) {
        if (candidato.size() != palabra.size())
            continue;
        std::string otra = primos ? productoPrimos(candidato) : candidato;
        if (!primos) {
            letras(otra);
            std::sort(otra.begin(), otra.end());
        }
        if (otra == firma && vistos.insert(candidato).second)
            resultado.push_back(candidato);
    }
    if (in.bad())
        throw std::runtime_error("Error de diccionario");
    return resultado;
}
std::vector<int> leerBpp(std::istream &in, int &capacidad) {
    int cantidad;
    if (!(in >> cantidad >> capacidad) || cantidad < 0)
        throw std::invalid_argument("Cabecera: cantidad capacidad");
    std::vector<int> objetos;
    int x;
    for (int i = 0; i < cantidad; ++i) {
        if (!(in >> x))
            throw std::invalid_argument("Faltan volumenes");
        objetos.push_back(x);
    }
    std::string extra;
    if (in >> extra)
        throw std::invalid_argument("Sobran valores");
    validar(objetos, capacidad);
    return objetos;
}
} // namespace ordenamiento
