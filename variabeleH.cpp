#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
using namespace std;

float variabele_h(float h, vector<Vec> posities) {
	//algemeen, ipv allemaal afstanden te berekene, eerst x coord bekijken, als de afstand tussen die 2 bvb al groter is dan 1. dan al te veel
	//zo normaal gezien computationele tijd inkorten
	float variabele_h_weger = 1;
	//overloop alle vectoren
	for (int i = 0; i < posities.size(); i++) {

		//overloop alle vectoren die na de eerste vector komt
		for (int j = (posities.size() -1); j >i; j--) {

			//bekijk x afstand 
			float x_afst_kwadr = abs(posities[i].x()*posities[i].x() - posities[j].x()*posities[j].x());
			//moeten geen wortel nemen, is extra berekening en als het nu al groter of gelijk is aan 1, gaat wortel niks wijzigen
			if (x_afst_kwadr >= 1) {
				break;
			}

			float y_afst_kwadr = abs(posities[i].y()*posities[i].y() - posities[j].y()*posities[j].y());

			//weer zelfde opmerking over wortel
			if ((x_afst_kwadr + y_afst_kwadr) >= 1) {
				break;
			}

			float z_afst_kwadr = abs(posities[i].z()*posities[i].z() - posities[j].z()*posities[j].z());

			//zelfde uitleg voor waarom hier geen wortel
			if (( x_afst_kwadr+ y_afst_kwadr + z_afst_kwadr) >= 1) {
				break;
			}

			//aanmaken mogelijke h(want moet anders 2 keer berekenen)
			//controleren of het kleiner is dan de huidige verkorte h
			float mogelijke_h_weger = sqrt(x_afst_kwadr+ y_afst_kwadr + z_afst_kwadr);
			if ( mogelijke_h_weger < variabele_h_weger) {
				variabele_h_weger = mogelijke_h_weger;
			}
		}
	}
	//return dus de echte h maal de wegingsfactor, voor zo kleinere h
	return (variabele_h_weger * h);
}