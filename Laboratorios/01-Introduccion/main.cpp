#include "ejercicios.h"
#include <iostream>
int main() {
    using namespace introduccion;
    std::cout << "Siguiente de10: " << siguiente(10) << "\nSuma3+5: " << suma(3, 5)
              << "\nFibonacci20: " << fibonacciRecursivo(20)
              << "\nImpares menores que10: " << imparesFor(10)
              << "\nDivisores de12: " << divisoresWhile(12)
              << "\nCombinatorio10,3: " << combinatorioIterativo(10, 3) << '\n';
}
