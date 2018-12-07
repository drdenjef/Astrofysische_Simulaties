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

void Leapfrog(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + "_LF.txt");
	outfile1 << std::setprecision(15);

	//lijst voor bijhouden van alle h's
	std::vector<double> h_lijst;

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
	std::vector<Vec> rhalf;
	for (int j = 0; j < N; j++) {
		rhalf.push_back(r[j] + (0.5*h_var * v[j]) + (0.125*h_var * h_var*a(m, r, j, N)));
	}


	std::vector<double> tijd_iteratie;

	double verstreken_tijd = 0;
	while (verstreken_tijd < integratietijd) {

		//voor onthouden vorige posities
		std::vector<Vec> vn;
		std::vector<Vec> rnhalf;

		double h_var = h;
		if (gebruiken_var_h)
			double h_var = variabele_h(h, r);
		verstreken_tijd += h_var;
		h_lijst.push_back(h_var);

		clock_t sstart = clock();

		for (int j = 0; j < N; j++) {

			Vec x = v[j] + h_var * a(m, rhalf, j, N);
			vn.push_back(x);
			rnhalf.push_back(rhalf[j] + h_var * x);

		}

		tijd_iteratie.push_back((clock() - sstart) / (CLOCKS_PER_SEC / 1000));


		//bereken gemiddelde positie vector (zit dan op zelfde "hoogte" als snelheid)
		for (int k = 0; k < rnhalf.size(); k++) {
			r[k] = 0.5*(rhalf[k] + rnhalf[k]);
			outfile1 << r[k].x() << ' ' << r[k].y() << ' ' << r[k].z() << '\t';
		}

		outfile1 << std::endl;
		outfile2 << Energie(r, vn, m) << std::endl;
		outfile3 << error_energie(r, vn, m, start_energie) << '\t' << dichtste_afstand(r) << std::endl;

		rhalf = rnhalf;
		v = vn;

	}

	std::cout << "De kost bedroeg " << kost_int_methode_varh(h_lijst, N, 5) << std::endl;;
	std::cout << "Posities werden bijgehouden in bestand " << naam << "_LF.txt" << std::endl;
	std::cout << "Energie werd bijgehouden in bestand " << naam << "_LF_E.txt" << std::endl;
	std::cout << "Relatieve energiefouten en dichtste afstanden werden bijgehouden in bestand " << naam << "_LF_E_err.txt" << std::endl;
	outfile1.close();
	outfile2.close();
	outfile3.close();

	double tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;

}