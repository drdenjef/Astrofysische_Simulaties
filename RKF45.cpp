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
*  Runge-Kutta-Fehlberg Method (RKF45)   *
*										 *
*****************************************/



void RKF45(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam) {

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

		std::vector<Vec> kr1;
		std::vector<Vec> kv1;
		std::vector<Vec> kr2;
		std::vector<Vec> kv2;
		std::vector<Vec> kr3;
		std::vector<Vec> kv3;
		std::vector<Vec> kr4;
		std::vector<Vec> kv4;
		std::vector<Vec> kr5;
		std::vector<Vec> kv5;
		std::vector<Vec> kr6;
		std::vector<Vec> kv6;

		for (int j = 0; j < N; j++) {
			kr1.push_back(v[j]);
			kv1.push_back(a(m, r, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr2.push_back(v[j] + .25*h_var*kv1[j]);
			kv2.push_back(a(m, r + .25*h_var*kr1, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr3.push_back(v[j] + (3 / 8)*h_var*kv2[j]);
			kv3.push_back(a(m, r + (3 / 8)*h_var*kr2, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr4.push_back(v[j] + (12 / 13)*h_var*kv3[j]);
			kv4.push_back(a(m, r + (12 / 13)*h_var*kr3, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr5.push_back(v[j] + h_var * kv4[j]);
			kv5.push_back(a(m, r + h_var * kr4, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr6.push_back(v[j] + .5*h_var*kv5[j]);
			kv6.push_back(a(m, r + .5*h_var*kr5, j, N));
		}

		// bereken r_n+1 en v_n+1 en onthoud deze woorden voor volgende iteraties
		r = r + h_var * ((25 / 216)*kr1 + (1408 / 2565)*kr3 + (2197 / 4104)*kr4 - .2*kr5);
		v = v + h_var * ((25 / 216)*kv1 + (1408 / 2565)*kv3 + (2197 / 4104)*kv4 - .2*kv5);

		for (int j = 0; j < N; j++) {
			outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
		}
		outfile1 << std::endl;
		outfile2 << Energie(r, v, m) << std::endl;
		outfile3 << error_energie(r, v, m, start_energie) << std::endl;
	}

	std::cout << "Posities werden bijgehouden in bestand " << naam << ".txt" << std::endl;
	std::cout << "Energie werd bijgehouden in bestand " << naam << ".txt" << std::endl;
	std::cout << "Relatieve energiefouten werden bijgehouden in bestand " << naam << ".txt" << std::endl;
	outfile1.close();
	outfile2.close();
	outfile3.close();

	
}


