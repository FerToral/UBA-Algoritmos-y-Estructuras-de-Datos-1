#include "cadenas.hpp"
#include <iostream>
using namespace std;
int main() {
    /* No hace falta modificar el main */
    // Leo la entrada
    string s;
    int j;
    cin >> s >> j;
    string res = rotar(s, j);
    cout << res;
    return 0;
}
