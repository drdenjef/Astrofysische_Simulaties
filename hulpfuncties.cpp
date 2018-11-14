#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"

using namespace std;

double variabele_h(double h, vector<Vec> posities) {
	//algemeen, ipv allemaal afstanden te berekene, eerst x coord bekijken, als de afstand tussen die 2 bvb al groter is dan 1. dan al te veel
	//zo normaal gezien computationele tijd inkorten
	double variabele_h_weger = 1;
	//overloop alle vectoren
	for (int i = 0; i < posities.size(); i++) {

		//overloop alle vectoren die na de eerste vector komt
		for (int j = (posities.size() - 1); j > i; j--) {

			//bekijk x afstand 
			double x_afst_kwadr = pow(posities[i].x() - posities[j].x(), 2);
			//moeten geen wortel nemen, is extra berekening en als het nu al groter of gelijk is aan 1, gaat wortel niks wijzigen
			if (x_afst_kwadr >= 1) {
				break;
			}

			double y_afst_kwadr = pow(posities[i].y() - posities[j].y(), 2);

			//weer zelfde opmerking over wortel
			if ((x_afst_kwadr + y_afst_kwadr) >= 1) {
				break;
			}

			double z_afst_kwadr = pow(posities[i].z() - posities[j].z(), 2);

			//zelfde uitleg voor waarom hier geen wortel
			if ((x_afst_kwadr + y_afst_kwadr + z_afst_kwadr) >= 1) {
				break;
			}

			//aanmaken mogelijke h(want moet anders 2 keer berekenen)
			//controleren of het kleiner is dan de huidige verkorte h
			double mogelijke_h_weger = sqrt(x_afst_kwadr + y_afst_kwadr + z_afst_kwadr);
			if (mogelijke_h_weger < variabele_h_weger) {
				variabele_h_weger = mogelijke_h_weger;
			}
		}
	}
	//return dus de echte h maal de wegingsfactor, voor zo kleinere h
	return (variabele_h_weger * h);
}

Vec a(std::vector<double> m, std::vector<Vec> r, int i, int N) {

	Vec a;

	for (int j = 0; j < N; j++) {
		if (j != i) {
			a += m[j] * (r[i] - r[j]) / (r[i] - r[j]).norm3();
		}

	}
	return -1.*a;
}

double Energie(vector<Vec> poslist, vector<Vec> velolist, vector<double> masslist) {
	const int z = poslist.size();
	double energie_tot = 0;
	for (int i = 0; i != z; i += 1) {
		energie_tot += 0.5*masslist[i] * velolist[i].norm2();
		for (int j = 0; j != z; j += 1) {
			if (i != j) {
				Vec x = poslist[i] - poslist[j];
				energie_tot -= 0.5* masslist[i] * masslist[j] / x.norm();
			};
		};
	};
	return energie_tot;
}

double error_energie(std::vector<Vec> poslist, std::vector<Vec> velolist, std::vector<double> masslist, double start_energie) {
	//vraag huidige totale energie op
	double huidige_energie = Energie(poslist, velolist, masslist);

	//bereken de fout
	double error_energie = abs((start_energie - huidige_energie) / start_energie);

	//geef ze terug
	return error_energie;

}