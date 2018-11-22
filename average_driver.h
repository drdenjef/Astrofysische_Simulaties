#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "3DVectClass.h"
using namespace std;


// basisidee:
//
// input: 
// lijst van alle h-waarden ; 
// aantal drivers-functies uitgevoerd in een loop (bij RK4 bv is dit 4); 
// aantal deeltjes en 
// tijdseenheid waarin je het gemmidelde wilt.
//
// berekening:
// elke element word bij elkaar opgetelt tot je bij of iets voorbij de tijdseenheid zit. je houd ook bij hoeveel elementen er zijn.
// eens voorbij steek je het aantal elementen in een vector en reset je de som en het aantal elementen.
// vervolgens word er gezocht naar het gemiddelde van de vector van aantal loops per unit.
// het resultaat is dan het gemmidelde aantal loops per unit maal het aantal deeltjes maal het aantal drivers.
// (voor elk deeltje moet de drivers functie gebruikt worden, hierdoor moet vermenigvuldigd worden door het aantal deeltjes)

double average_driver(vector<double> hlist, double num_drivers, double num_particles, double t_unit) {
	double number = 0;
	double sum = 0;
	vector<double> average_loop;
	for (int i = 0; i < hlist.size(); i += 1) {
		sum += hlist[i];
		number += 1;
		if( sum >= t_unit){
			average_loop.push_back(number);
			sum = 0;
			number = 0;
		};
	};
	double average = 0;
	for (int j = 0; j < average_loop.size(); j += 1) {
		average += average_loop[j];
	};
	average /= average_loop.size();
	return average * num_drivers * num_particles;
};