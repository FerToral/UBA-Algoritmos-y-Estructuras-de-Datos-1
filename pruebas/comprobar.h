#pragma once
#include <stdexcept>
#include <string>
#define COMPROBAR(expresion) do { if (!(expresion)) throw std::runtime_error(std::string("Fallo: ")+ #expresion + " en linea " + std::to_string(__LINE__)); } while(false)
