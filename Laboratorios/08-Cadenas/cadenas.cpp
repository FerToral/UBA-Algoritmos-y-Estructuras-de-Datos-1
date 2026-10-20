#include "cadenas.hpp"
#include <algorithm>
#include <array>
#include <map>
#include <stdexcept>

std::vector<std::string> split(std::string s, char delim) {
    std::vector<std::string> partes;
    std::string actual;
    for (char c : s) {
        if (c == delim) {
            if (!actual.empty())
                partes.push_back(actual);
            actual.clear();
        } else
            actual.push_back(c);
    }
    if (!actual.empty())
        partes.push_back(actual);
    return partes;
}
std::string darVueltaPalabra(std::string s) {
    const auto partes = split(s, ' ');
    std::string resultado;
    for (std::size_t i = partes.size(); i > 0; --i) {
        if (!resultado.empty())
            resultado.push_back(' ');
        for (char c : partes[i - 1])
            resultado.push_back(c);
    }
    return resultado;
}
std::vector<std::vector<std::string>> agruparAnagramas(std::vector<std::string> v) {
    std::map<std::array<int, 256>, std::size_t> grupos;
    std::vector<std::vector<std::string>> resultado;
    for (const auto &palabra : v) {
        std::array<int, 256> frecuencias{};
        for (unsigned char c : palabra)
            ++frecuencias[c];
        auto encontrado = grupos.find(frecuencias);
        if (encontrado == grupos.end()) {
            grupos[frecuencias] = resultado.size();
            resultado.push_back({palabra});
        } else
            resultado[encontrado->second].push_back(palabra);
    }
    return resultado;
}
bool esPalindromo(std::string s) {
    for (std::size_t i = 0; i < s.size() / 2; ++i)
        if (s[i] != s[s.size() - 1 - i])
            return false;
    return true;
}
bool tieneRepetidos(std::string s) {
    std::array<bool, 256> vistos{};
    for (unsigned char c : s) {
        if (vistos[c])
            return true;
        vistos[c] = true;
    }
    return false;
}
std::string rotar(std::string s, int j) {
    if (j < 0)
        throw std::invalid_argument("La cantidad debe ser no negativa");
    if (s.empty())
        return s;
    const auto giro = static_cast<std::size_t>(j) % s.size();
    std::string resultado;
    for (std::size_t i = 0; i < s.size(); ++i)
        resultado.push_back(s[(i + s.size() - giro) % s.size()]);
    return resultado;
}
bool subsecuencia(std::string s, std::string t) {
    std::size_t indice = 0;
    for (char caracter : t)
        if (indice < s.size() && s[indice] == caracter)
            ++indice;
    return indice == s.size();
}

std::string darVueltaK(std::string s, int k) {
    if (k <= 0)
        throw std::invalid_argument("El bloque debe ser positivo");
    std::string resultado;
    const auto bloque = static_cast<std::size_t>(k);
    for (std::size_t inicio = 0; inicio < s.size(); inicio += bloque) {
        const auto fin = std::min(s.size(), inicio + bloque);
        for (std::size_t i = fin; i > inicio; --i)
            resultado.push_back(s[i - 1]);
    }
    return resultado;
}
std::string abueloLaino(std::string s) {
    for (char c : s)
        if (c == 'i' || c == 'I')
            return "N";
    return "S";
}
int cantidadDeFelicitaciones(std::vector<std::string> v) {
    int internos = 0, dd = 0, rr = 0, rd = 0;
    for (const auto &nombre : v) {
        char primero = 0, ultimo = 0;
        for (char c : nombre)
            if (c == 'D' || c == 'R') {
                if (!primero)
                    primero = c;
                if (ultimo == 'D' && c == 'R')
                    ++internos;
                ultimo = c;
            }
        if (primero == 'D' && ultimo == 'D')
            ++dd;
        if (primero == 'R' && ultimo == 'R')
            ++rr;
        if (primero == 'R' && ultimo == 'D')
            ++rd;
    }
    // Los bloques RD forman una cadena. DD/RR permiten cerrar sus extremos.
    const int enlaces = rd + std::min(dd, rr) - (rd > 0 && dd == 0 && rr == 0);
    return internos + enlaces;
}
int middleOut(std::string s, std::string t) {
    if (s.size() != t.size())
        return -1;
    std::array<int, 256> balance{};
    for (unsigned char c : s)
        ++balance[c];
    for (unsigned char c : t)
        --balance[c];
    for (int frecuencia : balance)
        if (frecuencia != 0)
            return -1;
    // Lo no movido debe ser un intervalo de t y una subsecuencia de s.
    std::size_t conservados = 0;
    for (std::size_t inicio = 0; inicio < t.size(); ++inicio) {
        std::size_t fin = inicio;
        for (char c : s)
            if (fin < t.size() && t[fin] == c)
                ++fin;
        conservados = std::max(conservados, fin - inicio);
    }
    return static_cast<int>(s.size() - conservados);
}
