#include <iostream>
#include "ejercicios.hpp"
using namespace std;

int main() {
    /* No hace falta modificar el main */
    // Leo las entradas
    int n;
    cin >> n;
    int i = 0;
    int x;
    vector<int> v;// En v leo el vector
    while (i<n){
        cin >> x;
        v.push_back(x);
        i++;
    }

    // Evaluo si el vector v esta ordenado
    bool res = estaOrdenado(v);

    // Imprimo la salida
    cout << (res?"True":"False");

    return 0;
}
