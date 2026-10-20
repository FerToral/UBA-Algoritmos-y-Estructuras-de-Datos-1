// Propuestas de resolución de 2026 sobre el taller UBA 1C2022.
// Consigna y casos docentes conservados; no son entregas históricas recuperadas.
#include "ejercicios.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace {
using Matriz = vector<vector<int>>;
void rectangular(const Matriz &m) {
    if (!m.empty())
        for (const auto &fila : m)
            if (fila.size() != m[0].size())
                throw invalid_argument("Matriz irregular");
}
void cuadrada(const Matriz &m) {
    rectangular(m);
    if (!m.empty() && m.size() != m[0].size())
        throw invalid_argument("Se requiere matriz cuadrada");
}
void region(const Matriz &m) {
    rectangular(m);
    if (m.size() < 2 || m[0].size() < 2)
        throw invalid_argument("Minimo 2x2");
}
int entero(long long valor) {
    if (valor < numeric_limits<int>::min() || valor > numeric_limits<int>::max())
        throw overflow_error("Resultado no representable como int");
    return static_cast<int>(valor);
}
} // namespace

vector<vector<int>> productoVectorial(vector<int> u, vector<int> v) {
    vector<vector<int>> res(u.size(), vector<int>(v.size()));
    for (size_t i = 0; i < u.size(); ++i)
        for (size_t j = 0; j < v.size(); ++j)
            res[i][j] = entero(1LL * u[i] * v[j]);
    return res;
}

void trasponer(vector<vector<int>> &m) {
    cuadrada(m);
    for (size_t i = 0; i < m.size(); ++i)
        for (size_t j = i + 1; j < m.size(); ++j)
            swap(m[i][j], m[j][i]);
}

vector<vector<int>> multiplicar(vector<vector<int>> a, vector<vector<int>> b) {
    rectangular(a);
    rectangular(b);
    if (a.empty() || b.empty() || b[0].empty() || a[0].size() != b.size())
        throw invalid_argument("Dimensiones incompatibles");
    vector<vector<int>> res(a.size(), vector<int>(b[0].size(), 0));
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = 0; j < b[0].size(); ++j) {
            long long suma = 0;
            for (size_t k = 0; k < b.size(); ++k) {
                long long producto = 1LL * a[i][k] * b[k][j];
                if ((producto > 0 && suma > numeric_limits<long long>::max() - producto) ||
                    (producto < 0 && suma < numeric_limits<long long>::min() - producto))
                    throw overflow_error("Suma no representable");
                suma += producto;
            }
            res[i][j] = entero(suma);
        }
    return res;
}

vector<vector<int>> promediar(vector<vector<int>> m) {
    region(m);
    auto res = m;
    int alto = static_cast<int>(m.size()), ancho = static_cast<int>(m[0].size());
    for (int i = 0; i < alto; ++i)
        for (int j = 0; j < ancho; ++j) {
            long long suma = 0;
            int cantidad = 0;
            for (int a = max(0, i - 1); a <= min(alto - 1, i + 1); ++a)
                for (int b = max(0, j - 1); b <= min(ancho - 1, j + 1); ++b) {
                    suma += m[a][b];
                    ++cantidad;
                }
            // div matematico con divisor positivo: piso, tambien en negativos.
            res[i][j] = entero(suma / cantidad - (suma % cantidad < 0 ? 1 : 0));
        }
    return res;
}

int contarPicos(vector<vector<int>> m) {
    region(m);
    int alto = static_cast<int>(m.size()), ancho = static_cast<int>(m[0].size()), total = 0;
    for (int i = 0; i < alto; ++i)
        for (int j = 0; j < ancho; ++j) {
            bool pico = true;
            for (int a = max(0, i - 1); a <= min(alto - 1, i + 1); ++a)
                for (int b = max(0, j - 1); b <= min(ancho - 1, j + 1); ++b)
                    if ((a != i || b != j) && m[i][j] <= m[a][b])
                        pico = false;
            if (pico)
                ++total;
        }
    return total;
}

bool esTriangular(vector<vector<int>> m) {
    cuadrada(m);
    bool superior = true, inferior = true;
    for (size_t i = 0; i < m.size(); ++i)
        for (size_t j = 0; j < m.size(); ++j) {
            if (i > j && m[i][j] != 0)
                superior = false;
            if (i < j && m[i][j] != 0)
                inferior = false;
        }
    return superior || inferior;
}

bool hayAmenaza(vector<vector<int>> m) {
    region(m);
    vector<pair<int, int>> reinas;
    for (int i = 0; i < static_cast<int>(m.size()); ++i)
        for (int j = 0; j < static_cast<int>(m[i].size()); ++j) {
            if (m[i][j] != 0 && m[i][j] != 1)
                throw invalid_argument("Tablero no binario");
            if (m[i][j] == 1)
                reinas.push_back({i, j});
        }
    for (size_t a = 0; a < reinas.size(); ++a)
        for (size_t b = a + 1; b < reinas.size(); ++b)
            if (reinas[a].first == reinas[b].first || reinas[a].second == reinas[b].second ||
                abs(reinas[a].first - reinas[b].first) == abs(reinas[a].second - reinas[b].second))
                return true;
    return false;
}

int diferenciaDiagonales(vector<vector<int>> m) {
    cuadrada(m);
    long long diferencia = 0;
    for (size_t i = 0; i < m.size(); ++i) {
        diferencia += m[i][i];
        diferencia -= m[i][m.size() - 1 - i];
    }
    return entero(diferencia < 0 ? -diferencia : diferencia);
}

bool tatetiTerminado(vector<vector<int>> m) {
    cuadrada(m);
    if (m.empty())
        throw invalid_argument("Tablero vacio");
    for (const auto &fila : m)
        for (int casilla : fila)
            if (casilla < 0 || casilla > 2)
                throw invalid_argument("Fichas 0,1,2");
    size_t n = m.size();
    for (size_t i = 0; i < n; ++i) {
        bool fila = m[i][0] != 0, columna = m[0][i] != 0;
        for (size_t j = 1; j < n; ++j) {
            fila = fila && m[i][j] == m[i][0];
            columna = columna && m[j][i] == m[0][i];
        }
        if (fila || columna)
            return true;
    }
    bool principal = m[0][0] != 0, secundaria = m[0][n - 1] != 0, lleno = true;
    for (size_t i = 0; i < n; ++i) {
        principal = principal && m[i][i] == m[0][0];
        secundaria = secundaria && m[i][n - 1 - i] == m[0][n - 1];
        for (int casilla : m[i])
            lleno = lleno && casilla != 0;
    }
    return principal || secundaria || lleno;
}

long long caminosRobot(int x, int y) {
    if (x < 0 || y < 0)
        throw invalid_argument("Coordenadas no negativas");
    vector<long long> caminos(static_cast<size_t>(y) + 1, 1);
    for (int i = 0; i < x; ++i)
        for (int j = 1; j <= y; ++j) {
            if (caminos[j] > numeric_limits<long long>::max() - caminos[j - 1])
                throw overflow_error("Demasiados caminos");
            caminos[j] += caminos[j - 1];
        }
    return caminos[y];
}
