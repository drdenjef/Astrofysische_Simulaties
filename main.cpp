#include "3DVectClass.h"
#include "GebruikerInterface.h"
#include "InitCondities.h"


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
	float h = tijdstap_opvraag();
	//zeg gebruiker wat hij/zij/het gekozen heeft van h
	cout << endl << "De gekozen tijdstap is " << h << ' ' << endl;
	
	//vraag de gebruiker of hij/zij/het initiele begincondities wilt gebruiken (of er zelf in wilt voeren)
	bool load_init_cond = aanwezige_begincondities();
	//maakt duidelijk wat de keuze was
	cout << endl << "U heeft ";
	if (load_init_cond == 1) {
		cout << "Ja gekozen." << endl;

		//vraagt naam (nummer) van voorgecodeerde begincondities op
		int optie = nummer_beginconditie(aantal);

		//return de keuze
		//-2 wegens pas informatie vanaf 2 deeltjes (maar starg op 0de positie)
		cout << endl << "U heeft " << lijst_begincond_namen()[aantal-2][optie] << " gekozen." << endl;

		//vraag de gewenste begin condities op
		vector<Vec> begin_posities = posities(aantal, optie);
		vector<Vec> begin_snelheden = snelheden(aantal, optie);
		vector<float> begin_massas = massas(aantal, optie);

		//schrijft beginposities uit
		cout << "Dit zijn de startposities" << endl;
		print_posities(begin_posities);

		//schrijft beginsnelheden uit
		cout << "Dit zijn de startsnelheden" << endl;
		print_snelheden(begin_snelheden);

		//schrijft beginmassas uit
		cout << "Dit zijn de startmassas" << endl;
		print_massas(begin_massas);

	}
	else {
		cout << "Neen gekozen." << endl << endl;
	}


	getchar(); 

	return 0;
}
