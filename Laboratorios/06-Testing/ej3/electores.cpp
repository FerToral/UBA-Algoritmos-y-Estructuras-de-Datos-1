#include "electores.h"
namespace {
bool fechaValida(int a, int m, int d) {
    if (a < 1 || m < 1 || m > 12 || d < 1) return false;
    const bool bisiesto = a%400 == 0 || (a%4 == 0 && a%100 != 0);
    const int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return d <= dias[m-1] + (m == 2 && bisiesto ? 1 : 0);
}
}
// El PDF no fija año electoral: se recibe explícitamente.
int validarVotanteEnEleccion(int a, int m, int d, int anioEleccion) {
    if (!fechaValida(a,m,d) || anioEleccion < 1) return ERROR;
    if (a > anioEleccion || (a == anioEleccion && (m > 10 || (m == 10 && d > 22))))
        return ERROR;
    const int edad = anioEleccion-a-(m > 10 || (m == 10 && d > 22));
    if (edad < 16) return NO_VOTA;
    if (edad < 18) return OPCIONAL_MENOR;
    if (edad < 70) return OBLIGATORIO;
    return OPCIONAL_MAYOR;
}
int validarVotante(int a, int m, int d) {
    // Convención de mantenimiento, no año acreditado por la fuente.
    return validarVotanteEnEleccion(a,m,d,2017);
}
