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

// funcite die random nummer genereert tussen max en min waarde
double f_random(double fMin, double fMax);

// functie die voor een gegeven aantal deeltjes random massas genereert
std::vector<double> random_massa(int N, double min_massa, double max_massa);

// functie die voor een gegeven aantal deeltjes random posities genereert
std::vector<Vec> random_positie(int N, double min_positie, double max_positie);

// functie die voor een gegeven aantal deeltjes random snelheden genereert
std::vector<Vec> random_snelheid(int N, int min_snelheid, int max_snelheid);

//schrijft posities naar scherm
void print_posities(std::vector<Vec> begin_posities);

//schrijft snelheden naar scherm
void print_snelheden(std::vector<Vec> begin_snelheden);

//schrijft massas naar scherm
void print_massas(std::vector<double> begin_massas);

#endif