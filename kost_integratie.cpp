#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"
#include <numeric>

double kost_int_varh(std::vector<double> hlijst, double aantal_drivers, double aantal_deeltjes, double integratietijd) {
	//lengte van hlijst is ook aantal iteraties
	return hlijst.size() * aantal_drivers * aantal_deeltjes / integratietijd;
}


double kost_int_methode_varh(std::vector<double> hlijst, double aantal_deeltjes, int methode, double integratietijd) {

	double kost;
	//RK4
	if (methode == 1) {
		kost = kost_int_varh(hlijst, 4, aantal_deeltjes, integratietijd);
	}

	//ingebedde RK
	if (methode == 2) {
		kost = kost_int_varh(hlijst, 6, aantal_deeltjes, integratietijd);
	}

	//Verlet
	if (methode == 3) {
		kost = kost_int_varh(hlijst, 2, aantal_deeltjes, integratietijd);
	}

	//Forest-Ruth
	if (methode == 4) {
		kost = kost_int_varh(hlijst, 3, aantal_deeltjes, integratietijd);
	}

	//Leapfrog
	if (methode == 5) {
		kost = kost_int_varh(hlijst, 1, aantal_deeltjes, integratietijd);
	}

	//PEFRL
	if (methode == 6) {
		kost = kost_int_varh(hlijst, 4, aantal_deeltjes, integratietijd);
	}

	return kost;
}
