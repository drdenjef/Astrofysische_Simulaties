#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include "3DVectClass.h"
#include "hulpfuncties.h"
#include "kost_integratie.h"
using namespace std;

/****************************************************************************************
*																						*
*								Verlet Method											*
*																						*
****************************************************************************************/

void Verlet(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + "_V.txt");
	outfile1 << std::setprecision(15);

	//lijst voor bijhouden van alle h's
	std::vector<double> h_lijst;

	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_V_E_err.txt");
	outfile2 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);

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

		for (int i = 0; i < N; i++) {
			v[i] = v[i] + 0.5 * h_var * a(m, r, i, N);
			r[i] = r[i] + h_var * v[i];
			v[i] = v[i] + 0.5 * h_var * a(m, r, i, N);

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

	std::cout << "De kost bedroeg " << kost_int_methode_varh(h_lijst, N, 3, integratietijd) << std::endl;
	std::cout << "Posities werden bijgehouden in bestand " << naam << "_V.txt" << std::endl;
	std::cout << "Relatieve energiefouten, dichtste afstanden en de tijd werden bijgehouden in bestand " << naam << "_V_E_err.txt" << std::endl;
	outfile1.close();
	outfile2.close();

	double tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;

}