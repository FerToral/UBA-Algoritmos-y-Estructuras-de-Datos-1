#include "ejercicios.hpp"
#include <limits>
#include <stdexcept>
#include <iostream>
int main() {
    int fallos=0,a=std::numeric_limits<int>::max(),b=1;
    ::swap(a,b);
    fallos += a!=1 || b!=std::numeric_limits<int>::max();
    ::swap(a,a); fallos += a!=1;
    fallos += fibonacci(0)!=0 || fibonacci(1)!=1 || fibonacci(10)!=55
           || fibonacci(46)!=1836311903;
    try { fibonacci(47); ++fallos; } catch(const std::overflow_error&) {}
    fallos += !estaOrdenado({}) || !estaOrdenado({1,1,2}) || !estaOrdenado({3,3,1})
           || estaOrdenado({1,3,2});
    fallos += rotar({1,2,3,4,5,6},2)!=std::vector<int>({3,4,5,6,1,2})
           || rotar({},10)!=std::vector<int>{} || rotar({1},1000000)!=std::vector<int>{1};
    int q,r; division(31,19,q,r); fallos += q!=1 || r!=12;
    division(0,7,q,r); fallos += q!=0 || r!=0;
    try { division(3,0,q,r); ++fallos; } catch(const std::invalid_argument&) {}
    std::cout << "Fallos: " << fallos << '\n';
    return fallos ? 1 : 0;
}
