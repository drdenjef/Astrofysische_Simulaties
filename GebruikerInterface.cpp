#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>
#include <map> 


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
	