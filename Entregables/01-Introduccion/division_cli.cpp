#include <iostream>
#include "ejercicios.hpp"
using namespace std;

int main() {
    /* No hace falta modificar el main */
    //Leo la entrada
    int divisor,dividendo,cociente,resto;
    cin >> dividendo>>divisor;

    //Calculo la division
    division(dividendo,divisor,cociente,resto);

    //Salida
    cout << cociente << " " << resto;

    return 0;
}
