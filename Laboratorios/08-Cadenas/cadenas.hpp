#pragma once
#include <string>
#include <vector>
std::vector<std::string> split(std::string s, char delim);
std::string darVueltaPalabra(std::string s);
std::vector<std::vector<std::string>> agruparAnagramas(std::vector<std::string> v);
bool esPalindromo(std::string s);
bool tieneRepetidos(std::string s);
std::string darVueltaK(std::string s, int k);
std::string abueloLaino(std::string s);
int cantidadDeFelicitaciones(std::vector<std::string> v);
int middleOut(std::string s, std::string t);
std::string rotar(std::string s, int j);
bool subsecuencia(std::string s, std::string t);
