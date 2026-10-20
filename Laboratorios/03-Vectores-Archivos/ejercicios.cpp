#include "ejercicios.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
namespace vectores_archivos {
bool divide(const std::vector<int> &v, int a) {
    if (!a)
        throw std::invalid_argument("Divisor no nulo");
    for (int x : v)
        if (static_cast<long long>(x) % a)
            return false;
    return true;
}
int mayor(const std::vector<int> &v) {
    if (v.empty())
        throw std::invalid_argument("Vector no vacio");
    return *std::max_element(v.begin(), v.end());
}
std::vector<int> reverso(std::vector<int> v) {
    std::reverse(v.begin(), v.end());
    return v;
}
std::vector<int> rotar(std::vector<int> v, int k) {
    if (v.empty())
        return v;
    long long pasos = k % static_cast<long long>(v.size());
    if (pasos < 0)
        pasos += v.size();
    std::rotate(v.begin(), v.begin() + pasos, v.end());
    return v;
}
bool estaOrdenado(const std::vector<int> &v) {
    return std::is_sorted(v.begin(), v.end()) || std::is_sorted(v.rbegin(), v.rend());
}
std::vector<int> factoresPrimos(int n) {
    if (n < 1)
        throw std::invalid_argument("Entero positivo");
    std::vector<int> r;
    for (int p = 2; p <= n / p; ++p)
        while (n % p == 0) {
            r.push_back(p);
            n /= p;
        }
    if (n > 1)
        r.push_back(n);
    return r;
}
void mostrarVector(const std::vector<int> &v, std::ostream &out) {
    out << '[';
    for (unsigned i = 0; i < v.size(); ++i) {
        if (i)
            out << ", ";
        out << v[i];
    }
    out << ']';
}
static bool siguiente(std::istream &in, int &x) {
    std::string token;
    if (!(in >> token)) {
        if (in.eof())
            return false;
        throw std::runtime_error("Error al leer el archivo");
    }
    try {
        std::size_t usados = 0;
        long long valor = std::stoll(token, &usados);
        if (usados != token.size() || valor < INT_MIN || valor > INT_MAX)
            throw std::invalid_argument("Entero fuera de rango");
        x = static_cast<int>(valor);
        return true;
    } catch (const std::exception &) {
        throw std::invalid_argument("Archivo con un valor no entero representable");
    }
}
static std::ifstream abrir(const std::string &ruta) {
    std::ifstream in(ruta);
    if (!in)
        throw std::runtime_error("No se puede abrir " + ruta);
    return in;
}
static void guardar(const std::string &ruta, const std::string &contenido) {
    std::ofstream out(ruta);
    if (!out)
        throw std::runtime_error("No se puede escribir " + ruta);
    out << contenido;
    if (!out)
        throw std::runtime_error("Escritura incompleta");
}
std::vector<int> leerVector(std::istream &in) {
    std::vector<int> r;
    int x;
    while (siguiente(in, x))
        r.push_back(x);
    return r;
}
std::vector<int> leerVector(const std::string &ruta) {
    auto in = abrir(ruta);
    return leerVector(in);
}
void guardarVector(const std::vector<int> &v, const std::string &ruta) {
    std::ostringstream out;
    mostrarVector(v, out);
    guardar(ruta, out.str() + "\n");
}
int elementoMedio(const std::vector<int> &v) {
    long long derecha = std::accumulate(v.begin(), v.end(), 0LL), izquierda = 0;
    for (int x : v) {
        izquierda += x;
        derecha -= x;
        if (izquierda > derecha)
            return x;
    }
    throw std::domain_error("No hay cruce de sumas");
}
std::map<int, unsigned> cantApariciones(std::istream &in) {
    std::map<int, unsigned> r;
    int x;
    while (siguiente(in, x))
        ++r[x];
    return r;
}
void cantApariciones(const std::string &origen, const std::string &destino) {
    auto in = abrir(origen);
    auto r = cantApariciones(in);
    std::ostringstream out;
    for (const auto &par : r)
        out << par.first << ' ' << par.second << '\n';
    guardar(destino, out.str());
}
unsigned cantidadAparicionesDePalabra(std::istream &in, const std::string &palabra) {
    unsigned n = 0;
    std::string token;
    while (in >> token)
        if (token == palabra)
            ++n;
    if (in.bad())
        throw std::runtime_error("Fallo al leer texto");
    return n;
}
void promedio(std::istream &a, std::istream &b, std::ostream &out) {
    std::ostringstream temporal;
    int x, y;
    bool primero = true;
    while (true) {
        bool hayA = siguiente(a, x), hayB = siguiente(b, y);
        if (hayA != hayB)
            throw std::invalid_argument("Las secuencias deben tener la misma longitud");
        if (!hayA)
            break;
        if (!primero)
            temporal << ' ';
        primero = false;
        temporal << (static_cast<long long>(x) + y) / 2.0;
    }
    out << temporal.str() << '\n';
}
void promedio(const std::string &a, const std::string &b, const std::string &destino) {
    auto inA = abrir(a), inB = abrir(b);
    std::ostringstream out;
    promedio(inA, inB, out);
    guardar(destino, out.str());
}
void ordenarSecuencias(std::istream &a, std::istream &b, std::ostream &out) {
    int x = 0, y = 0, antA = 0, antB = 0;
    bool hayA = siguiente(a, x), hayB = siguiente(b, y), primero = true;
    std::ostringstream temporal;
    while (hayA || hayB) {
        if (!primero)
            temporal << ' ';
        primero = false;
        if (!hayB || (hayA && x <= y)) {
            temporal << x;
            antA = x;
            hayA = siguiente(a, x);
            if (hayA && x < antA)
                throw std::invalid_argument("Primera secuencia no ordenada");
        } else {
            temporal << y;
            antB = y;
            hayB = siguiente(b, y);
            if (hayB && y < antB)
                throw std::invalid_argument("Segunda secuencia no ordenada");
        }
    }
    out << temporal.str() << '\n';
}
void ordenarSecuencias(const std::string &a, const std::string &b, const std::string &destino) {
    auto inA = abrir(a), inB = abrir(b);
    std::ostringstream out;
    ordenarSecuencias(inA, inB, out);
    guardar(destino, out.str());
}
std::vector<int> interseccion(std::istream &a, std::istream &b) {
    std::set<int> enA, emitidos;
    int x;
    while (siguiente(a, x))
        enA.insert(x);
    std::vector<int> r;
    while (siguiente(b, x))
        if (enA.count(x) && emitidos.insert(x).second)
            r.push_back(x);
    return r;
}
} // namespace vectores_archivos
