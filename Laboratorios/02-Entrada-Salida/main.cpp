#include "ejercicios.h"
#include <iostream>
#include <stdexcept>
int main(int argc, char **argv) {
    using namespace entrada_salida;
    try {
        int ejercicio = argc > 1 ? std::stoi(argv[1]) : 0;
        if (ejercicio >= 1 && ejercicio <= 3) {
            std::vector<int> notas;
            int n;
            std::cout << "Notas0..10"
                      << (ejercicio == 1 ? " (diez valores)" : " (-1 para terminar)") << ":\n";
            while ((ejercicio != 1 || notas.size() < 10) && std::cin >> n) {
                if (ejercicio != 1 && n == -1)
                    break;
                if (n < 0 || n > 10) {
                    std::cerr << "Nota invalida\n";
                    continue;
                }
                notas.push_back(n);
            }
            if ((ejercicio == 1 && notas.size() != 10) || (ejercicio == 3 && notas.size() < 6))
                throw std::invalid_argument("Cantidad insuficiente de estudiantes");
            auto r = analizar(notas);
            std::cout << "Suma: " << r.suma << " Promedio: " << r.promedio << '\n';
            if (ejercicio == 3)
                std::cout << "Aprobados: " << r.aprobados << " Reprobados: " << r.reprobados
                          << (r.ampliar ? " Se pueden ampliar las plazas" : "") << '\n';
        } else if (ejercicio == 4) {
            std::string n;
            std::cin >> n;
            std::cout << binarioADecimal(n) << '\n';
        } else if (ejercicio == 5) {
            double radio;
            if (!(std::cin >> radio))
                throw std::invalid_argument("Radio invalido");
            auto c = circulo(radio);
            std::cout << c.diametro << ' ' << c.circunferencia << ' ' << c.area << '\n';
        } else if (ejercicio == 6) {
            int cuenta = 5;
            std::cout << triplicarPorValor(cuenta) << " original=" << cuenta << '\n';
            triplicarPorReferencia(cuenta);
            std::cout << "Por referencia=" << cuenta << '\n';
        } else if (ejercicio == 7) {
            int a = 2, b = 7;
            intercambiar(a, b);
            std::cout << a << ' ' << b << '\n';
        } else if (ejercicio == 8) {
            auto pasos = collatzIterativo(11, std::cout);
            std::cout << "Pasos=" << pasos << '\n';
            collatzRecursivo(11, std::cout);
        } else if (ejercicio == 9) {
            int a, b;
            if (!(std::cin >> a >> b))
                throw std::invalid_argument("Dos enteros");
            auto r = divisionIterativa(a, b);
            std::cout << "Cociente=" << r.first << " resto=" << r.second << '\n';
        } else
            std::cout << "Uso: entrada_salida_demo <1..9>; ver README\n";
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
