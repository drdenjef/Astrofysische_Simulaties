#ifndef INITCONDITIES_H
#define INITCONDITIES_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"

//functie om te kijken of iets van de vorm double is, extra variabele als iets niet neg mag zijn
bool is_double(std::string input, int nietneg);

//functie voor lijst met namen van de begincondities
std::vector<std::map<int, std::string>> lijst_begincond_namen();

//functie voor lijst met de namen van tekstbestanden van begincondities
std::vector<std::vector<std::vector<std::string>>> lijst_begincond();

//functie voor teruggeven nummer van gekozen beginconditie
int nummer_beginconditie(int aantal);

//functie voor teruggeven alle startposities
std::vector<Vec> posities(int aantal_deeltjes, int beginconditie);

//functie voor teruggeven alle startsnelheden
std::vector<Vec> snelheden(int aantal_deeltjes, int beginconditie);

//functie voor teruggeven alle massas, al genormeerd
std::vector<double> massas(int aantal_deeltjes, int beginconditie);

//functie voor opvragen x positie/snelheid
double x_pos_snel(int deeltje, bool positie);

//functie voor opvragen y positie/snelheid
double y_pos_snel(int deeltje, bool positie);

//functie voor opvragen z positie/snelheid
double z_pos_snel(int deeltje, bool positie);

//functie voor opvragen massa
double opvraag_massa(int deeltje);

//functie voor opvragen alle startposities
std::vector<Vec> vraag_posities(int aantal_deeltjes);

//functie voor opvragen alle startsnelheden
std::vector<Vec> vraag_snelheden(int aantal_deeltjes);

//functie voor opvragen alle massas, al genormeerd
std::vector<double> vraag_massas(int aantal_deeltjes);

//schrijft posities naar scherm
void print_posities(std::vector<Vec> begin_posities);

//schrijft snelheden naar scherm
void print_snelheden(std::vector<Vec> begin_snelheden);

//schrijft massas naar scherm
void print_massas(std::vector<double> begin_massas);

#endif