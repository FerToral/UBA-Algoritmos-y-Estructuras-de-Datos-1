#include "ejercicios.h"
#include <chrono>
#include <fstream>
#include <iostream>
int main(int argc, char **argv) {
    using namespace ordenamiento;
    try {
        if (argc < 3) {
            std::cout << "Uso: ordenamiento_demo bpp archivo.in | anagramas palabra "
                         "[diccionario]\n";
            return 0;
        }
        std::string modo = argv[1];
        if (modo == "bpp") {
            std::ifstream in(argv[2]);
            if (!in)
                throw std::runtime_error("No se abre el archivo");
            int capacidad;
            auto objetos = leerBpp(in, capacidad);
            auto inicio = std::chrono::steady_clock::now();
            auto ordenados = objetos;
            mergeSort(ordenados);
            double ms =
                std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - inicio)
                    .count();
            std::cout << "Objetos=" << objetos.size() << " capacidad=" << capacidad
                      << "\nNextFit=" << nextFit(objetos, capacidad)
                      << " BestFit=" << bestFit(objetos, capacidad)
                      << " BestFitDecreciente=" << bestFitDecreciente(objetos, capacidad)
                      << "\nMergeSort_ms=" << ms << '\n';
        } else if (modo == "anagramas") {
            std::string ruta = argc > 3 ? argv[3] : "datos/ingles.dic";
            for (bool primos : {false, true}) {
                std::ifstream in(ruta);
                if (!in)
                    throw std::runtime_error("No se abre el diccionario");
                std::cout << (primos ? "Primos" : "Ordenamiento") << ":\n";
                for (const auto &palabra : buscarAnagramas(in, argv[2], primos))
                    std::cout << palabra << '\n';
            }
        } else
            throw std::invalid_argument("Modo desconocido");
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
