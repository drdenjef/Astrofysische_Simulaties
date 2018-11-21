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

void Leapfrog(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + "_LF.txt");
	outfile1 << std::setprecision(15);

	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;

	// maak een file aan waar de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_LF_E.txt");
	outfile2 << std::setprecision(15);

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile3(naam + "_LF_E_err.txt");
	outfile3 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);
	double h_var = h;
	//double h_var = variabele_h(h, r);

	// Eerste aparte behandeling voor positie
	for (int j = 0; j < N; j++) {
		r[j] = r[j] + (h_var * v[j] / 2.0) + (h_var * h_var*a(m, r, j, N) / 8);
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;



	std::vector<double> tijd_iteratie;

	for (int i = 0; i < iteraties; i++) {

		//voor onthouden vorige posities
		std::vector<Vec> r_tijd;

		double h_var = h;

		clock_t sstart = clock();

		for (int j = 0; j < N; j++) {

			v[j] = v[j] + h_var * a(m, r, j, N);
			//sla vorige positie op voor nieuwe berekent wordt
			r_tijd.push_back(r[j]);

			r[j] = r[j] + h_var * v[j];

		}

		tijd_iteratie.push_back((clock() - sstart) / (CLOCKS_PER_SEC / 1000));

		for (int j = 0; j < N; j++) {
			outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
		}

		std::vector<Vec> gem_r;
		//bereken gemiddelde positie vector (zit dan op zelfde "hoogte" als snelheid)
		for (int k = 0; k < r_tijd.size(); k++) {
			gem_r.push_back(r[k] + r_tijd[k] / 2);
		}

		outfile1 << std::endl;
		outfile2 << Energie(gem_r, v, m) << std::endl;
		outfile3 << error_energie(gem_r, v, m, start_energie) << std::endl;

		//alle tijdelijke vectoren terug leeg flushen;
		r_tijd.clear();
		gem_r.clear();

	}

	std::cout << "Posities werden bijgehouden in bestand " << naam << "_LF.txt" << std::endl;
	std::cout << "Energie werd bijgehouden in bestand " << naam << "_LF_E.txt" << std::endl;
	std::cout << "Relatieve energiefouten werden bijgehouden in bestand " << naam << "_LF_E_err.txt" << std::endl;
	outfile1.close();
	outfile2.close();
	outfile3.close();

	double tijd_gemiddelde;
	tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;


}