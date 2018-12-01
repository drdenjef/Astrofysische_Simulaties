#ifndef HULPFUNCTIES_H
#define HULPFUNCTIES_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"

//functie voor berekenen kleinere h indien nodig (2 objecten dicht bij elkaar)
double variabele_h(double h, std::vector<Vec> posities);

// m = massa	r = positie		N = # deeltjes		i = beschouwde deeltje
Vec a(std::vector<double> m, std::vector<Vec> r, int i, int N);

//functie voor berekenen totale energie systeem
double Energie(std::vector<Vec> poslist, std::vector<Vec> velolist, std::vector<double> masslist);

//functie voor berekenen fout op energie
double error_energie(std::vector<Vec> poslist, std::vector<Vec> velolist, std::vector<double> masslist, double start_energie);

// functie die afstand berekent tussen 2 deeltjes
double afstand(Vec a, Vec b);

// functie die toelaat de dichtste afstand van 2 deeltjes te berekenen
double dichtste_afstand(std::vector<Vec> poslist);


#endif