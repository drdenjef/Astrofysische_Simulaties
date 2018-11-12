#ifndef GEBRUIKERINTERFACE_H
#define GEBRUIKERINTERFACE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "3DVectClass.h"

std::string lees_input();

bool input_is_integer(const std::string &s);

int aantal_objecten();

double tijdstap_opvraag();

int iteraties_opvraag();

int type_integratie_cijfer();

std::string type_integratie_naam(int i);

bool aanwezige_begincondities();

std::vector<std::vector<Vec>> alle_posities(std::vector<double> m, std::vector<Vec>r, std::vector<Vec> v, int N, int iter, double h, int methode);

#endif









