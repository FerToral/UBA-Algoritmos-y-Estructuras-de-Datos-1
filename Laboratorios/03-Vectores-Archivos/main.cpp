#include "ejercicios.h"
#include <fstream>
#include <iostream>
#include <sstream>
int main(int argc, char **argv) {
    using namespace vectores_archivos;
    try {
        if (argc > 1) {
            auto v = leerVector(argv[1]);
            std::cout << "Vector: ";
            mostrarVector(v, std::cout);
            std::cout << "\nMaximo: " << mayor(v) << "\nCruce de sumas: " << elementoMedio(v)
                      << '\n';
            if (argc > 2)
                guardarVector(rotar(v, 2), argv[2]);
        } else {
            std::vector<int> v{1, 2, 3, 4, 5, 6};
            mostrarVector(rotar(v, 2), std::cout);
            std::cout << '\n';
            std::istringstream a("1 2 3 4"), b("1 25 3 12");
            promedio(a, b, std::cout);
            std::cout << "Uso con archivo: vectores_archivos_demo datos/numeros.in "
                         "[salida.txt]\n";
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
