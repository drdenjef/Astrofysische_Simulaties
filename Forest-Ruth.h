#ifndef FORESTRUTH_H
#define FORESTRUTH_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "3DVectClass.h"
#include "hulpfuncties.h"



// functie ForestRuth die posities + snelheden van deeltjes teruggeeft
void ForestRuth(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie);

#endif