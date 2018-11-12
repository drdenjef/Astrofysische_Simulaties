#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>
#include <map> 
#include <vector>
#include "3DVectClass.h"
#include "Embedded_RK.h"



using namespace std;

std::string lees_input() {

	//vraagt input op en leest in
	string input;
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
	std::string::size_type sz;   // alias of size_t
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

	//controleren of dit effectief een double is, dus allemaal digits en 1 punt
	//variabele die false is wanneer er non-integer char gevonden is
	int integer = 1;
	//houdt aantal punten bij
	int punten = 0;

	//extra check als input een lege string is of als h = 0 opgegeven was
	if (input.length() == 0 || input =="0") {
		cout << "Geen nietnegatieve double, probeer opnieuw." << endl;
		return tijdstap_opvraag();
	}

	//check char per char of input van de vorm double is
	for (size_t i = 0; i < input.length(); i++)
	{
		
		if (input[i] == '.') {
			punten += 1;
		}
		else if (!isdigit(input[i]))
		{
			integer = 0;
			break;
		}
		//er mag ook niet meer dan 1 punt zijn
		if (punten > 1) {
			integer = 0;
			break;
		}
	}

	//kijkt dus of de functie succesvol was
	if (!integer) {
		cout << "Geen nietnegatieve double, probeer opnieuw." << endl;
		return tijdstap_opvraag();
	}

	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double h = std::stof(input, &sz);

	//geef double terug
	return h;	
}

int iteraties_opvraag() {
	//vraagt input op en leest in
	cout << "Voer gewenste aantal iteraties in: ";
	string input = lees_input();

	//check als input van de vorm integer is
	int integer = input_is_integer(input);

	//herbegin functie wanneer integer check gefaald is
	if (!integer) {
		cout << "Error, dit is geen nietnegatief geheel getal" << endl;
		return iteraties_opvraag();
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias of size_t
	int aantal = std::stoi(input, &sz);

	return aantal;
}

int type_integratie_cijfer() {
	//vraagt input op en leest in
	cout << "Voer type integratie in " << endl;
	cout << "Typ 1 voor RK4" << endl;
	cout << "Typ 2 voor ingebedde RK" << endl;
	cout << "Typ 3 voor Verlet" << endl;
	cout << "Typ 4 voor Forest-Ruth" << endl;
	string methode = lees_input();

	//kijkt of input een integer is
	bool is_int = input_is_integer(methode);

	if (!is_int) {
		cout << "Error, geen geldige input" << endl;
		return type_integratie_cijfer();
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias of size_t
	int nummer_methode = std::stoi(methode, &sz);

	//kijkt of de methode bestaat
	bool is_methode = nummer_methode == 1 || nummer_methode == 2 || nummer_methode == 3 || nummer_methode == 4;
	if (!is_methode) {
		cout << "Error, geen geldige input" << endl;
		return type_integratie_cijfer();
	}

	//return nummer van methode
	return nummer_methode;

}

std::string type_integratie_naam(int i) {
	map <int, string> integrators;
	integrators[1] = "RK4.";
	integrators[2] = "ingebedde RK.";
	integrators[3] = "Verlet.";
	integrators[4] = "Forest-Ruth.";

	return integrators[i];

}

bool aanwezige_begincondities() {

	//vraagt input op en leest in
	cout << "Wilt u voorgeselecteerde begincondities gebruiken? J (Ja) of N (Neen): ";
	string JaNee = lees_input();

	
	//mogelijke ja antwoorden (rekening gehouden met dat users soms lastig kunnen doen en niet helemaal correct inputten)
	if (JaNee == "J" || JaNee == "j" || JaNee == "Ja" || JaNee == "ja" || JaNee == "JA ") {
		return 1;
	}
	else if(JaNee == "N" || JaNee == "n" || JaNee == "nee" || JaNee == "neen" || JaNee == "Neen" || JaNee == "Nee" || JaNee == "NEE" || JaNee == "NEEN") {
		return 0;
	}
	//als de input echt compleet er naast zat, error en opnieuw
	else {
		cout << "Error, geen geldige input" << endl;
		return aanwezige_begincondities();
	}

}

vector<vector<Vec>> alle_posities(vector<double> m, vector<Vec>r, vector<Vec> v, int N, int iter, double h, int methode) {
	//nu derigeren naar correcte methode
	vector<vector<Vec>> alle_geintegreerde_posities;

	//RK4
	if (methode == 1) {

	}

	//ingebedde RK
	if (methode == 2) {
		alle_geintegreerde_posities = RKF45(m, r, v, N, iter, h);
	}

	//Verlet
	if (methode == 3) {

	}

	//Forest-Ruth
	if (methode == 4) {

	}

	return alle_geintegreerde_posities;
}
	