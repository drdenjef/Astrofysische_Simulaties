#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <numeric> 
#include "3DVectClass.h"
#include "hulpfuncties.h"
#include "kost_integratie.h"

/****************************************************************************************
*																						*
*								Leapfrog Method											*
*																						*
****************************************************************************************/

void Leapfrog(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie) {

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

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_LF_E_err.txt");
	outfile2 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);
	double h_var = h;
	if (gebruiken_var_h)
		h_var = variabele_h(h, r);

	// Eerste aparte behandeling voor positie
	std::vector<Vec> r0;
	for (int j = 0; j < N; j++) {
		r0.push_back(r[j] + (0.5*h_var * v[j]) + (0.125*h_var * h_var*a(m, r, j, N)));
	}
	r = r0;

	//houdt tijden bij, om later gemiddelde te nemen
	std::vector<double> tijd_iteratie;

	// houd de iteraties bij
	int iteratie = 1;

	// houd de tijd bij van de simulatie
	double verstreken_tijd = 0;

	//voor onthouden vorige posities, en alvast met iets opvullen
	std::vector<Vec> r_volg = r;

	//voor juiste niveau te kunnen uitschrijven vorige posities, en alvast met iets opvullen
	std::vector<Vec> r_half = r;

	// start van de iteraties
	while (verstreken_tijd < integratietijd) {

		//check of variabele h nodig is
		double h_var = h;
		if (gebruiken_var_h)
			h_var = variabele_h(h, r);

		//voeg de huidige h toe aan verstreken tijd
		verstreken_tijd += h_var;
		h_lijst.push_back(h_var);

		clock_t sstart = clock();

		//voegt integratie uit
		for (int j = 0; j < N; j++) {

			v[j] = v[j] + h_var * a(m, r, j, N);
			r_volg[j] = r[j] + h_var * v[j];

		}

		tijd_iteratie.push_back((clock() - sstart) / (CLOCKS_PER_SEC / 1000));


		// bekijk of je deze iteratie wil wegschrijven
		if (iteratie % fractie == 0) {
			//bereken gemiddelde positie vector (zit dan op zelfde "hoogte" als snelheid)
			for (unsigned int k = 0; k < r.size(); k++) {
				r_half[k] = 0.5*(r[k] + r_volg[k]);
				outfile1 << r_half[k].x() << ' ' << r_half[k].y() << ' ' << r_half[k].z() << '\t';
			}
			outfile1 << std::endl;
			outfile2 << error_energie(r_half, v, m, start_energie) << '\t' << dichtste_afstand(r_half) << '\t' << verstreken_tijd << std::endl;
		}

		r = r_volg;

		iteratie += 1;

	}

	//bereken gemiddelde tijd per iteratie
	double tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	// maak een file aan waar de kost en de duur van de simulatie wordt bijgehouden
	std::ofstream outfile3(naam + "_LF_kost_duur_" + std::to_string(h) + ".txt");
	outfile3 << std::setprecision(15);
	outfile3 << kost_int_methode_varh(h_lijst, N, 5, integratietijd) << '\t' << tijd_gemiddelde << std::endl;
	outfile1.close();
	outfile2.close();
	outfile3.close();

	//zeg gebruiker naar waar alles is weggeschreven
	std::cout << "Posities werden bijgehouden in bestand " << naam << "_LF.txt" << std::endl;
	std::cout << "Relatieve energiefouten, dichtste afstanden en de tijd werden bijgehouden in bestand " << naam << "_LF_E_err.txt" << std::endl;
	std::cout << "De kost en de gemiddelde iteratieduur werden bijgehouden in bestand " << naam << "_LF_kost_duur.txt" << std::endl;

	//zeg nog eens expliciet de kost en de gemiddelde tijd per iteratie
	std::cout << "De kost bedroeg " << kost_int_methode_varh(h_lijst, N, 5, integratietijd) << std::endl;
	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;
	std::cout << std::endl;
}