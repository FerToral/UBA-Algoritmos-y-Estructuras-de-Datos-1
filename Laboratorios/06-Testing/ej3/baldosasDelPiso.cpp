#include "baldosasDelPiso.h"
#include <limits>
#include <stdexcept>
// Propuesta nueva: redondear cada lado, no el área.
int baldosasDelPiso(int M, int N, int B) {
    if (M <= 0 || N <= 0 || B <= 0)
        throw std::invalid_argument("Las dimensiones deben ser positivas");
    const long long total = (1LL + (M-1)/B) * (1LL + (N-1)/B);
    if (total > std::numeric_limits<int>::max())
        throw std::overflow_error("La cantidad no cabe en int");
    return static_cast<int>(total);
}
