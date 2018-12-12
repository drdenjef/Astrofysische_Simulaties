#ifndef PEFRL_H
#define PEFRL_H
#define _USE_MATH_DEFINES
#include <vector>
#include "3DVectClass.h"

//functie voor PEFRL integratie
void PEFRL(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie);

#endif