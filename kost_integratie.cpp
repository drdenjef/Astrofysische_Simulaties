#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"
#include <numeric>

double kost_int_varh(std::vector<double> hlijst, double aantal_drivers, double aantal_deeltjes) {
	//lengte van hlijst is ook aantal iteraties
	double teller = hlijst.size() * aantal_drivers * aantal_deeltjes;
	double noemer = 0;
	for (int i = 0; i < hlijst.size(); i++) {
		noemer += hlijst[i];
	}

	return teller / noemer;

}

double kost_int(double h, int iteraties, double aantal_drivers, double aantal_deeltjes) {
	//lengte van hlijst is ook aantal iteraties
	double teller = iteraties * aantal_drivers * aantal_deeltjes;
	double noemer = h*iteraties;

	return teller / noemer;

}

double kost_int_methode_varh(std::vector<double> hlijst, double aantal_deeltjes, int methode) {

	double kost;
	//RK4
	if (methode == 1) {
		kost = kost_int_varh(hlijst, 4, aantal_deeltjes);
	}

	//ingebedde RK
	if (methode == 2) {
		kost = kost_int_varh(hlijst, 6, aantal_deeltjes);
	}

	return kost;
}

double kost_int_methode(double h, int iteraties, double aantal_deeltjes, int methode) {

	double kost;
	
	//Verlet
	if (methode == 3) {
		kost = kost_int(h, iteraties, 2, aantal_deeltjes);
	}

	//Forest-Ruth
	if (methode == 4) {
		kost = kost_int(h, iteraties, 3, aantal_deeltjes);
	}

	//Leapfrog
	if (methode == 5) {
		kost = kost_int(h, iteraties, 1, aantal_deeltjes);
	}

	//PEFRL
	if (methode == 6) {
		kost = kost_int(h, iteraties, 4, aantal_deeltjes);
	}

	return kost;
}