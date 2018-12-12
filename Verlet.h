#ifndef VERLET_H
#define VERLET_H
#include <vector>
#include "3DVectClass.h"

//functie voor Verlet integratie
void Verlet(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v,  int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie);

#endif