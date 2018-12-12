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
*							 Runge-Kutta Method (RK4)									*
*																						*
****************************************************************************************/



void RK4(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, double integratietijd, double h, std::string naam, double gebruiken_var_h, int fractie) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + "_RK4.txt");
	outfile1 << std::setprecision(15);

	//lijst voor bijhouden van alle h's
	std::vector<double> h_lijst;


	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_RK4_E_err.txt");
	outfile2 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);

	//houdt tijden bij, om later gemiddelde te nemen
	std::vector<double> tijd_iteratie;

	// houd de iteraties bij
	int iteratie = 1;

	// houd de tijd bij van de simulatie
	double verstreken_tijd = 0;

	// start van de iteraties
	while (verstreken_tijd < integratietijd) {

		//check of variabele h nodig is
		double h_var = h;
		if (gebruiken_var_h)
			h_var = variabele_h(h, r);

		//voeg de huidige h toe aan verstreken tijd
		verstreken_tijd += h_var;
		h_lijst.push_back(h_var);

		//maak nodige k's aan
		std::vector<Vec> kr1;
		std::vector<Vec> kv1;
		std::vector<Vec> kr2;
		std::vector<Vec> kv2;
		std::vector<Vec> kr3;
		std::vector<Vec> kv3;
		std::vector<Vec> kr4;
		std::vector<Vec> kv4;

		clock_t sstart = clock();

		//voer alle tussenintegratiestappen uit
		for (int j = 0; j < N; j++) {
			kr1.push_back(v[j]);
			kv1.push_back(a(m, r, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr2.push_back(v[j] + .5*h_var*kv1[j]);
			kv2.push_back(a(m, r + .5*h_var*kr1, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr3.push_back(v[j] + .5*h_var*kv2[j]);
			kv3.push_back(a(m, r + .5*h_var*kr2, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr4.push_back(v[j] + h_var * kv3[j]);
			kv4.push_back(a(m, r + h_var * kr3, j, N));
		}

		//voer integratie uit
		r = r + (h_var / 6) * (kr1 + 2 * kr2 + 2 * kr3 + kr4);
		v = v + (h_var / 6) * (kv1 + 2 * kv2 + 2 * kv3 + kv4);

		tijd_iteratie.push_back((clock() - sstart) / (CLOCKS_PER_SEC / 1000));

		// bekijk of je deze iteratie wil wegschrijven
		if (iteratie % fractie == 0) {
			for (int j = 0; j < N; j++) {
				outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
			}
			outfile1 << std::endl;
			outfile2 << error_energie(r, v, m, start_energie) << '\t' << dichtste_afstand(r) << '\t' << verstreken_tijd << std::endl;
		}

		iteratie += 1;

	}

	//bereken gemiddelde tijd per iteratie
	double tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	// maak een file aan waar de kost en de duur van de simulatie wordt bijgehouden
	std::ofstream outfile3(naam + "_RK4_kost_duur_" + std::to_string(h) + ".txt");
	outfile3 << std::setprecision(15);
	outfile3 << kost_int_methode_varh(h_lijst, N, 1, integratietijd) << '\t' << tijd_gemiddelde << std::endl;
	outfile1.close();
	outfile2.close();
	outfile3.close();

	//zeg gebruiker naar waar alles is weggeschreven
	std::cout << "Posities werden bijgehouden in bestand " << naam << "_RK4.txt" << std::endl;
	std::cout << "Relatieve energiefouten, dichtste afstanden en de tijd werden bijgehouden in bestand " << naam << "_RK4_E_err.txt" << std::endl;
	std::cout << "De kost en de gemiddelde iteratieduur werden bijgehouden in bestand " << naam << "_RK4_kost_duur.txt" << std::endl;

	//zeg nog eens expliciet de kost en de gemiddelde tijd per iteratie
	std::cout << "De kost bedroeg " << kost_int_methode_varh(h_lijst, N, 1, integratietijd) << std::endl;
	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;
	std::cout << std::endl;

}