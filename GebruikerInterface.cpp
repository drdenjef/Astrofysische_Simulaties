#include <iostream>
#include <string>
#include <cmath>
#include <map> 
#include <vector>
#include "RKF45.H"
#include "Forest-Ruth.h"
#include "RK4.h"
#include "Verlet.h"
#include "PEFRL.h"
#include "Leapfrog.h"

using namespace std;

std::string lees_input() {

	string input;
	//vraagt input op en leest in
	getline(cin, input);
	return input;
}

bool input_is_integer(const string &s) {

	//variabele die false is wanneer er non-integer char gevonden is
	int integer = 1;

	//extra check als input een lege string is
	if (s.length() == 0) {
		return integer = 0;
	}

	//check char per char of input van de vorm integer is
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isdigit(s[i]))
		{
			integer = 0;
			break;
		}
	}

	//geef bool terug
	return integer;
}

bool input_is_double(std::string input, int nietneg) {
	//controleren of dit effectief een double is, dus allemaal digits en 1 punt
	//variabele die false is wanneer er non-integer char gevonden is
	int integer = 1;
	//houdt aantal punten bij
	int punten = 0;
	//houdt aantal mintekens bij
	int minteken = 0;

	//extra check als input een lege string is of als h = 0 opgegeven was
	if (input.length() == 0) {
		return 0;
	}

	//check char per char of input van de vorm double is
	for (size_t i = 0; i < input.length(); i++)
	{
		//extra variabele, zodat else if niet getriggered wordt op punt
		int punt_gezien = 0;
		if (input[i] == '.') {
			punt_gezien = 1;
			punten += 1;
		}
		if (input[i] == '-' && !nietneg) {
			minteken += 1;
		}
		else if (!isdigit(input[i]) and !punt_gezien)
		{
			integer = 0;
			break;
		}
		//er mag ook niet meer dan 1 punt zijn
		if (punten > 1) {
			integer = 0;
			break;
		}
		//er mag ook niet meer dan 1 minteken zijn
		if (minteken > 1) {
			integer = 0;
			break;
		}
	}
	return integer;
}

int input_is_janee(const std::string &JaNee) {

	//mogelijke antwoorden (rekening gehouden met dat users soms lastig kunnen doen en niet helemaal correct inputten)
	if (JaNee == "J" || JaNee == "j" || JaNee == "Ja" || JaNee == "ja" || JaNee == "JA ") {
		return 1;
	}
	else if (JaNee == "N" || JaNee == "n" || JaNee == "nee" || JaNee == "neen" || JaNee == "Neen" || JaNee == "Nee" || JaNee == "NEE" || JaNee == "NEEN") {
		return 0;
	}
	else
		return 2;
}


int aantal_objecten() {

	//vraagt input op en leest in
	cout << "Geef aantal gewenste deeltjes op: ";
	string aantal_input = lees_input();

	//check als input van de vorm integer is
	int integer = input_is_integer(aantal_input);

	//herbegin functie wanneer integer check gefaald is
	if (!integer) {
		cout << "Error, dit is geen nietnegatief geheel getal" << endl;
		return aantal_objecten();
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias van size_t
	int aantal = std::stoi(aantal_input, &sz);

	//controleer op triviale aantallen van deeltjes
	if (aantal <= 1) {
		cout << "Dit aantal is te triviaal, gelieve een ander te kiezen." << endl;
		return aantal_objecten();
	}
	
	//geef aantal deeltjes terug
	return aantal;
}

double tijdstap_opvraag() {
	//vraagt input op en leest in
	cout << "Voer gewenste tijdstap in: ";
	string input = lees_input();

	//check of input van vorm double is
	bool doubl = input_is_double(input, 1);

	//kijkt dus of de functie succesvol was
	if (!doubl) {
		cout << "Geen positieve double, probeer opnieuw." << endl;
		return tijdstap_opvraag();
	}

	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double h = std::stof(input, &sz);

	//extra check op 0.00 bvb (in input_is_double checken is onnodig langer maken, zo is sneller)
	if (!h) {
		cout << "Geen nietnegatieve double, probeer opnieuw." << endl;
		return tijdstap_opvraag();
	}

	//geef double terug
	return h;	
}

bool gebruik_var_h() {

	//vraagt input op en leest in
	cout << "Wilt u een variabele tijdstap gebruiken? J (Ja) of N (Neen). Opgelet, bij gebruik hiervan is simpliciteit niet te garanderen: ";
	string JaNee = lees_input();

	//check of correcte vorm, returnwaarde geeft de info (1 is ja, 0 is neen, 2 is compleet foute input)
	int janee = input_is_janee(JaNee);

	//als de input echt compleet er naast zat, error en opnieuw
	if (janee == 2) {
		cout << "Error, geen geldige input" << endl;
		return gebruik_var_h();
	}
	else
		return janee;
}

double tijd_opvraag(double h) {
	//vraagt input op en leest in
	cout << "Voer gewenste integratietijd in: ";
	string input = lees_input();

	//check of input van vorm double is
	bool doubl = input_is_double(input, 1);

	//kijkt dus of de functie succesvol was
	if (!doubl) {
		cout << "Geen positieve double, probeer opnieuw." << endl;
		return tijd_opvraag(h);
	}

	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double tijd = std::stof(input, &sz);

	//extra check op 0.00 bvb, (in input_is_double checken is onnodig langer maken, zo is sneller)
	if (!tijd) {
		cout << "Geen positieve double, probeer opnieuw." << endl;
		return tijd_opvraag(h);
	}

	//integratietijd mag ook niet kleiner zijn dan de tijdstap
	if (tijd < h) {
		cout << "integratietijd mag niet kleiner zijn dan tijdstap, probeer opnieuw." << endl;
		return tijd_opvraag(h);
	}

	return tijd;
}

int fractie_opvraag(double integratietijd, double h) {
	//vraagt input op en leest in
	cout << "Na hoeveel integraties wilt u telkens de posities wegschrijven? Dit is handig wanneer u heel lang en/of precies wilt integreren.";
	string aantal_input = lees_input();

	//check als input van de vorm integer is
	int fractie = input_is_integer(aantal_input);

	//herbegin functie wanneer integer check gefaald is
	if (!fractie) {
		cout << "Error, dit is geen positief geheel getal" << endl;
		return fractie_opvraag( integratietijd,  h);
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias of size_t
	int aantal = std::stoi(aantal_input, &sz);

	//controleer of groter dan 0 is
	if (aantal == 0) {
		cout << "Error, dit is geen positief geheel getal" << endl;
		return fractie_opvraag( integratietijd,  h);
	}

	double stappen = ceil(integratietijd / h);
	//controleer of er uberhaupt wel iets weggeschreven kan worden
	if ((double)aantal> stappen) {
		cout << "Error, op deze manier gaat u helemaal niks wegschrijven" << endl;
		return fractie_opvraag( integratietijd,  h);
	}

	//geef aantal deeltjes terug
	return aantal;

}

int type_integratie_cijfer() {
	//vraagt input op en leest in
	cout << "Voer type integratie in " << endl;
	cout << "Typ 1 voor RK4" << endl;
	cout << "Typ 2 voor RKF45" << endl;
	cout << "Typ 3 voor Verlet" << endl;
	cout << "Typ 4 voor Forest-Ruth" << endl;
	cout << "Typ 5 voor Leapfrog" << endl;
	cout << "Typ 6 voor PEFRL" << endl;
	cout << "Typ 7 voor alle methodes" << endl;
	string methode = lees_input();

	//kijkt of input een integer is
	bool is_int = input_is_integer(methode);

	//indien integer check faalt, opnieuw opvragen
	if (!is_int) {
		cout << "Error, geen geldige input" << endl;
		return type_integratie_cijfer();
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias of size_t
	int nummer_methode = std::stoi(methode, &sz);

	//kijkt of de methode bestaat
	bool is_methode = nummer_methode > 0 && nummer_methode <= 7;
	if (!is_methode) {
		cout << "Error, geen geldige input" << endl;
		return type_integratie_cijfer();
	}

	//return nummer van methode
	return nummer_methode;

}

std::string type_integratie_naam(int i) {

	//mapje die methodecijfer koppelt met naam
	map <int, string> integrators;
	integrators[1] = "RK4.";
	integrators[2] = "RKF45.";
	integrators[3] = "Verlet.";
	integrators[4] = "Forest-Ruth.";
	integrators[5] = "Leapfrog.";
	integrators[6] = "PEFRL.";
	integrators[7] = "Alles.";

	return integrators[i];

}

bool aanwezige_begincondities() {

	//vraagt input op en leest in
	cout << "Wilt u voorgeselecteerde begincondities gebruiken? J (Ja) of N (Neen): ";
	string JaNee = lees_input();

	//check of correcte vorm, returnwaarde geeft de info (1 is ja, 0 is neen, 2 is compleet foute input)
	int janee = input_is_janee(JaNee);

	//als de input echt compleet er naast zat, error en opnieuw
	if (janee == 2) {
		cout << "Error, geen geldige input" << endl;
		return gebruik_var_h();
	}
	else
		return janee;

}

bool random_genereren() {
	//vraagt input op en leest in
	cout << "Wilt u random (gecentreerde en herschaalde) toestand genereren (anders moet u er zelf invoeren)? J (Ja) of N (Neen): ";
	string JaNee = lees_input();

	//check of correcte vorm, returnwaarde geeft de info (1 is ja, 0 is neen, 2 is compleet foute input)
	int janee = input_is_janee(JaNee);

	//als de input echt compleet er naast zat, error en opnieuw
	if (janee == 2) {
		cout << "Error, geen geldige input" << endl;
		return gebruik_var_h();
	}
	else
		return janee;
}

void alle_posities(vector<double> m, vector<Vec>r, vector<Vec> v, int N, double integratietijd, double h, int methode, string naam, bool gebruiken_var_h, int fractie) {

	//roept integrator en wegschrijven data via RK4 op
	if (methode == 1) {
		RK4(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

	//roept integrator en wegschrijven data via RKF45 op
	if (methode == 2) {
		RKF45(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

	//roept integrator en wegschrijven data via Verlet op
	if (methode == 3) {
		Verlet(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

	//roept integrator en wegschrijven data via Forest-Ruth op
	if (methode == 4) {
		ForestRuth(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

	//roept integrator en wegschrijven data via Leapfrog op
	if (methode == 5) {
		Leapfrog(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

	//roept integrator en wegschrijven data via PEFRL op
	if (methode == 6) {
		PEFRL(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

	//roept integrator en wegschrijven data via alle methodes op
	if (methode == 7) {
		RK4(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
		RKF45(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
		Verlet(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
		ForestRuth(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
		Leapfrog(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
		PEFRL(m, r, v, N, integratietijd, h, naam, gebruiken_var_h, fractie);
	}

}
	