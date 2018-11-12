#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "3DVectClass.h"
#include "hulpfuncties.h"

/*****************************************
*										 *
*  Runge-Kutta-Fehlberg Method (RKF45)   *
*										 *
*****************************************/

//
// we gaan ervan uit dat we een tijdsstap h gegeven hebben en beginposities en - snelheden
// in de vorm van een Vec object
//


// functie RKF45 die posities van deeltjes teruggeeft
std::vector<std::vector<Vec>> RKF45(std::vector<double> m, std::vector<Vec> r, std::vector<Vec> v, int N, int iteraties, double h) {

	// maak een lijst aan waaraan de lijsten komen die de posities bevatten van de deeltjes voor elke iteratie
	// de lengte van deze lijst komt overeen met het aantal iteraties
	// deze lijst zal uiteindelijk teruggegeven worden
	std::vector<std::vector<Vec>> posities;
	//voeg de beginposities al toe
	posities.push_back(r);

	// begint te itereren over het aantal iteraties die je wilt uitvoeren
	// kan meegegeven worden aan de functie RKF45
	for (int i = 0; i <= iteraties; i++) {

		// maak een lijst aan waaraan voor elke iteratie de positie van de deeltjes wordt meegegeven
		// de lengte van deze lijst komt overeen met het aantal deeltjes
		std::vector<Vec> posities_per_deeltje;

		// begint te itereren over alle deeltjes
		for (int j = 0; j < N; j++) {

			//voor elk deeltje, maak alle nodige k's aan

			Vec kr1 = v[j];
			//r[j] = r[j]
			Vec kv1 = a(m, r, j, N);

			Vec kr2 = v[j] + .25*h*kv1;
			r[j] = r[j] + .25*h*kr1;
			Vec kv2 = a(m, r, j, N);

			Vec kr3 = v[j] + (3 / 8)*h*kv2;
			r[j] = r[j] + (3 / 8)*h*kr2;
			Vec kv3 = a(m, r, j, N);

			Vec kr4 = v[j] + (12 / 13)*h*kv3;
			r[j] = r[j] + (12 / 13)*h*kr3;
			Vec kv4 = a(m, r, j, N);

			Vec kr5 = v[j] + h * kv4;
			r[j] = r[j] + h * kr4;
			Vec kv5 = a(m, r, j, N);

			Vec kr6 = v[j] + .5*h*kv5;
			r[j] = r[j] + .5*h*kr5;
			Vec kv6 = a(m, r, j, N);

			// bereken r_n+1 en v_n+1 en onthoud deze woorden voor volgende iteraties
			r[j] = r[j] + h * ((25 / 216)*kr1 + (1408 / 2565)*kr3 + (2197 / 4101)*kr4 - .2*kr5);
			v[j] = v[j] + h * ((25 / 216)*kv1 + (1408 / 2565)*kv3 + (2197 / 4101)*kv4 - .2*kv5);


			// voeg de positie van het deeltje toe aan de lijst
			posities_per_deeltje.push_back(r[j]);
		}

		// voeg de lijst van de posities van de deeltjes toe aan de lijst waarin alle posities worden bijgehouden
		posities.push_back(posities_per_deeltje);
	
	}

	// geef de totale lijst met alle posities terug
	return posities;
}


