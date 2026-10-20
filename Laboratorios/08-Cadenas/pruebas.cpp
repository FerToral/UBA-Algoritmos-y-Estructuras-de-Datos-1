#include "cadenas.hpp"
#include "src/risas.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <stdexcept>
TEST(Rotar, EjemploConsigna) {
    EXPECT_EQ("olah", rotar("hola", 7));
}
TEST(Rotar, Ciclos) {
    EXPECT_EQ("hola", rotar("hola", 0));
    EXPECT_EQ("hola", rotar("hola", 4));
    EXPECT_EQ("ahol", rotar("hola", 1));
}
TEST(Rotar, VacioYUnCaracter) {
    EXPECT_EQ("", rotar("", 3));
    EXPECT_EQ("a", rotar("a", 1000000000));
}
TEST(Rotar, GrandeYNegativo) {
    EXPECT_EQ("hola", rotar("hola", 1000000000));
    EXPECT_THROW(rotar("hola", -1), std::invalid_argument);
}
TEST(Subsecuencia, EjemplosConsigna) {
    EXPECT_TRUE(subsecuencia("ace", "abcdec"));
    EXPECT_FALSE(subsecuencia("abdc", "abcecde"));
}
TEST(Subsecuencia, Vacios) {
    EXPECT_TRUE(subsecuencia("", ""));
    EXPECT_TRUE(subsecuencia("", "abc"));
    EXPECT_FALSE(subsecuencia("a", ""));
}
TEST(Subsecuencia, Repetidos) {
    EXPECT_FALSE(subsecuencia("aa", "a"));
    EXPECT_TRUE(subsecuencia("aa", "aba"));
    EXPECT_FALSE(subsecuencia("aaa", "aba"));
    EXPECT_TRUE(subsecuencia("aaa", "abaca"));
}
TEST(Subsecuencia, OrdenNoEsPertenencia) {
    EXPECT_FALSE(subsecuencia("ba", "ab"));
    EXPECT_TRUE(subsecuencia("ab", "aab"));
}
TEST(Subsecuencia, ContrasteExhaustivoPorSubconjuntos) {
    for (int longitud = 0; longitud <= 6; ++longitud)
        for (int bits = 0; bits < (1 << longitud); ++bits) {
            std::string t;
            for (int i = 0; i < longitud; ++i)
                t += (bits & (1 << i)) ? 'a' : 'b';
            for (int ls = 0; ls <= 4; ++ls)
                for (int bs = 0; bs < (1 << ls); ++bs) {
                    std::string s;
                    for (int i = 0; i < ls; ++i)
                        s += (bs & (1 << i)) ? 'a' : 'b';
                    bool esperado = false;
                    for (int mascara = 0; mascara < (1 << longitud); ++mascara) {
                        std::string extraida;
                        for (int i = 0; i < longitud; ++i)
                            if (mascara & (1 << i))
                                extraida += t[i];
                        esperado = esperado || extraida == s;
                    }
                    ASSERT_EQ(esperado, subsecuencia(s, t));
                }
        }
}

TEST(GuiaCompleta, BordesYArchivosDeRisas) {
    EXPECT_EQ("", darVueltaK("", 3));
    EXPECT_THROW(darVueltaK("abc", 0), std::invalid_argument);
    EXPECT_EQ("rbaacabadar", darVueltaK("abracadabra", 3));
    EXPECT_TRUE(esPalindromo(""));
    EXPECT_EQ((std::vector<std::vector<std::string>>{{"", ""}, {"ab", "ba"}}),
              agruparAnagramas({"", "ab", "", "ba"}));
    EXPECT_THROW(leerDatos("risas/no-existe"), std::runtime_error);
    for (int i = 1; i <= 54; ++i) {
        const std::string nombre = "risas/" + (i < 10 ? std::string("0") : "") + std::to_string(i);
        // El paquete docente tiene series 01-04,10-14,...,50-54.
        std::ifstream archivo(nombre);
        if (archivo)
            EXPECT_EQ(leerLargoReal(nombre + ".a"), risaMasLarga(leerDatos(nombre)));
    }
}
TEST(Felicitaciones, ContrastePorTodasLasPermutacionesPequenas) {
    const std::vector<std::string> opciones = {"", "D", "R", "RD", "DR", "RDR", "DRD"};
    for (int codigo = 0; codigo < 2401; ++codigo) {
        int valor = codigo;
        std::vector<std::string> nombres;
        for (int i = 0; i < 4; ++i) {
            nombres.push_back(opciones[valor % 7]);
            valor /= 7;
        }
        std::sort(nombres.begin(), nombres.end());
        int esperado = 0;
        do {
            int pares = 0;
            bool tengoD = false;
            for (const auto &nombre : nombres)
                for (char c : nombre) {
                    if (c == 'D')
                        tengoD = true;
                    if (c == 'R' && tengoD) {
                        ++pares;
                        tengoD = false;
                    }
                }
            esperado = std::max(esperado, pares);
        } while (std::next_permutation(nombres.begin(), nombres.end()));
        ASSERT_EQ(esperado, cantidadDeFelicitaciones(nombres));
    }
}
TEST(MiddleOut, ContrastePorMovimientosReales) {
    // BFS independiente: retirar un caracter y ponerlo al inicio o al final.
    for (const std::string inicial : {"aabb", "abca", "abcde"}) {
        std::map<std::string, int> distancia{{inicial, 0}};
        std::queue<std::string> pendientes;
        pendientes.push(inicial);
        while (!pendientes.empty()) {
            const auto actual = pendientes.front();
            pendientes.pop();
            ASSERT_EQ(distancia[actual], middleOut(inicial, actual));
            for (std::size_t i = 0; i < actual.size(); ++i)
                for (bool frente : {false, true}) {
                    auto siguiente = actual;
                    const char c = siguiente[i];
                    siguiente.erase(i, 1);
                    if (frente)
                        siguiente.insert(siguiente.begin(), c);
                    else
                        siguiente.push_back(c);
                    if (!distancia.count(siguiente)) {
                        distancia[siguiente] = distancia[actual] + 1;
                        pendientes.push(siguiente);
                    }
                }
        }
    }
    EXPECT_EQ(0, middleOut("", ""));
    EXPECT_EQ(-1, middleOut("ab", "aaa"));
}
