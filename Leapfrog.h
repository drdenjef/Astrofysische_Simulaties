#ifndef LEAPFROG_H
#define LEAPFROG_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"



void Leapfrog(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam);


#endif