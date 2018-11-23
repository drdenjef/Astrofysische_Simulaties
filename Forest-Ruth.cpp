
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"

using namespace std;

/*****************************************
*										 *
*  Forest-Ruth Method   *
*										 *
*****************************************/

void ForestRuth(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam +"_FR.txt");
	outfile1 << std::setprecision(15);

	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;

	// maak een file aan waar de energieën worden bijgehouden
	std::ofstream outfile2(naam +"_FR_E.txt");
	outfile2 << std::setprecision(15);

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile3(naam +"_FR_E_err.txt");
	outfile3 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);


	double theta = 1. / (2. - pow(2., 1. / 3.));

	// iteratie over aantal integraties
	for (int k = 0; k < iteraties; k++) {

		//check of variabele h nodig is
		double h_var = variabele_h(h, r);

		//iteratie over aantal deeltjes
		for (int i = 0; i < N; i++) {
			// substep 1
			
			r[i] = r[i] + (0.5*theta*h_var)*v[i];

			// berekenen van de versnelling
			Vec acc = a(m, r, i, N);

			// substeps 2 & 3
			v[i] = v[i] + theta * h_var*acc;
			r[i] = r[i] + 0.5*(1 - theta)*h_var*v[i];
			// berekenen van de versnelling
			acc = a(m, r, i, N);

			//substeps 4 & 5
			v[i] = v[i] + ((1 - 2 * theta) * h_var) * acc;
			r[i] = r[i] + 0.5*(1 - theta)*h_var*v[i];

			// berekenen van de versnelling
			acc = a(m, r, i, N);

			// substeps 6 & 7
			v[i] = v[i] + theta * h_var*acc;
			r[i] = r[i] + 0.5*theta*h_var*v[i];

			//uitschrijven naar file
			outfile1 << r[i].x() << ' ' << r[i].y() << ' ' << r[i].z() << '\t';
		}
		outfile1 << std::endl;

		//uitschrijven van energie en error_energie
		outfile2 << Energie(r, v, m) << std::endl;
		outfile3 << error_energie(r, v, m, start_energie) << std::endl;
	}
	outfile1.close();
	outfile2.close();
	outfile3.close();
	std::cout << "Posities werden bijgehouden in bestand " << naam <<  "_FR.txt" << std::endl;
	std::cout << "Energie werd bijgehouden in bestand " << naam << "_FR_E.txt" << std::endl;
	std::cout << "Relatieve energiefouten werden bijgehouden in bestand " << naam << "_FR_E_err.txt" << std::endl;
	
}
