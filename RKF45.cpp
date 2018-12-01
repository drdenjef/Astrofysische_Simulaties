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


/*****************************************
*										 *
*  Runge-Kutta-Fehlberg Method (RKF45)   *
*										 *
*****************************************/



void RKF45(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam) {

	// maak een file aan waar de posities van de deeltjes wordt bijgehouden
	std::ofstream outfile1(naam + "_RKF45.txt");
	outfile1 << std::setprecision(15);

	// beginposities meegeven
	for (int j = 0; j < N; j++) {
		outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
	}
	outfile1 << std::endl;

	// maak een file aan waar de energieën worden bijgehouden
	std::ofstream outfile2(naam + "_RKF45_E.txt");
	outfile2 << std::setprecision(15);

	// maak een file aan waar de relatieve fouten van de energieën worden bijgehouden
	std::ofstream outfile3(naam + "_RKF45_E_err.txt");
	outfile3 << std::setprecision(15);

	// hou de startenergie van het systeem bij
	double start_energie = Energie(r, v, m);

	std::vector<double> tijd_iteratie;

	// constanten definieren

	double a21 = .25;

	double a31 = 3. / 32.;
	double a32 = 9. / 32.;

	double a41 = 1932. / 2197.;
	double a42 = -7200. / 2197.;
	double a43 = 7296. / 2197.;

	double a51 = 439. / 216.;
	double a52 = -8.;
	double a53 = 3680. / 513.;
	double a54 = -845. / 4104.;

	double a61 = -8. / 27.;
	double a62 = 2.;
	double a63 = -3544. / 2565.;
	double a64 = 1859. / 4104.;
	double a65 = -11. / 40.;

	double b1 = 25. / 216.;
	double b3 = 1408. / 2565.;
	double b4 = 2197. / 4104.;
	double b5 = -0.2;

	// begint te itereren over het aantal iteraties die je wilt uitvoeren
	// kan meegegeven worden aan de functie RKF45
	for (int i = 0; i < iteraties; i++) {

		double h_var = variabele_h(h, r);

		clock_t sstart = clock();

		std::vector<Vec> kr1;
		std::vector<Vec> kr2;
		std::vector<Vec> kr3;
		std::vector<Vec> kr4;
		std::vector<Vec> kr5;
		std::vector<Vec> kr6;

		std::vector<Vec> kv1;
		std::vector<Vec> kv2;
		std::vector<Vec> kv3;
		std::vector<Vec> kv4;
		std::vector<Vec> kv5;
		std::vector<Vec> kv6;

		for (int j = 0; j < N; j++) {
			kr1.push_back(h_var*v[j]);
			kv1.push_back(h_var*a(m, r, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr2.push_back(h_var*(v[j] + .25*kv1[j]));
			kv2.push_back(h_var*a(m, r + a21*kr1, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr3.push_back(h_var*(v[j] + a31*kv1[j] + a32*kv2[j]));
			kv3.push_back(h_var*a(m, r + a31*kr1 + a32*kr2, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr4.push_back(h_var*(v[j] + a41*kv1[j] + a42*kv2[j] + a43*kv3[j]));
			kv4.push_back(h_var*a(m, r + a41*kr1 + a42*kr2 + a43*kr3, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr5.push_back(h_var*(v[j] + a51*kv1[j] + a52*kv2[j] + a53*kv3[j] + a54*kv4[j]));
			kv5.push_back(h_var*a(m, r + a51*kr1 + a52*kr2 + a53*kr3 + a54*kr4, j, N));
		}

		for (int j = 0; j < N; j++) {
			kr6.push_back(h_var*(v[j] + a61*kv1[j] + a62*kv2[j] + a63*kv3[j] + a64*kv4[j] + a65*kv5[j]));
			kv6.push_back(h_var*a(m, r + a61*kr1 + a62*kr2 + a63*kr3 + a64*kr4 + a65*kr5, j, N));
		}

		// bereken r_n+1 en v_n+1 en onthoud deze woorden voor volgende iteraties
		r = r +  b1*kr1 + b3*kr3 + b4*kr4 - b5*kr5 ;
		v = v +  b1*kv1 + b3*kv3 + b4*kv4 - b5*kv5 ;

		tijd_iteratie.push_back((clock() - sstart) / (CLOCKS_PER_SEC / 1000));


		for (int j = 0; j < N; j++) {
			outfile1 << r[j].x() << ' ' << r[j].y() << ' ' << r[j].z() << '\t';
		}

		outfile1 << std::endl;
		outfile2 << Energie(r, v, m) << std::endl;
		outfile3 << error_energie(r, v, m, start_energie) << '\t' << dichtste_afstand(r) << std::endl;
	}

	std::cout << "Posities werden bijgehouden in bestand " << naam << "_RKF45.txt" << std::endl;
	std::cout << "Energie werd bijgehouden in bestand " << naam << "_RKF45_E.txt" << std::endl;
	std::cout << "Relatieve energiefouten en dichtste afstanden werden bijgehouden in bestand " << naam << "_RKF45_E_err.txt" << std::endl;
	outfile1.close();
	outfile2.close();
	outfile3.close();	

	double tijd_gemiddelde;
	tijd_gemiddelde = accumulate(tijd_iteratie.begin(), tijd_iteratie.end(), 0.0) / tijd_iteratie.size();

	std::cout << tijd_gemiddelde << ' ' << "milliseconden per iteratie" << std::endl;
}