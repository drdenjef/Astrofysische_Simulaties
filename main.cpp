#include "3DVectClass.h"
#include "GebruikerInterface.h"
#include "InitCondities.h"
#include <time.h>
#include <string>
#include <random>
#include "random_init.h"



//de main function
int main() {
	using namespace std;
	
	//vraag aantal objecten aan gebruiker
	int aantal = aantal_objecten();
	cout << endl <<"Aantal deeltjes is " << aantal << "." << endl << endl;

	//vraag type integratie aan gebruiker
	int integratie = type_integratie_cijfer();
	cout << endl << "De gekozen type integratie is ";
	//zeg gebruiker wat hij/zij/het gekozen heeft
	cout << type_integratie_naam(integratie) << endl << endl;

	//vraagt tijdstap aan gebruiker
	double h = tijdstap_opvraag();
	//zeg gebruiker wat hij/zij/het gekozen heeft van h
	cout << endl << "De gekozen tijdstap is " << h << ' ' << endl;

	//vraagt of gebruiker een variabele tijdstap wilt
	bool gebruiken_var_h = gebruik_var_h();
	//confirmeer keuze aan gebruiker
	cout << endl << "U heeft ";
	if (gebruiken_var_h)
		cout << "ja gekozen" << endl;
	else
		cout << "neen gekozen" << endl;

	//vraagt aantal iteraties aan gebruiker;
	int iteraties = iteraties_opvraag();
	//zeg gebruiker wat hij/zij/het gekozen heeft van iteraties;
	cout << endl << "De gekozen aantal iteraties is " << iteraties << ' ' << endl;
	
	//vraag de gebruiker of hij/zij/het initiele begincondities wilt gebruiken (of er zelf in wilt voeren)
	bool load_init_cond = aanwezige_begincondities();
	//maakt duidelijk wat de keuze was
	cout << endl << "U heeft ";

	//maak alle objecten aan, zodat ze na de ifelse nog gebruikt kunnen worden
	vector<Vec> begin_posities;
	vector<Vec> begin_snelheden;
	vector<double> begin_massas;
	if (load_init_cond == 1) {
		cout << "ja gekozen." << endl;

		//vraagt naam (nummer) van voorgecodeerde begincondities op
		int optie = nummer_beginconditie(aantal);

		//return de keuze
		//-2 wegens pas informatie vanaf 2 deeltjes (maar starg op 0de positie)
		cout << endl << "U heeft " << lijst_begincond_namen()[aantal-2][optie] << " gekozen." << endl;

		//vraag de gewenste begin condities op
		begin_posities = posities(aantal, optie);
		begin_snelheden = snelheden(aantal, optie);
		begin_massas = massas(aantal, optie);

	
	}
	else {
		cout << "neen gekozen." << endl;

		//vraagt of gebruiker random wilt genereren
		bool random = random_genereren();
		//maakt duidelijk wat de keuze was
		cout << endl << "U heeft ";

		if (random) {
			cout << " ja gekozen." << endl;

			//laat random gebonden toestand genereren
			begin_massas = massrescaling(randommass(aantal));
			begin_posities = posrescaling(begin_massas, randomVec(aantal));
			begin_snelheden = velrescaling(begin_massas, randomVec(aantal));

		}

		else {

			cout << " neen gekozen." << endl;
			//vraag de gewenste begin condities op
			begin_posities = vraag_posities(aantal);
			begin_snelheden = vraag_snelheden(aantal);
			begin_massas = vraag_massas(aantal);
		}
	}
	
	//schrijft beginposities uit
	cout << "Dit zijn de startposities" << endl;
	print_posities(begin_posities);

	//schrijft beginsnelheden uit
	cout << "Dit zijn de startsnelheden" << endl;
	print_snelheden(begin_snelheden);

	//schrijft beginmassas uit
	cout << "Dit zijn de startmassas" << endl;
	print_massas(begin_massas);

	//vraagt naam bestand voor wegschrijven op
	cout << "Geef naam naar waar de posities weggeschreven wordt op: ";
	string bestand_naam = lees_input();
	cout << '\n' << "De gekozen naam is: " << bestand_naam << endl;

	//nu derigeren naar juiste methode, dit geeft een vector van vector van Vec's terug, eerste lengte is aantal iteraties, tweede is aantal deeltjes, derde zijn de posities
	//dit komt achteraf buiten deze if, maar moet nu nog binnen

	//berekent tijd hoe lang dit duurde
	clock_t tStart = clock();
	alle_posities(begin_massas, begin_posities, begin_snelheden, aantal, iteraties, h, integratie, bestand_naam, gebruiken_var_h);
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);


	getchar(); 

	return 0;
}
