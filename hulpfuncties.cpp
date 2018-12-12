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
	
	//alleen variabele h gebruiken als dichtste nadering kleiner is dan 1, deze afstand is dan ook hetgene waarmee men h vermenigvuldigt
	double variabele_h_weger = 1;
	//overloop alle vectoren
	for (unsigned int i = 0; i < posities.size() - 1; i++) {
		//overloop alle vectoren die na de eerste vector komt
		for (unsigned int j = (posities.size() - 1); j > i; j--) {
			//bereken afstand, en kijk of deze kleiner is dan de huidige weger
			double afstand = (posities[i] - posities[j]).norm();
			if (variabele_h_weger > afstand) {
				variabele_h_weger = afstand;
			}
		}
	}
	double nieuwe_h = variabele_h_weger * h;
	return nieuwe_h;
}

Vec a(std::vector<double> m, std::vector<Vec> r, int i, int N) {

	Vec a;

	//overloop alle deeltjes, indien anders dan deeltje i, bereken de versnelling
	for (int j = 0; j < N; j++) {
		if (j != i) {
			a += m[j] * (r[i] - r[j]) / (r[i] - r[j]).norm3();
		}

	}
	return -1.*a;
}

double Energie(vector<Vec> poslist, vector<Vec> velolist, vector<double> masslist) {

	//maak totale energie op, momenteel nog niks berekend dus nul
	double energie_tot = 0;

	//overloop alle deeltjes
	for (unsigned int i = 0; i < poslist.size(); i ++) {
		//kinetische energie
		energie_tot += 0.5*masslist[i] * velolist[i].norm2();
		//potentiele energie
		for (unsigned int j = 0; j < poslist.size(); j ++) {
			if (i != j) {
				Vec x = poslist[i] - poslist[j];
				energie_tot -= 0.5* masslist[i] * masslist[j] / x.norm();
			}
		}
	}
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

double afstand(Vec a, Vec b) {
	return sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2) + pow(a.z() - b.z(), 2));
}

// functie die toelaat de dichtste afstand tussen alle deeltjes
double dichtste_afstand(std::vector<Vec> poslist) {

	double dichtste_nadering;
	
	if (poslist.size() == 2) {
		return afstand(poslist[0], poslist[1]);
	}
	else {
		//neem absurd groot getal dat zeker niet kleiner dan de echtste dichtste nadering gaat zijn
		dichtste_nadering = 1e15;
		//overloop alle vectoren
		for (unsigned int i = 0; i < poslist.size() - 1; i++) {
			//overloop alle vectoren die na de eerste vector komt
			for (unsigned int j = (poslist.size() - 1); j > i; j--) {
				//als deze afstand kleiner is dan de vorige kleinste afstand, pas deze dan aan
				double check_afstand = afstand(poslist[i], poslist[j]);
				if (check_afstand < dichtste_nadering) {
					dichtste_nadering = check_afstand;
				}
			}
		}
		return dichtste_nadering;
	}
}