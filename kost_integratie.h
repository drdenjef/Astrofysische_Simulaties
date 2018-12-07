#ifndef COSTINTEGRATION_H
#define COSTINTEGRATION_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"
//hlijst is een lijst van alle h's, is anders voor variabele h's
//aantal_drivers is aantal keer versnelling berekent per integratiestap
//aantal_deeltjes is aantal deeltjes, laat aantal driver evaluations per integratie linear schalen
double kost_int_varh(std::vector<double> hlijst, double aantal_drivers, double aantal_deeltjes);

double kost_int_methode_varh(std::vector<double> hlijst, double aantal_deeltjes, int methode);

#endif