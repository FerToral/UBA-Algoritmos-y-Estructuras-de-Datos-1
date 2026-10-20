#include "ejercicios.h"
#include "gtest/gtest.h"
#include <limits>
#include <stdexcept>

TEST(Bordes, ProductoVacioYRectangular) {
    EXPECT_TRUE(productoVectorial({}, {1, 2}).empty());
    EXPECT_EQ(productoVectorial({1, 2}, {}).size(), 2u);
    EXPECT_EQ(productoVectorial({-1, 2}, {3, -4}), (vector<vector<int>>{{-3, 4}, {6, -8}}));
}
TEST(Bordes, TraspuestaVaciaUnoYDosVeces) {
    vector<vector<int>> vacia;
    trasponer(vacia);
    vector<vector<int>> m = {{1, -2}, {3, 4}}, original = m;
    trasponer(m);
    trasponer(m);
    EXPECT_EQ(m, original);
    vector<vector<int>> uno = {{7}};
    trasponer(uno);
    EXPECT_EQ(uno[0][0], 7);
    vector<vector<int>> rectangular = {{1, 2, 3}, {4, 5, 6}};
    EXPECT_THROW(trasponer(rectangular), invalid_argument);
}
TEST(Bordes, MultiplicarRectangularYNegativos) {
    EXPECT_EQ(multiplicar({{1, 2}}, {{3}, {4}}), (vector<vector<int>>{{11}}));
    EXPECT_EQ(multiplicar({{-1, 2}, {3, -4}}, {{1}, {2}}), (vector<vector<int>>{{3}, {-5}}));
    EXPECT_THROW(multiplicar({{1, 2}}, {{1, 2}}), invalid_argument);
}
TEST(Bordes, PromedioIncluyeCentroYNoAlteraFuente) {
    vector<vector<int>> m = {{1, 2}, {3, 4}}, copia = m;
    EXPECT_EQ(promediar(m), (vector<vector<int>>{{2, 2}, {2, 2}}));
    EXPECT_EQ(m, copia);
    EXPECT_EQ(promediar({{-1, 0}, {0, 0}}), (vector<vector<int>>{{-1, -1}, {-1, -1}}));
}
TEST(Bordes, PicosNoIncluyenCentroNiAceptanEmpates) {
    EXPECT_EQ(contarPicos({{0, 0}, {0, 0}}), 0);
    EXPECT_EQ(contarPicos({{9, 0}, {0, 1}}), 1);
    EXPECT_EQ(contarPicos({{-1, -2}, {-3, -4}}), 1);
}
TEST(Bordes, TriangularVaciaEIdentidad) {
    EXPECT_TRUE(esTriangular({}));
    EXPECT_TRUE(esTriangular({{3}}));
    EXPECT_TRUE(esTriangular({{1, 0}, {0, 1}}));
    EXPECT_FALSE(esTriangular({{1, 2}, {3, 4}}));
    EXPECT_THROW(esTriangular({{1, 2}}), invalid_argument);
}
TEST(Bordes, AmenazasRectangularesFilasColumnasYDiagonales) {
    EXPECT_FALSE(hayAmenaza({{0, 0, 0}, {0, 0, 0}}));
    EXPECT_FALSE(hayAmenaza({{1, 0, 0}, {0, 0, 1}}));
    EXPECT_TRUE(hayAmenaza({{1, 0, 1}, {0, 0, 0}}));
    EXPECT_TRUE(hayAmenaza({{1, 0, 0}, {1, 0, 0}}));
    EXPECT_TRUE(hayAmenaza({{1, 0, 0}, {0, 1, 0}}));
    EXPECT_THROW(hayAmenaza({{2, 0}, {0, 0}}), invalid_argument);
}
TEST(Bordes, DiferenciaDiagonalesYDesbordamientos) {
    EXPECT_EQ(diferenciaDiagonales({}), 0);
    EXPECT_EQ(diferenciaDiagonales({{1, 2}, {3, 4}}), 0);
    EXPECT_THROW(productoVectorial({numeric_limits<int>::max()}, {2}), overflow_error);
    EXPECT_THROW(diferenciaDiagonales({{numeric_limits<int>::max(), -1}, {-1, 1}}), overflow_error);
}
TEST(Bordes, RechazoDeMatricesIrregulares) {
    vector<vector<int>> irregular = {{1}, {2, 3}};
    EXPECT_THROW(trasponer(irregular), invalid_argument);
    EXPECT_THROW(multiplicar(irregular, {{1}}), invalid_argument);
    EXPECT_THROW(promediar(irregular), invalid_argument);
    EXPECT_THROW(contarPicos(irregular), invalid_argument);
    EXPECT_THROW(hayAmenaza(irregular), invalid_argument);
}
TEST(Adicionales, TatetiTresYGeneralizado) {
    EXPECT_TRUE(tatetiTerminado({{1, 1, 1}, {0, 2, 0}, {2, 0, 0}}));
    EXPECT_TRUE(tatetiTerminado({{1, 2, 1}, {1, 2, 2}, {2, 1, 1}})); // lleno, sin ganador
    EXPECT_FALSE(tatetiTerminado({{0, 0, 0}, {0, 1, 0}, {0, 0, 2}}));
    EXPECT_TRUE(tatetiTerminado({{2, 0}, {0, 2}}));
    EXPECT_TRUE(tatetiTerminado({{1}}));
    EXPECT_THROW(tatetiTerminado({}), invalid_argument);
}
TEST(Adicionales, RobotSinFormulaCerrada) {
    EXPECT_EQ(caminosRobot(0, 0), 1);
    EXPECT_EQ(caminosRobot(0, 9), 1);
    EXPECT_EQ(caminosRobot(2, 2), 6);
    EXPECT_EQ(caminosRobot(3, 2), 10);
    for (int x = 1; x < 12; ++x)
        for (int y = 1; y < 12; ++y) {
            EXPECT_EQ(caminosRobot(x, y), caminosRobot(x - 1, y) + caminosRobot(x, y - 1));
            EXPECT_EQ(caminosRobot(x, y), caminosRobot(y, x));
        }
    EXPECT_THROW(caminosRobot(-1, 1), invalid_argument);
    EXPECT_THROW(caminosRobot(40, 40), overflow_error);
}
