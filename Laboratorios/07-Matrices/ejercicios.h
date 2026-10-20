#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> productoVectorial(vector<int> u, vector<int> v);
void trasponer(vector<vector<int>> &m);
vector<vector<int>> multiplicar(vector<vector<int>> m1, vector<vector<int>> m2);
vector<vector<int>> promediar(vector<vector<int>> m);
int contarPicos(vector<vector<int>> m);
bool esTriangular(vector<vector<int>> m);
bool hayAmenaza(vector<vector<int>> m);
int diferenciaDiagonales(vector<vector<int>> m);
// Adicionales de la consigna: propuestas de 2026, no entregas historicas.
bool tatetiTerminado(vector<vector<int>> m);
long long caminosRobot(int x, int y);
