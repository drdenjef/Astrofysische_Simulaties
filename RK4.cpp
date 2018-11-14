#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "3DVectClass.h"
#include "hulpfuncties.h"


/*****************************************
*										 *
*  Runge-Kutta Method (RK4)   *
*										 *
*****************************************/



void RK4(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + ".txt");
	outfile1 << std::setprecision(15);

	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;



	// maak een file aan waar de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_E.txt");
	outfile2 << std::setprecision(15);

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile3(naam + "_E_err.txt");
	outfile3 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);

	// begint te itereren over het aantal iteraties die je wilt uitvoeren
	// kan meegegeven worden aan de functie RKF45
	for (int i = 0; i < iteraties; i++) {

		double h_var = variabele_h(h, r);

		// begint te itereren over alle deeltjes
		for (int j = 0; j < N; j++) {

			//voor elk deeltje, maak alle nodige k's aan

			Vec kr1 = v[j];
			//r[j] = r[j]
			Vec kv1 = a(m, r, j, N);

			Vec kr2 = v[j] + .5*h_var*kv1;
			r[j] = r[j] + .5*h_var*kr1;
			Vec kv2 = a(m, r, j, N);

			Vec kr3 = v[j] + .5*h_var*kv2;
			r[j] = r[j] + .5*h_var*kr2;
			Vec kv3 = a(m, r, j, N);

			Vec kr4 = v[j] + h_var*kv3;
			r[j] = r[j] + h_var*kr3;
			Vec kv4 = a(m, r, j, N);

			// bereken r_n+1 en v_n+1 en onthoud deze woorden voor volgende iteraties
			r[j] = r[j] + (h_var / 6) * (kr1 + 2 * kr2 + 2 * kr3 + kr4);
			v[j] = v[j] + (h_var / 6) * (kv1 + 2 * kv2 + 2 * kv3 + kv4);


			outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';


		}
		outfile1 << std::endl;



		outfile2 << Energie(r, v, m) << std::endl;
		outfile3 << error_energie(r, v, m, start_energie) << std::endl;
	}

	std::cout << "Posities werden bijgehouden in bestand RK4.txt" << std::endl;
	std::cout << "Energie werd bijgehouden in bestand RK4_E.txt" << std::endl;
	std::cout << "Relatieve energiefouten werden bijgehouden in bestand RK4_E_err.txt" << std::endl;
	outfile2.close();


}