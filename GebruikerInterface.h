#ifndef GEBRUIKERINTERFACE_H
#define GEBRUIKERINTERFACE_H
#include <string>
#include <vector>
#include "3DVectClass.h"

//functie voor inlezen tekst at runtime
std::string lees_input();

//controleert of een string van de vorm integer is
bool input_is_integer(const std::string &s);

//functie om te kijken of iets van de vorm double is, extra variabele als iets niet neg mag zijn
bool input_is_double(std::string input, int nietneg);

//controleert of iets een geldige ja/nee is
int input_is_janee(const std::string &s);

//vraagt op hoeveel objecten je wilt, en returnt dit
int aantal_objecten();

//vraagt de tijdstap op, en returnt dit
double tijdstap_opvraag();

//vraagt op of men variabele h wilt gebruiken
bool gebruik_var_h();

//vraagt simulatietijd op en returnt dit
double tijd_opvraag(double h);

//vraagt op om de hoeveel integraties men data wilt wegschrijven, en returnt dit
int fractie_opvraag(double integratietijd, double h);

//vraagt op welke integratie gebruiker wilt (als cijfer) en returnt dit
int type_integratie_cijfer();

//geeft de naam van de integratiemethode terug a.d.h.v. zijn/haar/het cijfer
std::string type_integratie_naam(int i);

//vraagt op of gebruiker al gedefinieerde begincondities wilt
bool aanwezige_begincondities();

//vraagt of gebruiker random zaken wilt integreren (anders moet er zelf worden meegegeven at runtime)
bool random_genereren();

//voert de volledige integratie uit, alle berekeningen worden in integratoren weggeschreven
void alle_posities(std::vector<double> m, std::vector<Vec>r, std::vector<Vec> v, int N, double integratietijd, double h, int methode, std::string naam, bool gebruiken_var_h, int fractie);

#endif









