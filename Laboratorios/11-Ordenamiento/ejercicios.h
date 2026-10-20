#pragma once
#include <iosfwd>
#include <string>
#include <vector>
namespace ordenamiento {
void insertionSort(std::vector<int> &v);
void selectionSort(std::vector<int> &v);
void mergeSort(std::vector<int> &v);
unsigned nextFit(const std::vector<int> &objetos, int capacidad);
unsigned bestFit(const std::vector<int> &objetos, int capacidad);
unsigned bestFitDecreciente(std::vector<int> objetos, int capacidad);
bool esAnagramaOrdenando(std::string a, std::string b);
std::string productoPrimos(const std::string &palabra);
bool esAnagramaPrimos(const std::string &a, const std::string &b);
std::vector<std::string> buscarAnagramas(std::istream &diccionario, const std::string &palabra,
                                         bool primos);
std::vector<int> leerBpp(std::istream &in, int &capacidad);
} // namespace ordenamiento
