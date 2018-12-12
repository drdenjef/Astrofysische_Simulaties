#ifndef RKF45_H
#define RKF45_H
#define _USE_MATH_DEFINES
#include <vector>
#include "3DVectClass.h"

//functie voor RKF45 integratie
void RKF45(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie);

#endif