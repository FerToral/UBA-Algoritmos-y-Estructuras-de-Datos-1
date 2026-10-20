#include "risas.h"
#include <fstream>
#include <stdexcept>

std::vector<char> leerDatos(std::string filename) {
    std::ifstream archivo(filename);
    if (!archivo) throw std::runtime_error("No se pudo abrir " + filename);
    std::vector<char> caracteres;
    char c;
    while (archivo >> c) caracteres.push_back(c);
    return caracteres;
}
int leerLargoReal(std::string filename) {
    std::ifstream archivo(filename);
    int largo;
    if (!(archivo >> largo)) throw std::runtime_error("Resultado invalido: " + filename);
    return largo;
}
int risaMasLarga(std::vector<char> s) {
    int actual = 0, mayor = 0;
    char anterior = 0;
    for (char c : s) {
        if (c != 'h' && c != 'a') actual = 0;
        else actual = (actual > 0 && c != anterior) ? actual+1 : 1;
        if (actual > mayor) mayor = actual;
        anterior = c;
    }
    return mayor;
}
