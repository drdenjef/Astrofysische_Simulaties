#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
#include "hulpfuncties.h"
using namespace std;


void Verlet(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h, std::string naam) {

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

	for (int j = 0; j < iteraties; j++) {
		for (int i = 0; i < N; i++) {
			v[i] = v[i] + 0.5 * h * a(m, r, i, N);
			r[i] = r[i] + h * v[i];
			v[i] = v[i] + 0.5 * h * a(m, r, i, N);

			//wegschrijven naar file
			outfile1 << r[i].x() << ' ' << r[i].y() << ' ' << r[i].z() << '\t';
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

