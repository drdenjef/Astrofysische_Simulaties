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

		//MOET HIERVOOR PRINT VOOR VECTOREN EN PRINT VOOR 3DVECT MAKEN INDIEN GEWENST
		//cout << "Dit zijn de begin posities" << endl << begin_posities << endl << endl;
		//cout << "Dit zijn de begin snelheden" << endl << begin_snelheden << endl << endl;
		//cout << "Dit zijn de begin massas" << endl << begin_massas << endl << endl;

		//de correcte begincondities worden wel geladen, al getest via debuggen

	}
	else {
		cout << "Neen gekozen." << endl << endl;
	}


	getchar(); 

	return 0;
}
