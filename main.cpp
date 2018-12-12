#include "3DVectClass.h"
#include "GebruikerInterface.h"
#include "InitCondities.h"
#include "random_init.h"

//de main functie
int main() {
	using namespace std;
	
	//vraag aantal objecten aan gebruiker
	int aantal = aantal_objecten();
	//zeg gebruiker wat hij/zij/het heeft gekozen
	cout << endl <<"Aantal deeltjes is " << aantal << "." << endl << endl;

	//vraag type integratie aan gebruiker
	int integratie = type_integratie_cijfer();
	cout << endl << "De gekozen type integratie is ";
	//zeg gebruiker wat hij/zij/het gekozen heeft
	cout << type_integratie_naam(integratie) << endl << endl;

	//vraagt tijdstap aan gebruiker
	double h = tijdstap_opvraag();
	//zeg gebruiker wat hij/zij/het gekozen heeft van h
	cout << endl << "De gekozen tijdstap is " << h << ' ' << endl << endl;

	//vraagt of gebruiker een variabele tijdstap wilt
	bool gebruiken_var_h = gebruik_var_h();
	//confirmeer keuze aan gebruiker
	cout << endl << "U heeft ";
	if (gebruiken_var_h)
		cout << "ja gekozen" << endl << endl;
	else
		cout << "neen gekozen" << endl << endl;

	//vraagt integratietijd aan gebruiker
	double integratietijd = tijd_opvraag(h);
	//zeg gebruiker wat hij/zij/het gekozen heeft van integratietijd
	cout << endl << "De gekozen integratietijd is " << integratietijd << ' ' << endl << endl;

	//vraagt hoe vaak positie weggeschreven moet worden
	int fractie = fractie_opvraag(integratietijd, h);
	//zeg gebruiker wat hij/zij/het gekozen heeft
	cout << endl << "Men zal om de " << fractie << " integraties de posities wegschrijven." << endl << endl;
	
	//vraag de gebruiker of hij/zij/het initiele begincondities wilt gebruiken (of er zelf in wilt voeren)
	bool load_init_cond = aanwezige_begincondities();
	//maakt duidelijk wat de keuze was
	cout << endl << "U heeft ";

	//maak alle objecten aan, zodat ze na de ifelse nog gebruikt kunnen worden
	vector<Vec> begin_posities;
	vector<Vec> begin_snelheden;
	vector<double> begin_massas;
	if (load_init_cond == 1) {
		cout << "ja gekozen." << endl << endl;

		//vraagt naam (nummer) van voorgecodeerde begincondities op
		//-2 wegens pas informatie vanaf 2 deeltjes (maar start op 0de positie)
		int optie = nummer_beginconditie(aantal-2);

		//return de keuze
		//-2 wegens pas informatie vanaf 2 deeltjes (maar start op 0de positie)
		cout << endl << "U heeft " << lijst_begincond_namen()[aantal-2][optie] << " gekozen." << endl << endl;

		//slaat de gewenste begin condities op
		begin_posities = posities(aantal, optie);
		begin_snelheden = snelheden(aantal, optie);
		begin_massas = massas(aantal, optie);

	
	}
	else {
		cout << "neen gekozen." << endl << endl;

		//vraagt of gebruiker random wilt genereren
		bool random = random_genereren();
		//maakt duidelijk wat de keuze was
		cout << endl << "U heeft ";

		if (random) {
			cout << " ja gekozen." << endl << endl;

			//slaat random gebonden toestand genereren
			begin_massas = massrescaling(randommass(aantal));
			begin_posities = posrescaling(begin_massas, randomVec(aantal));
			begin_snelheden = velrescaling(begin_massas, randomVec(aantal));

		}

		else {

			cout << " neen gekozen." << endl << endl;
			//vraag de gewenste begin condities op (via gebruiker) en slaat ze op
			begin_posities = vraag_posities(aantal);
			begin_snelheden = vraag_snelheden(aantal);
			begin_massas = vraag_massas(aantal);
		}
	}
	
	//schrijft beginposities uit
	cout << "Dit zijn de startposities" << endl ;
	print_posities(begin_posities);

	//schrijft beginsnelheden uit
	cout << "Dit zijn de startsnelheden" << endl;
	print_snelheden(begin_snelheden);

	//schrijft beginmassas uit
	cout << "Dit zijn de startmassas" << endl;
	print_massas(begin_massas);

	//vraagt naam bestand voor wegschrijven op
	cout << "Geef naam naar waar de data weggeschreven wordt op: ";
	string bestand_naam = lees_input();
	cout << '\n' << "De gekozen naam is: " << bestand_naam << endl << endl;

	//nu derigeren naar juiste methode
	alle_posities(begin_massas, begin_posities, begin_snelheden, aantal, integratietijd, h, integratie, bestand_naam, gebruiken_var_h, fractie);

	//vraagt char op zodat het niet meteen afsluit, maar gebruiker zelf kan kiezen
	cout << "Druk op eenderwelke toets om af te sluiten.";
	getchar(); 

	return 0;
}
