#ifndef INITCONDITIES_H
#define INITCONDITIES_H
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
#include "GebruikerInterface.h"

//functie voor lijst met namen van de begincondities
std::vector<std::map<int, std::string>> lijst_begincond_namen();

//functie voor lijst met de namen van tekstbestanden van begincondities
std::vector<std::vector<std::vector<std::string>>> lijst_begincond();

//functie voor teruggeven nummer van gekozen beginconditie
int nummer_beginconditie(int aantal);

//functie voor teruggeven alle startposities van een zekere beginconditie
std::vector<Vec> posities(int aantal_deeltjes, int beginconditie);

//functie voor teruggeven alle startsnelheden van een zekere beginconditie
std::vector<Vec> snelheden(int aantal_deeltjes, int beginconditie);

//functie voor teruggeven alle massas van een zekere beginconditie
std::vector<double> massas(int aantal_deeltjes, int beginconditie);

//functie voor opvragen x positie/snelheid (at runtime invoeren)
double x_pos_snel(int deeltje, bool positie);

//functie voor opvragen y positie/snelheid (at runtime invoeren)
double y_pos_snel(int deeltje, bool positie);

//functie voor opvragen z positie/snelheid (at runtime invoeren)
double z_pos_snel(int deeltje, bool positie);

//functie voor opvragen massa (at runtime invoeren)
double opvraag_massa(int deeltje);

//functie voor opvragen alle startposities (at runtime invoeren)
std::vector<Vec> vraag_posities(int aantal_deeltjes);

//functie voor opvragen alle startsnelheden (at runtime invoeren)
std::vector<Vec> vraag_snelheden(int aantal_deeltjes);

//functie voor opvragen alle massas, al genormeerd (at runtime invoeren)
std::vector<double> vraag_massas(int aantal_deeltjes);

//schrijft posities naar scherm
void print_posities(std::vector<Vec> begin_posities);

//schrijft snelheden naar scherm
void print_snelheden(std::vector<Vec> begin_snelheden);

//schrijft massas naar scherm
void print_massas(std::vector<double> begin_massas);

#endif