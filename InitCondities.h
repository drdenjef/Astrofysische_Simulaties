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

//functie voor teruggeven alle massas
std::vector<float> massas(int aantal_deeltjes, int beginconditie);

#endif