#ifndef GEBRUIKERINTERFACE_H
#define GEBRUIKERINTERFACE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

std::string lees_input();

bool input_is_integer(const std::string &s);

int aantal_objecten();

float tijdstap_opvraag();

int type_integratie_cijfer();

std::string type_integratie_naam(int i);

bool aanwezige_begincondities();

#endif









