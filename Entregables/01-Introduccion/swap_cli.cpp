#include <iostream>
#include "ejercicios.hpp"
using namespace std;

int main() {
    /* No hace falta modificar el main */
    int a,b;
    //Leo a
    cin >> a >> b;

    swap(a,b);

    //Devuelvo despues del swap
    cout << a << " " << b;
    return 0;
}
