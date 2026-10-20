#include "gtest/gtest.h"
#include "ej1/esPrimo.h"
#include "ej1/puntaje.h"
#include "ej2/llenarTaxis.h"
#include "ej3/baldosasDelPiso.h"
#include "ej3/contandoDragones.h"
#include "ej3/electores.h"
#include <climits>
#include <stdexcept>
TEST(Puntaje, CuatroRamas) {
    EXPECT_EQ(22,puntaje(6)); EXPECT_EQ(4,puntaje(7));
    EXPECT_EQ(22,puntaje(12)); EXPECT_EQ(1,puntaje(11));
}
TEST(Puntaje, FronteraDiezYCero) {
    EXPECT_EQ(28,puntaje(9)); EXPECT_EQ(0,puntaje(10)); EXPECT_EQ(10,puntaje(0));
}
TEST(Primos, Bordes) {
    EXPECT_FALSE(esPrimo(1)); EXPECT_TRUE(esPrimo(2));
    EXPECT_FALSE(esPrimo(49)); EXPECT_FALSE(esPrimo(-7));
}
// Consigna: diagnosticar los defectos docentes, NO arreglar las variantes.
TEST(Taxis, VarianteUnoNoComparteTresYUno) {
    EXPECT_EQ(2,llenarTaxis1(1,0,1)); // óptimo: 1
}
TEST(Taxis, VarianteDosDesaprovechaGrupoDeDos) {
    EXPECT_EQ(2,llenarTaxis2(1,1,0)); // óptimo: 1
}
TEST(Taxis, VarianteTresOmiteGrupoDeDosImpar) {
    EXPECT_EQ(0,llenarTaxis3(0,1,0)); // óptimo: 1
}
TEST(Taxis, VarianteTresPierdeDosPersonas) {
    EXPECT_EQ(1,llenarTaxis3(2,2,0)); // óptimo: 2
}
TEST(Taxis, VacioYTresGruposIguales) {
    EXPECT_EQ(0,llenarTaxis1(0,0,0)); EXPECT_EQ(0,llenarTaxis2(0,0,0));
    EXPECT_EQ(0,llenarTaxis3(0,0,0)); EXPECT_EQ(3,llenarTaxis1(1,1,1));
    EXPECT_EQ(2,llenarTaxis2(1,1,1)); EXPECT_EQ(1,llenarTaxis3(1,1,1));
}
TEST(Baldosas, ParticionesDivisibilidad) {
    EXPECT_EQ(6,baldosasDelPiso(4,6,2)); EXPECT_EQ(8,baldosasDelPiso(4,7,2));
    EXPECT_EQ(9,baldosasDelPiso(5,6,2)); EXPECT_EQ(12,baldosasDelPiso(5,7,2));
    EXPECT_EQ(1,baldosasDelPiso(1,1,9));
}
TEST(Baldosas, InvalidosYDesborde) {
    EXPECT_THROW(baldosasDelPiso(0,1,2),std::invalid_argument);
    EXPECT_THROW(baldosasDelPiso(1,-1,2),std::invalid_argument);
    EXPECT_THROW(baldosasDelPiso(1,1,0),std::invalid_argument);
    EXPECT_THROW(baldosasDelPiso(INT_MAX,INT_MAX,1),std::overflow_error);
}
TEST(Dragones, ParticionesCoprimosYMultiplos) {
    EXPECT_EQ(8,contandoDragones(30,2,3,5));
    EXPECT_EQ(22,contandoDragones(30,6,10,15));
    EXPECT_EQ(15,contandoDragones(30,2,4,8));
    // Los múltiplos de 4 y 6 ya son pares: quedan los 15 impares.
    EXPECT_EQ(15,contandoDragones(30,2,4,6));
}
TEST(Dragones, ContrasteExhaustivoPequeno) {
    for(int t=0;t<=50;++t) for(int a=1;a<8;++a)
        for(int b=a+1;b<9;++b) for(int c=b+1;c<10;++c) {
            int esperado=0;
            for(int i=1;i<=t;++i) esperado+=i%a!=0 && i%b!=0 && i%c!=0;
            ASSERT_EQ(esperado,contandoDragones(t,a,b,c));
        }
}
TEST(Dragones, BordesYDominios) {
    EXPECT_EQ(0,contandoDragones(0,2,3,4)); EXPECT_EQ(0,contandoDragones(100,1,2,3));
    EXPECT_EQ(INT_MAX-3,contandoDragones(INT_MAX,INT_MAX-2,INT_MAX-1,INT_MAX));
    EXPECT_THROW(contandoDragones(-1,2,3,4),std::invalid_argument);
    EXPECT_THROW(contandoDragones(10,0,3,4),std::invalid_argument);
    EXPECT_THROW(contandoDragones(10,2,2,4),std::invalid_argument);
}
TEST(Electores, LimitesEdad) {
    EXPECT_EQ(NO_VOTA,validarVotanteEnEleccion(2001,10,23,2017));
    EXPECT_EQ(OPCIONAL_MENOR,validarVotanteEnEleccion(2001,10,22,2017));
    EXPECT_EQ(OPCIONAL_MENOR,validarVotanteEnEleccion(1999,10,23,2017));
    EXPECT_EQ(OBLIGATORIO,validarVotanteEnEleccion(1999,10,22,2017));
    EXPECT_EQ(OBLIGATORIO,validarVotanteEnEleccion(1947,10,23,2017));
    EXPECT_EQ(OPCIONAL_MAYOR,validarVotanteEnEleccion(1947,10,22,2017));
}
TEST(Electores, Calendario) {
    EXPECT_EQ(OBLIGATORIO,validarVotanteEnEleccion(2000,2,29,2025));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(1900,2,29,2025));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2001,2,29,2025));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2000,4,31,2025));
}
TEST(Electores, InvalidosFuturos) {
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(0,1,1,2017));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2000,0,1,2017));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2000,13,1,2017));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2000,1,0,2017));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2018,1,1,2017));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2017,10,23,2017));
    EXPECT_EQ(NO_VOTA,validarVotanteEnEleccion(2017,10,22,2017));
    EXPECT_EQ(ERROR,validarVotanteEnEleccion(2000,1,1,0));
}
TEST(Electores, AnioExplicito) {
    EXPECT_EQ(OPCIONAL_MENOR,validarVotante(2001,10,22));
    EXPECT_EQ(OBLIGATORIO,validarVotanteEnEleccion(2001,10,22,2025));
}
