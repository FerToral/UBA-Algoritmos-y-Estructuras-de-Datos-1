#pragma once
#include <iosfwd>
#include <map>
#include <string>
#include <vector>
namespace vectores_archivos {
bool divide(const std::vector<int> &v, int a);
int mayor(const std::vector<int> &v);
std::vector<int> reverso(std::vector<int> v);
std::vector<int> rotar(std::vector<int> v, int k);
bool estaOrdenado(const std::vector<int> &v);
std::vector<int> factoresPrimos(int n);
void mostrarVector(const std::vector<int> &v, std::ostream &salida);
std::vector<int> leerVector(std::istream &entrada);
std::vector<int> leerVector(const std::string &archivo);
void guardarVector(const std::vector<int> &v, const std::string &archivo);
int elementoMedio(const std::vector<int> &v);
std::map<int, unsigned> cantApariciones(std::istream &entrada);
void cantApariciones(const std::string &entrada, const std::string &salida);
unsigned cantidadAparicionesDePalabra(std::istream &entrada, const std::string &palabra);
void promedio(std::istream &a, std::istream &b, std::ostream &salida);
void promedio(const std::string &a, const std::string &b, const std::string &salida);
void ordenarSecuencias(std::istream &a, std::istream &b, std::ostream &salida);
void ordenarSecuencias(const std::string &a, const std::string &b, const std::string &salida);
std::vector<int> interseccion(std::istream &a, std::istream &b);
} // namespace vectores_archivos
