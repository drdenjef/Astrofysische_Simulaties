#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "GebruikerInterface.h"

using namespace std;

std::vector<std::map<int, std::string>> lijst_begincond_namen() {
	//maak een map aan voor elk aantal deeltjes
	std::map<int, std::string> map2;
	std::map<int, std::string> map3;
	std::map<int, std::string> map4;
	std::map<int, std::string> map5;
	std::map<int, std::string> map6;
	std::map<int, std::string> map7;

	//voor elke aantal, definieer wat namen voor initiele begincondities
	map2[1] = "dubbelster";
	map2[2] = "zon_halley_3D";
	map2[3] = "zon_pluto_3D";

	map3[1] = "Burrau's_probleem";
	map3[2] = "Sitnikov_probleem";
	map3[3] = "3_3";

	map4[1] = "Sitnikov_4";
	map4[2] = "klavertje";
	map4[3] = "dubbeldubbelster";

	map5[1] = "klavertje_steel";
	map5[2] = "solar_binnen";
	map5[3] = "lagrange";
	
	map6[1] = "zon+binnen+jupiter";
	map6[2] = "6deeltjes_2";
	map6[3] = "6deeltjes_3";

	map7[1] = "zon+binnen+jupiter+saturnus";
	map7[2] = "7deeltjes_2";
	map7[3] = "7deeltjes_3";

	//voeg deze mappen toe aan een vector voor alle aantal deeltjes
	std::vector<std::map<int, std::string>> lijst_begincondities;
	lijst_begincondities.push_back(map2);
	lijst_begincondities.push_back(map3);
	lijst_begincondities.push_back(map4);
	lijst_begincondities.push_back(map5);
	lijst_begincondities.push_back(map6);
	lijst_begincondities.push_back(map7);

	//return deze vector van maps van namen begincondities
	return lijst_begincondities;
}


std::vector<std::vector<std::vector<std::string>>> lijst_begincond() {

	//aanmaken lijst alle tekstbestandnamen begincondities
	//de "oppervector" toont de dimentie
	//de vector daaronder toont de beginconditie (1 2 of 3)
	//de vector daaronder toont positie, snelheid, massa

	//moeten hiervoor eerst de volledige structuur opbouwen
	std::vector<std::vector<std::vector<std::string>>> bestanden_beginposities;

	//wordt gebruikt om alle namen vol te steken
	string opvulling;
	opvulling = "iets";
	for (int i = 0; i <= 5; i++) {

		vector<vector<string>> opvullingvectoren;
		bestanden_beginposities.push_back(opvullingvectoren);

		for (int j = 0; j <= 2; j++) {

			vector<string> opvullingvector;
			bestanden_beginposities[i].push_back(opvullingvector);

			for (int k = 0; k <= 2; k++) {

				bestanden_beginposities[i][j].push_back(opvulling);

			}
		}
	}

	//nu alle posities zijn aangemaakt, de echte namen erin steken (doe expliciet voor modaliteit namen)
	bestanden_beginposities[0][0][0] = "dubbelster_pos.txt";
	bestanden_beginposities[0][0][1] = "dubbelster_snel.txt";
	bestanden_beginposities[0][0][2] = "dubbelster_mas.txt";

	bestanden_beginposities[0][1][0] = "zon_halley_3D_pos.txt";
	bestanden_beginposities[0][1][1] = "zon_halley_3D_snel.txt";
	bestanden_beginposities[0][1][2] = "zon_halley_3D_mas.txt";

	bestanden_beginposities[0][2][0] = "zon_pluto_3D_pos.txt";
	bestanden_beginposities[0][2][1] = "zon_pluto_3D_snel.txt";
	bestanden_beginposities[0][2][2] = "zon_pluto_3D_mas.txt";

	bestanden_beginposities[1][0][0] = "Burrau's_probleem_pos.txt";
	bestanden_beginposities[1][0][1] = "Burrau's_probleem_snel.txt";
	bestanden_beginposities[1][0][2] = "Burrau's_probleem_mas.txt";

	bestanden_beginposities[1][1][0] = "sitnikov_pos.txt";
	bestanden_beginposities[1][1][1] = "sitnikov_snel.txt";
	bestanden_beginposities[1][1][2] = "sitnikov_mas.txt";

	bestanden_beginposities[1][2][0] = "3_3_pos.txt";
	bestanden_beginposities[1][2][1] = "3_3_snel.txt";
	bestanden_beginposities[1][2][2] = "3_3_mas.txt";

	bestanden_beginposities[2][0][0] = "sitnikov_4_pos.txt";
	bestanden_beginposities[2][0][1] = "sitnikov_4_snel.txt";
	bestanden_beginposities[2][0][2] = "sitnikov_4_mas.txt";

	bestanden_beginposities[2][1][0] = "klavertje_pos.txt";
	bestanden_beginposities[2][1][1] = "klavertje_snel.txt";
	bestanden_beginposities[2][1][2] = "klavertje_mas.txt";

	bestanden_beginposities[2][2][0] = "dubbeldubbelster_pos.txt";
	bestanden_beginposities[2][2][1] = "dubbeldubbelster_snel.txt";
	bestanden_beginposities[2][2][2] = "dubbeldubbelster_mas.txt";

	bestanden_beginposities[3][0][0] = "klavertje_steel_pos.txt";
	bestanden_beginposities[3][0][1] = "klavertje_steel_snel.txt";
	bestanden_beginposities[3][0][2] = "klavertje_steel_mas.txt";

	bestanden_beginposities[3][1][0] = "solar_binnen_pos.txt";
	bestanden_beginposities[3][1][1] = "solar_binnen_snel.txt";
	bestanden_beginposities[3][1][2] = "solar_binnen_mas.txt";

	bestanden_beginposities[3][2][0] = "lagrange_pos.txt";
	bestanden_beginposities[3][2][1] = "lagrange_snel.txt";
	bestanden_beginposities[3][2][2] = "lagrange_mas.txt";

	bestanden_beginposities[4][0][0] = "solar_pos.txt";
	bestanden_beginposities[4][0][1] = "solar_snel.txt";
	bestanden_beginposities[4][0][2] = "solar_mas.txt";

	bestanden_beginposities[4][1][0] = "6_2_pos.txt";
	bestanden_beginposities[4][1][1] = "6_2_snel.txt";
	bestanden_beginposities[4][1][2] = "6_2_mas.txt";

	bestanden_beginposities[4][2][0] = "6_3_pos.txt";
	bestanden_beginposities[4][2][1] = "6_3_snel.txt";
	bestanden_beginposities[4][2][2] = "6_3_mas.txt";

	bestanden_beginposities[5][0][0] = "solar+_pos.txt";
	bestanden_beginposities[5][0][1] = "solar+_snel.txt";
	bestanden_beginposities[5][0][2] = "solar+_mas.txt";

	bestanden_beginposities[5][1][0] = "7_2_pos.txt";
	bestanden_beginposities[5][1][1] = "7_2_snel.txt";
	bestanden_beginposities[5][1][2] = "7_2_mas.txt";

	bestanden_beginposities[5][2][0] = "7_3_pos.txt";
	bestanden_beginposities[5][2][1] = "7_3_snel.txt";
	bestanden_beginposities[5][2][2] = "7_3_mas.txt";

	return bestanden_beginposities;
}


int nummer_beginconditie(int aantal) {

	
	//geeft user de mogelijke opties
	cout << "Voor " << lijst_begincond_namen()[aantal][1] << ", kies 1." << endl;
	cout << "Voor " << lijst_begincond_namen()[aantal][2] << ", kies 2." << endl;
	cout << "Voor " << lijst_begincond_namen()[aantal][3] << ", kies 3." << endl;

	//leest input in
	string keuze = lees_input();
	
	//controleert of input een integer is
	if (!input_is_integer(keuze)) {
		cout << "Error, dit is geen van bovenstaande opties." << endl;
		return nummer_beginconditie(aantal);
	}

	//zet string om naar integer wanneer integer vorm heeft
	std::string::size_type sz;   // alias of size_t
	int optie = std::stoi(keuze, &sz);

	//controleert of het in de map met opties zit
	if (lijst_begincond_namen()[aantal].count(optie) == 0) {
		cout << "Error, dit is geen van bovenstaande opties." << endl;
		return nummer_beginconditie(aantal);
	}

	//als alles goed is, return nummer optie terug
	return optie;

}


std::vector<Vec> posities(int aantal_deeltjes, int beginconditie) {

	//aanmaken vector van positie vectoren
	vector<Vec> posities;

	//opzoeken gewenste begin condities
	//-2 wegens maar info vanaf 2 deeltjes
	//zelfde voor optie (vraag vanaf optie 1,  maar index begint op 0)
	string positie = lijst_begincond()[aantal_deeltjes-2][beginconditie-1][0];

	//maak de stream klaar
	std::fstream myfile(positie, std::ios_base::in);

	//maak variabele voor inlezen klaar
	double pos_x;
	double pos_y;
	double pos_z;

	//lees ze in en steek ze in vector, wel per 3 in for loop want 3D posities
	while (myfile >> pos_x >> pos_y >> pos_z)
	{
		//steek ze dan in vectorlijst met alle posities
		posities.push_back(Vec(pos_x, pos_y, pos_z));
		
	}

	//geef lijst met posities terug
	return posities;

}


std::vector<Vec> snelheden(int aantal_deeltjes, int beginconditie) {

	//aanmaken vector van snelheid vectoren
	vector<Vec> snelheden;

	//opzoeken gewenste begin condities
	//-2 wegens maar info vanaf 2 deeltjes
	//zelfde voor optie (vraag vanaf optie 1,  maar index begint op 0)
	string snelheid = lijst_begincond()[aantal_deeltjes-2][beginconditie-1][1];

	//maak de stream klaar
	std::fstream myfile(snelheid, std::ios_base::in);

	//maak variabele voor inlezen klaar
	double snel_x;
	double snel_y;
	double snel_z;

	//lees ze in en steek ze in vector, wel per 3 in for loop want 3D posities
	while (myfile >> snel_x >> snel_y >> snel_z)
	{
		//steek ze dan in vectorlijst met alle posities
		snelheden.push_back(Vec(snel_x, snel_y, snel_z));

	}

	//geef lijst met posities terug
	return snelheden;

}

std::vector<double> massas(int aantal_deeltjes, int beginconditie) {

	//aanmaken vector van massas
	vector<double> massas;

	//opzoeken gewenste begin condities
	//-2 wegens maar info vanaf 2 deeltjes
	//zelfde voor optie (vraag vanaf optie 1,  maar index begint op 0)
	string massa = lijst_begincond()[aantal_deeltjes-2][beginconditie-1][2];

	//maak de stream klaar
	std::fstream myfile(massa, std::ios_base::in);

	//maak variabele voor inlezen klaar
	double ind_massa;

	//lees ze in en steek ze in vector
	while (myfile >> ind_massa)
	{
		massas.push_back(ind_massa);
	}

	//return vector met genormeerde massas
	return massas;
}

double x_pos_snel(int deeltje, bool positie) {

	cout << endl;
	//vraagt double op, afh van of het positie of snelheid is
	cout << "Geef de x";
	if (positie) {
		cout << " positie";
	}
	else {
		cout << " snelheid";
	}

	cout << " van deeltje " << deeltje << " op :";
	string input = lees_input();

	//checkt of dit vorm double is
	if (!input_is_double(input, 0)) {
		cout << "Geen double, probeer opnieuw" << endl;
		return x_pos_snel(deeltje, positie);
	}
	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double x = std::stof(input, &sz);

	//geef double terug
	return x;
}


double y_pos_snel(int deeltje, bool positie) {

	cout << endl;
	//vraagt double op, afh van of het positie of snelheid is
	cout << "Geef de y";
	if (positie) {
		cout << " positie";
	}
	else {
		cout << " snelheid";
	}

	cout << " van deeltje " << deeltje << " op :";
	string input = lees_input();

	//checkt of dit vorm double is
	if (!input_is_double(input, 0)) {
		cout << "Geen double, probeer opnieuw" << endl;
		return y_pos_snel(deeltje, positie);
	}
	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double y = std::stof(input, &sz);

	//geef double terug
	return y;
}


double z_pos_snel(int deeltje, bool positie) {

	cout << endl;
	//vraagt double op, afh van of het positie of snelheid is
	cout << "Geef de z";
	if (positie) {
		cout << " positie";
	}
	else {
		cout << " snelheid";
	}

	cout << " van deeltje " << deeltje << " op :";
	string input = lees_input();

	//checkt of dit vorm double is
	if (!input_is_double(input, 0)) {
		cout << "Geen double, probeer opnieuw" << endl;
		return z_pos_snel(deeltje, positie);
	}
	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double z = std::stof(input, &sz);

	//geef double terug
	return z;
}

//functie voor opvragen massa
double opvraag_massa(int deeltje) {

	//vraagt double op
	cout << endl << "Geef massa voor deeltje " << deeltje<< " op: ";
	string input = lees_input();

	//checkt of dit vorm double is
	if (!input_is_double(input, 1)) {
		cout << "Geen nietnegatieve double, probeer opnieuw" << endl;
		return opvraag_massa(deeltje);
	}
	//maakt van de string een double
	std::string::size_type sz;     // alias of size_t
	double massa = std::stof(input, &sz);

	//geef double terug
	return massa;
}


vector<Vec> vraag_posities(int aantal_deeltjes) {

	//maak alle posities aan
	vector<Vec> posities;

	//vraag alle x,y,z voor elk deeltje op en steek ze in de begin_posities
	for (int i = 0; i < aantal_deeltjes; i++) {
		double x = x_pos_snel(i + 1, 1);
		double y = y_pos_snel(i + 1, 1);
		double z = z_pos_snel(i + 1, 1);

		Vec positie = Vec(x, y, z);
		posities.push_back(positie);
	}
	
	//return begin_posities
	return posities;
}


vector<Vec> vraag_snelheden(int aantal_deeltjes) {

	//maak alle snelheden aan
	vector<Vec> snelheden;

	//vraag alle x,y,z voor elk deeltje op en steek ze in de begin_snelheden
	for (int i = 0; i < aantal_deeltjes; i++) {
		double x = x_pos_snel(i + 1, 0);
		double y = y_pos_snel(i + 1, 0);
		double z = z_pos_snel(i + 1, 0);

		Vec snelheid = Vec(x, y, z);
		snelheden.push_back(snelheid);
	}

	//return begin_posities
	return snelheden;
}


vector<double> vraag_massas(int aantal_deeltjes) {

	//maak massas aan
	vector<double> massas;

	//overloop en vraag alle massas op
	for (int i = 0; i < aantal_deeltjes; i++) {
		double massa = opvraag_massa(i + 1);
		massas.push_back(massa);
	}

	//return
	return massas;
}

//functie voor tonen alle beginposities aan user (ter controle)
void print_posities(std::vector<Vec> begin_posities) {
	for (vector<Vec>::const_iterator i = begin_posities.begin(); i != begin_posities.end(); i++) {
		print(*i);
	}
	cout << endl;
}

//functie voor tonen alle beginsnelheden aan user (ter controle)
void print_snelheden(std::vector<Vec> begin_snelheden) {
	for (vector<Vec>::const_iterator j = begin_snelheden.begin(); j != begin_snelheden.end(); j++) {
		print(*j);
	}
	cout << endl;
}

//functie voor tonen alle beginmassas aan user (ter controle)
void print_massas(std::vector<double> begin_massas) {
	for (vector<double>::const_iterator k = begin_massas.begin(); k != begin_massas.end(); k++) {
		cout << *k << endl;
	}
	cout << endl;
}

