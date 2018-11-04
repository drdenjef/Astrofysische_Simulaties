#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "3DVectClass.h"
#include "GebruikerInterface.h"

using namespace std;


std::vector<std::map<int, std::string>> lijst_begincond_namen() {
	//maak een map aan voor elke dimentie
	std::map<int, std::string> map2;
	std::map<int, std::string> map3;
	std::map<int, std::string> map4;
	std::map<int, std::string> map5;
	std::map<int, std::string> map6;
	std::map<int, std::string> map7;

	//voor elke dimentie, definieer wat namen voor initiele begincondities
	map2[1] = "2deeltjes_1";
	map2[2] = "2deeltjes_2";
	map2[3] = "2deeltjes_3";

	map3[1] = "3deeltjes_1";
	map3[2] = "3deeltjes_2";
	map3[3] = "3deeltjes_3";

	map4[1] = "4deeltjes_1";
	map4[2] = "4deeltjes_2";
	map4[3] = "4deeltjes_3";

	map5[1] = "5deeltjes_1";
	map5[2] = "5deeltjes_2";
	map5[3] = "5deeltjes_3";

	map6[1] = "6deeltjes_1";
	map6[2] = "6deeltjes_2";
	map6[3] = "6deeltjes_3";

	map7[1] = "7deeltjes_1";
	map7[2] = "7deeltjes_2";
	map7[3] = "7deeltjes_3";

	//voeg deze mappen toe aan een vector voor alle dimenties
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
	bestanden_beginposities[0][0][0] = "2_1_pos.txt";
	bestanden_beginposities[0][0][1] = "2_1_snel.txt";
	bestanden_beginposities[0][0][2] = "2_1_mas.txt";

	bestanden_beginposities[0][1][0] = "2_2_pos.txt";
	bestanden_beginposities[0][1][1] = "2_2_snel.txt";
	bestanden_beginposities[0][1][2] = "2_2_mas.txt";

	bestanden_beginposities[0][2][0] = "2_3_pos.txt";
	bestanden_beginposities[0][2][1] = "2_3_snel.txt";
	bestanden_beginposities[0][2][2] = "2_3_mas.txt";

	bestanden_beginposities[1][0][0] = "3_1_pos.txt";
	bestanden_beginposities[1][0][1] = "3_1_snel.txt";
	bestanden_beginposities[1][0][2] = "3_1_mas.txt";

	bestanden_beginposities[1][1][0] = "3_2_pos.txt";
	bestanden_beginposities[1][1][1] = "3_2_snel.txt";
	bestanden_beginposities[1][1][2] = "3_2_mas.txt";

	bestanden_beginposities[1][2][0] = "3_3_pos.txt";
	bestanden_beginposities[1][2][1] = "3_3_snel.txt";
	bestanden_beginposities[1][2][2] = "3_3_mas.txt";

	bestanden_beginposities[2][0][0] = "4_1_pos.txt";
	bestanden_beginposities[2][0][1] = "4_1_snel.txt";
	bestanden_beginposities[2][0][2] = "4_1_mas.txt";

	bestanden_beginposities[2][1][0] = "4_2_pos.txt";
	bestanden_beginposities[2][1][1] = "4_2_snel.txt";
	bestanden_beginposities[2][1][2] = "4_2_mas.txt";

	bestanden_beginposities[2][2][0] = "4_3_pos.txt";
	bestanden_beginposities[2][2][1] = "4_3_snel.txt";
	bestanden_beginposities[2][2][2] = "4_3_mas.txt";

	bestanden_beginposities[3][0][0] = "5_1_pos.txt";
	bestanden_beginposities[3][0][1] = "5_1_snel.txt";
	bestanden_beginposities[3][0][2] = "5_1_mas.txt";

	bestanden_beginposities[3][1][0] = "5_2_pos.txt";
	bestanden_beginposities[3][1][1] = "5_2_snel.txt";
	bestanden_beginposities[3][1][2] = "5_2_mas.txt";

	bestanden_beginposities[3][2][0] = "5_3_pos.txt";
	bestanden_beginposities[3][2][1] = "5_3_snel.txt";
	bestanden_beginposities[3][2][2] = "5_3_mas.txt";

	bestanden_beginposities[4][0][0] = "6_1_pos.txt";
	bestanden_beginposities[4][0][1] = "6_1_snel.txt";
	bestanden_beginposities[4][0][2] = "6_1_mas.txt";

	bestanden_beginposities[4][1][0] = "6_2_pos.txt";
	bestanden_beginposities[4][1][1] = "6_2_snel.txt";
	bestanden_beginposities[4][1][2] = "6_2_mas.txt";

	bestanden_beginposities[4][2][0] = "6_3_pos.txt";
	bestanden_beginposities[4][2][1] = "6_3_snel.txt";
	bestanden_beginposities[4][2][2] = "6_3_mas.txt";

	bestanden_beginposities[5][0][0] = "7_1_pos.txt";
	bestanden_beginposities[5][0][1] = "7_1_snel.txt";
	bestanden_beginposities[5][0][2] = "7_1_mas.txt";

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
	//zelfde voor optie (vraag vanaf 1 maar index vanaf 0)
	string positie = lijst_begincond()[aantal_deeltjes-2][beginconditie-1][0];

	//maak de stream klaar
	std::fstream myfile(positie, std::ios_base::in);

	//maak variabele voor inlezen klaar
	float pos_x;
	float pos_y;
	float pos_z;

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
	//zelfde voor optie (vraag vanaf 1 maar index vanaf 0)
	string snelheid = lijst_begincond()[aantal_deeltjes-2][beginconditie-1][1];

	//maak de stream klaar
	std::fstream myfile(snelheid, std::ios_base::in);

	//maak variabele voor inlezen klaar
	float snel_x;
	float snel_y;
	float snel_z;

	//lees ze in en steek ze in vector, wel per 3 in for loop want 3D posities
	while (myfile >> snel_x >> snel_y >> snel_z)
	{
		//steek ze dan in vectorlijst met alle posities
		snelheden.push_back(Vec(snel_x, snel_y, snel_z));

	}

	//geef lijst met posities terug
	return snelheden;

}

std::vector<float> massas(int aantal_deeltjes, int beginconditie) {

	//aanmaken vector van massas
	vector<float> massas;

	//opzoeken gewenste begin condities
	//-2 wegens maar info vanaf 2 deeltjes
	//zelfde voor optie (vraag vanaf 1 maar index vanaf 0)
	string massa = lijst_begincond()[aantal_deeltjes-2][beginconditie-1][2];

	//maak de stream klaar
	std::fstream myfile(massa, std::ios_base::in);

	//maak variabele voor inlezen klaar
	float ind_massa;

	//lees ze in en steek ze in vector
	while (myfile >> ind_massa)
	{
		massas.push_back(ind_massa);
	}

	//return vector met massas
	return massas;
}


