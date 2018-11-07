#ifndef EMBEDDED_RK_H
#define EMBEDDED_RK_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "Embedded_RK.h"

// m = massa	r = positie		N = # deeltjes		i = beschouwde deeltje
Vec a(std::vector<float> m, std::vector<Vec> r, int i, int N);

// functie RKF45 die posities van deeltjes teruggeeft
std::vector<std::vector<std::vector<Vec>>> RKF45(std::vector<float> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, float h);






#endif