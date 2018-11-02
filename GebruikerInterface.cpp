#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>


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

int type_integratie() {
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
		return type_integratie();
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias of size_t
	int nummer_methode = std::stoi(methode, &sz);

	//kijkt of de methode bestaat
	bool is_methode = nummer_methode == 1 || nummer_methode == 2 || nummer_methode == 3 || nummer_methode == 4;
	if (!is_methode) {
		cout << "Error, geen geldige input" << endl;
		return type_integratie();
	}

	//return nummer van methode
	return nummer_methode;

}

bool aanwezige_begincondities() {

	//vraagt input op en leest in
	cout << "Wilt u voorgeselecteerde begincondities gebruiken? J (Ja) of N (Neen): ";
	string JaNee = lees_input();

	//kijkt of de mogelijke antwoorden in de string zitten
	bool J_N = JaNee.find('J') || JaNee.find('N');

	//controleert ook extra op het wel 1 character is
	if (!J_N || JaNee.length() != 1) {
		cout << "Error, geen geldige input" << endl;
		return aanwezige_begincondities();
	}

	//als alles goed, maak de return waarden aan
	if (JaNee == "J") {
		return 1;
	}
	else {
		return 0;
	}

}
	