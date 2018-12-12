#ifndef COSTINTEGRATION_H
#define COSTINTEGRATION_H
#include <cmath>
#include <vector>
//hlijst is een lijst van alle h's (want er kunnen variabele h_s berekend zijn/worden)
//aantal_drivers is aantal keer versnelling berekent per integratiestap
//aantal_deeltjes is aantal deeltjes, laat aantal driver evaluations per integratie linear schalen
double kost_int_varh(std::vector<double> hlijst, double aantal_drivers, double aantal_deeltjes, double integratietijd);

double kost_int_methode_varh(std::vector<double> hlijst, double aantal_deeltjes, int methode, double integratietijd);

#endif