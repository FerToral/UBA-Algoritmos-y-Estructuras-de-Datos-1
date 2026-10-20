#include "ejercicios.hpp"
#include <stdexcept>
#include <limits>

int fibonacci(int n) {
    if (n < 0) throw std::invalid_argument("Indice no negativo");
    int anterior=0, actual=1;
    if(n==0) return 0;
    for(int i=1;i<n;++i) {
        if(anterior > std::numeric_limits<int>::max()-actual)
            throw std::overflow_error("Fibonacci excede int");
        const int siguiente=anterior+actual; anterior=actual; actual=siguiente;
    }
    return actual;
}
void swap(int& a,int& b) {
    const int anterior=a; a=b; b=anterior;
}
void division(int n,int d,int& q,int& r) {
    if(n<0 || d<=0) throw std::invalid_argument("Dividendo no negativo y divisor positivo");
    q=0; r=n;
    while(r>=d) { r-=d; ++q; }
}
bool estaOrdenado(std::vector<int> v) {
    bool creciente=true,decreciente=true;
    for(std::size_t i=1;i<v.size();++i) {
        creciente=creciente && v[i-1]<=v[i];
        decreciente=decreciente && v[i-1]>=v[i];
    }
    return creciente || decreciente;
}
std::vector<int> rotar(std::vector<int> v,int k) {
    if(k<0) throw std::invalid_argument("Giro no negativo");
    if(v.empty()) return v;
    const auto giro=static_cast<std::size_t>(k)%v.size();
    std::vector<int> resultado;
    for(std::size_t i=0;i<v.size();++i) resultado.push_back(v[(i+giro)%v.size()]);
    return resultado;
}
