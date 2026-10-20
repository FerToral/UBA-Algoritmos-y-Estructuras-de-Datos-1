#include "ejercicios.h"
#include <stdexcept>

bool existePico(vector<int> v) {
    bool res = false;
    // I: res equivale a que existe un pico en [1,i).
    for (size_t i = 1; i + 1 < v.size(); ++i)
        res = res || (v[i] > v[i - 1] && v[i] > v[i + 1]);
    return res;
}
int mcd(int m, int n) {
    if (m <= 0 || n <= 0)
        throw invalid_argument("Se requieren enteros positivos");
    int a = m, b = n;
    // I: a,b positivos, acotados por los iniciales, mcd(a,b)=mcd(m,n).
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}
int indiceMinSubsec(vector<int> v, int l, int r) {
    if (l < 0 || r < l || static_cast<size_t>(r) >= v.size())
        throw out_of_range("Intervalo invalido");
    int res = r;
    // I: res pertenece a [l,r] y minimiza el sufijo ya recorrido.
    for (int i = r; i >= l; --i)
        if (v[i] <= v[res])
            res = i;
    return res;
}
void ordenar1(vector<int> &v) {
    // I: prefijo [0,i) ordenado; todo el sufijo es >= que ese prefijo.
    for (size_t i = 0; i < v.size(); ++i) {
        int minimo = indiceMinSubsec(v, static_cast<int>(i), static_cast<int>(v.size() - 1));
        const int aux = v[i];
        v[i] = v[minimo];
        v[minimo] = aux;
    }
}
void ordenar2(vector<int> &v) {
    for (int x : v)
        if (x < 0 || x > 2)
            throw invalid_argument("Solo 0,1,2");
    int i = 0, j = 0, k = static_cast<int>(v.size()) - 1;
    // I: [0,i)=0, [i,j)=1, (k,n)=2; [j,k] sin clasificar.
    while (j <= k) {
        if (v[j] == 0) {
            const int aux = v[i];
            v[i++] = v[j];
            v[j++] = aux;
        } else if (v[j] == 1)
            ++j;
        else {
            const int aux = v[k];
            v[k--] = v[j];
            v[j] = aux;
        }
    }
}
tuple<int, int> division(int n, int d) {
    if (n < 0 || d <= 0)
        throw invalid_argument("Dividendo no negativo y divisor positivo");
    int q = 0, r = n;
    // I: n=q*d+r, r>=n mod d; el resto decrece.
    while (r >= d) {
        r -= d;
        ++q;
    }
    return make_tuple(q, r);
}
