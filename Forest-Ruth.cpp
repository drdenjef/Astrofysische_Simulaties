#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <numeric> 
#include "3DVectClass.h"
#include "hulpfuncties.h"
#include "kost_integratie.h"

using namespace std;

/*****************************************
*										 *
*          Forest-Ruth Method            *
*										 *
*****************************************/

void ForestRuth(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + "_FR.txt");
	outfile1 << std::setprecision(15);

	//lijst voor bijhouden van alle h's
	std::vector<double> h_lijst;

	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_FR_E_err.txt");
	outfile2 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);

	std::vector<Vec> acc;
	for (int j = 0; j < N; j++) {
		acc.push_back(Vec(0., 0., 0.));
	}

	double theta = 1. / (2. - pow(2., 1. / 3.));

	std::vector<double> tijd_iteratie;

	// houd de iteraties bij
	int iteratie = 1;

	// houd de tijd bij van de simulatie
	double verstreken_tijd = 0;

	// start van de iteraties
	while (verstreken_tijd < integratietijd) {

		double h_var = h;
		if (gebruiken_var_h)
			h_var = variabele_h(h, r);

		verstreken_tijd += h_var;
		h_lijst.push_back(h_var);

		clock_t sstart = clock();
		//iteratie over aantal deeltjes
		for (int i = 0; i < N; i++) {
			// substep 1

			r[i] = r[i] + (0.5*theta*h_var)*v[i];
		}

		for (int i = 0; i < N; i++) {
			// berekenen van de versnelling
			acc[i] = (a(m, r, i, N));
		}

		for (int i = 0; i < N; i++) {
			// substeps 2 & 3
			v[i] = v[i] + theta * h_var*acc[i];
			r[i] = r[i] + 0.5*(1. - theta)*h_var*v[i];
		}

		for (int i = 0; i < N; i++) {
			// berekenen van de versnelling
			acc[i] = a(m, r, i, N);
		}

		for (int i = 0; i < N; i++) {

			//substeps 4 & 5
			v[i] = v[i] + ((1. - 2 * theta) * h_var) * acc[i];
			r[i] = r[i] + 0.5*(1. - theta)*h_var*v[i];

		}

		for (int i = 0; i < N; i++) {
			// berekenen van de versnelling
			acc[i] = a(m, r, i, N);

		}

		for (int i = 0; i < N; i++) {
			// substeps 6 & 7
			v[i] = v[i] + theta * h_var*acc[i];
			r[i] = r[i] + 0.5*theta*h_var*v[i];
		}

		tijd_iteratie.push_back((clock() - sstart) / (CLOCKS_PER_SEC / 1000));

		// bekijk of je deze iteratie wil wegschrijven
		if (iteratie % fractie == 0) {
			for (int i = 0; i < N; i++) {
				outfile1 << r[i].x() << ' ' << r[i].y() << ' ' << r[i].z() << '\t';
			}
			outfile1 << std::endl;
			outfile2 << error_energie(r, v, m, start_energie) << '\t' << dichtste_afstand(r) << '\t' << verstreken_tijd << std::endl;
		}

		iteratie += 1;

	}




	std::cout << "Posities werden bijgehouden in bestand " << naam << "_FR.txt" << std::endl;
	std::cout << "Relatieve energiefouten, dichtste afstanden en de tijd werden bijgehouden in bestand " << naam << "_FR_E_err.txt" << std::endl;
	std::cout << "De kost bedroeg " << kost_int_methode_varh(h_lijst, N, 4, integratietijd) << std::endl;
	std::cout << "De kost en de gemiddelde iteratieduur werden bijgehouden in bestand " << naam << "_kost_duur.txt" << std::endl;
	outfile1.close();
	outfile2.close();

	double tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	std::cout << "De kost bedroeg " << kost_int_methode_varh(h_lijst, N, 4, integratietijd) << std::endl;
	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;
	std::cout << std::endl;

	// maak een file aan waar de kost en de duur van de simulatie wordt bijgehouden
	std::ofstream outfile3(naam + "_FR_kost_duur_" + std::to_string(h) + ".txt");
	outfile3 << std::setprecision(15);
	outfile3 << kost_int_methode_varh(h_lijst, N, 4, integratietijd) << '\t' << tijd_gemiddelde << std::endl;
	outfile3.close();

}